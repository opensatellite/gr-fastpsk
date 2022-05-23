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
#include "deambiguity_impl.h"
#include "imath.h"

namespace gr {
  namespace fastpsk {

    deambiguity::sptr
    deambiguity::make(int npsk, bool swap, bool diff)
    {
      return gnuradio::get_initial_sptr
        (new deambiguity_impl(npsk, swap, diff));
    }

    const int deambiguity_impl::scale = 8192;
    const int deambiguity_impl::shift = 13;

    /*
     * The private constructor
     */
    deambiguity_impl::deambiguity_impl(int npsk, bool swap, bool diff)
      : gr::sync_block("deambiguity",
              gr::io_signature::make(1, 1, sizeof(sc16)),
              gr::io_signature::make(1, 1, sizeof(sc16))),
              d_phase(sc16(scale, 0)),
              d_swap(false),
              d_diff(diff)
    {
      if(diff) {
        set_history(2);
      } else {
        for(int i = 0; i < npsk; i++) {
          float phase = 2.0 * M_PI * i / npsk;
          sc16 p = sc16_expj(phase, scale);
          rotate.push_back(p);
          //std::cout << "deambiguity: [" << i << "]=(" << p.real() << "," << p.imag() << ")" << std::endl;
        }
      }
    }

    /*
     * Our virtual destructor.
     */
    deambiguity_impl::~deambiguity_impl()
    {

    }

    void deambiguity_impl::set_phase(int x) {
      d_phase = rotate[x];
    }

    void deambiguity_impl::set_swap(bool en) {
      d_swap = en;
    }

    int
    deambiguity_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const sc16 *in = (const sc16 *) input_items[0];
      sc16 *out = (sc16 *) output_items[0];

      if(d_diff) {
        for(int i = 0; i < noutput_items; i++) {
          int32_t o_r = (in[i+1].real() * in[i].real()) + (in[i+1].imag() * in[i].imag());
          int32_t o_i = (in[i+1].imag() * in[i].real()) - (in[i+1].real() * in[i].imag());
          if(d_swap) {
            out[i].real(o_i >> shift);
            out[i].imag(o_r >> shift);
          } else {
            out[i].real(o_r >> shift);
            out[i].imag(o_i >> shift);
          }
        }
      } else {
        for(int i = 0; i < noutput_items; i++) {
          int32_t o_r = (in[i].real() * d_phase.real()) - (in[i].imag() * d_phase.imag());
          int32_t o_i = (in[i].real() * d_phase.imag()) + (in[i].imag() * d_phase.real());
          if(d_swap) {
            out[i].real(o_i >> shift);
            out[i].imag(o_r >> shift);
          } else {
            out[i].real(o_r >> shift);
            out[i].imag(o_i >> shift);
          }
        }
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace fastpsk */
} /* namespace gr */
