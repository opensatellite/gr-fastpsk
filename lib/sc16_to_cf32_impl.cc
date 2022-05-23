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
#include <fastpsk/icomplex.h>
#include "sc16_to_cf32_impl.h"

namespace gr {
  namespace fastpsk {

    sc16_to_cf32::sptr
    sc16_to_cf32::make(int scale)
    {
      return gnuradio::get_initial_sptr
        (new sc16_to_cf32_impl(scale));
    }

    /*
     * The private constructor
     */
    sc16_to_cf32_impl::sc16_to_cf32_impl(int scale)
      : gr::sync_block("sc16_to_cf32",
              gr::io_signature::make(1, 1, sizeof(sc16)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {
      s = 1.0f / ((float)scale);
    }

    /*
     * Our virtual destructor.
     */
    sc16_to_cf32_impl::~sc16_to_cf32_impl()
    {
    }

    int
    sc16_to_cf32_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const sc16 *in = (const sc16 *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      // Do <+signal processing+>
      for(int i = 0; i < noutput_items; i++) {
        float re = in[i].real();
        float im = in[i].imag();
        re *= s;
        im *= s;
        out[i] = gr_complex(re, im);
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace fastpsk */
} /* namespace gr */
