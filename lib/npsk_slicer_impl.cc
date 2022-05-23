/* -*- c++ -*- */
/*
 * Copyright 2022 kcsa.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "npsk_slicer_impl.h"

namespace gr {
  namespace fastpsk {

    npsk_slicer::sptr
    npsk_slicer::make(int npsk, bool gray)
    {
      return gnuradio::get_initial_sptr
        (new npsk_slicer_impl(npsk, gray));
    }

    static int log2(unsigned int x) {
      if(x == 0) return -1;
      if(x == 1) return 0;
      int ret = 0;
      while(x > 1) {
        x >>= 1;
        ret++;
      }
      return ret;
    }

    /*
     * The private constructor
     */
    npsk_slicer_impl::npsk_slicer_impl(int npsk, bool gray)
      : gr::sync_interpolator("npsk_slicer",
              gr::io_signature::make(1, 1, sizeof(sc16)),
              gr::io_signature::make(1, 1, sizeof(char)), log2(npsk)),
              n(npsk)
    {
      //std::cout << "npsk_slicer: npsk=" << n << ", bits_per_sym=" << log2(n) << std::endl;
      if(npsk == 2) {
        d_gray = false;
      } else if(npsk == 4) {
        d_gray = gray;
      } else if(npsk == 8) {
        d_gray = gray;
      } else {
        throw("invalid npsk value");
      }
    }

    /*
     * Our virtual destructor.
     */
    npsk_slicer_impl::~npsk_slicer_impl()
    {
    }

#define SLICE(X)   ((X) >= 0 ? 1 : 0)

    int
    npsk_slicer_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const sc16 *in = (const sc16 *) input_items[0];
      char *out = (char *) output_items[0];

      // Do <+signal processing+>
      if(d_gray) {
        if(n == 4) {
          for(int i = 0; i < noutput_items / 2; i++) {
            out[i*2]   = SLICE(in[i].imag());
            out[i*2+1] = SLICE(in[i].real());
          }
        } else if(n == 8) {
          for(int i = 0; i < noutput_items / 3; i++) {
            int32_t a0 = in[i].imag() - in[i].real();
            int32_t a1 = in[i].imag() + in[i].real();
            int32_t a2 = std::min(std::abs(a0), std::abs(a1));
            out[i*3]   = in[i].imag() < 0 ? 1 : 0;
            out[i*3+1] = in[i].real() < 0 ? 1 : 0;
            out[i*3+2] = SLICE(a0) ^ SLICE(a1) ^ SLICE(a2);
          }
        } else {
          for(int i = 0; i < noutput_items; i++) {
            out[i] = SLICE(in[i].real());
          }
        }
      } else {
        if(n == 4) {
          for(int i = 0; i < noutput_items / 2; i++) {
            char b0 = SLICE(in[i].imag());
            char b1 = SLICE(in[i].real());
            if(b1 && b0) {
              out[i*2] = 1;
              out[i*2+1] = 0;
            } else if((!b1) && (b0)) {
              out[i*2] = 1;
              out[i*2+1] = 1;
            } else {
              out[i*2] = b0;
              out[i*2+1] = b1;
            }
          }
        } else if(n == 8) {
          for(int i = 0; i < noutput_items / 3; i++) {
            int32_t a0 = in[i].imag() - in[i].real();
            int32_t a1 = in[i].imag() + in[i].real();
            int32_t a2 = std::min(std::abs(a0), std::abs(a1));

            static const char lut[] = {0, 1, 3, 2, 7, 6, 4, 5};
            char sym = (SLICE(a0) ^ SLICE(a1) ^ SLICE(a2)) |
                       (in[i].real() < 0 ? 2 : 0) | (in[i].imag() < 0 ? 4 : 0);
            sym = lut[sym];
            out[i*3]   = sym >> 2;
            out[i*3+1] = (sym >> 1) & 1;
            out[i*3+2] = sym & 1;
          }
        }
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace fastpsk */
} /* namespace gr */
