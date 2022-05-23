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
#include "agc_impl.h"
#include "imath.h"

namespace gr {
  namespace fastpsk {

    agc::sptr
    agc::make(int n, float ref, float rate, float max_gain)
    {
      return gnuradio::get_initial_sptr
        (new agc_impl(n, ref, rate, max_gain));
    }

    /*
     * The private constructor
     */
    agc_impl::agc_impl(int n, float ref, float rate, float max_gain)
      : gr::sync_block("agc",
              gr::io_signature::make(1, 1, sizeof(sc16)),
              gr::io_signature::make(1, 1, sizeof(sc16))),
              d_n(n),
              d_pwr(0),
              d_gain(1.0f),
              d_max_gain(max_gain),
              d_rate(rate),
              counter(0),
              debug(0)
    {
      char *debug_str = std::getenv("FASTPSK_DEBUG");
      if(debug_str) {
        debug = std::max(atoi(debug_str), 1024);
        std::cout << "agc: debug=" << debug << std::endl;
      }

      set_ref(ref);
      set_output_multiple(n);
    }

    /*
     * Our virtual destructor.
     */
    agc_impl::~agc_impl()
    {
    }

    void agc_impl::set_ref(float ref)
    {
      //d_ref = ref * ref * d_n;
      d_ref = ref * sqrtf(d_n);
    }

    void agc_impl::set_max_gain(float max_gain)
    {
      d_max_gain = max_gain;
    }

    float agc_impl::power()
    {
      return d_pwr;
    }

    float agc_impl::gain()
    {
      return d_gain;
    }

    int
    agc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const sc16 *in = (const sc16 *) input_items[0];
      sc16 *out = (sc16 *) output_items[0];

      //std::cout << "nout=" << noutput_items << std::endl;

      for(int j = 0; j < noutput_items / d_n; j++) {
          float pwr = 0;
          for(int i = 0; i < d_n; i++) {
            float re = in[i].real() * d_gain;
            float im = in[i].imag() * d_gain;
            //out[i].real() = branchless_clip(re, 32767.0f);
            //out[i].imag() = branchless_clip(im, 32767.0f);
            out[i] = sc16(re, im);
            //std::cout << re << "," << im << "," << std::endl;
            pwr += re*re + im*im;
          }

          d_pwr = pwr;
          float err = d_ref - sqrtf(d_pwr);
          d_gain = saturate(d_gain + d_rate * err, 1e-4, d_max_gain);

          if(debug > 0) {
            counter++;
            if(counter >= debug) {
              counter = 0;
              std::cout << "agc: " << err << "," << d_gain << std::endl;
            }
          }

          //move ptr
          in += d_n;
          out += d_n;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace fastpsk */
} /* namespace gr */
