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

#include "fir_filter_ssf_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
  namespace fastpsk {

    fir_filter_ssf::sptr
    fir_filter_ssf::make(int decim, const std::vector<float> &taps)
    {
      return gnuradio::get_initial_sptr
        (new fir_filter_ssf_impl(decim, taps));
    }

    /*
     * The private constructor
     */
    fir_filter_ssf_impl::fir_filter_ssf_impl(int decim, const std::vector<float> &taps)
      : gr::sync_decimator("fir_filter_ssf",
              gr::io_signature::make(1, 1, sizeof(sc16)),
              gr::io_signature::make(1, 1, sizeof(sc16)), decim)
    {
      d_updated = false;
      set_taps(taps);
      set_history(taps.size());
    }

    /*
     * Our virtual destructor.
     */
    fir_filter_ssf_impl::~fir_filter_ssf_impl()
    {
    }

    const int fir_filter_ssf_impl::scale = 32767;
    const int fir_filter_ssf_impl::shift = 15;

    void
    fir_filter_ssf_impl::set_taps(const std::vector<float> &taps)
    {
      gr::thread::scoped_lock l(d_setlock);
      itaps.resize(taps.size());
      //std::cout << "fir: taps=(";
      for(size_t i = 0; i < itaps.size(); i++) {
        itaps[i] = taps[i] * scale;
        //std::cout << itaps[i] << ",";
      }
      //std::cout << ")" << std::endl;
      d_updated = true;
    }

    std::vector<float>
    fir_filter_ssf_impl::taps() const
    {
      std::vector<float> taps(itaps.size(), 0);
      for(size_t i = 0; i < itaps.size(); i++) {
        float x = itaps[i];
        x /= scale;
        taps[i] = x;
      }
      return taps;
    }

    static sc16 dotprod(const sc16* in, int16_t *taps, int n, int shift) {
      int64_t re = 0, im = 0;
      const sc16* aPtr = in;
      const int16_t* bPtr = taps;

      for (int i = 0; i < n; i++)
      {
          re += real(*aPtr) * (*bPtr);
          im += imag(*aPtr) * (*bPtr);
          aPtr++;
          bPtr++;
      }
      re >>= shift;
      im >>= shift;

      if(re > 32767) re = 32767;
      else if(re < -32768) re = -32768;
      if(im > 32767) im = 32767;
      else if(im < -32768) im = -32768;

      return sc16(re, im);
    }

    int
    fir_filter_ssf_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      gr::thread::scoped_lock l(d_setlock);

      const sc16 *in = (const sc16 *) input_items[0];
      sc16 *out = (sc16 *) output_items[0];

      if (d_updated) {
      	set_history(itaps.size());
      	d_updated = false;
      	return 0;	     // history requirements may have changed.
      }

      if (decimation() == 1) {
	      for(int i = 0; i < noutput_items; i++) {
          out[i] = dotprod(&in[i], itaps.data(), itaps.size(), shift);
        }
      } else {
        int j = 0;
	      for(int i = 0; i < noutput_items; i++) {
          out[i] = dotprod(&in[j], itaps.data(), itaps.size(), shift);
          j += decimation();
        }
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace fastpsk */
} /* namespace gr */
