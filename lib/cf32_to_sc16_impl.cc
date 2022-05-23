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
#include "imath.h"
#include "cf32_to_sc16_impl.h"

namespace gr {
  namespace fastpsk {

    cf32_to_sc16::sptr
    cf32_to_sc16::make(int scale)
    {
      return gnuradio::get_initial_sptr
        (new cf32_to_sc16_impl(scale));
    }

    /*
     * The private constructor
     */
    cf32_to_sc16_impl::cf32_to_sc16_impl(int scale)
      : gr::sync_block("cf32_to_sc16",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(sc16))),
              s(scale)
    {}

    /*
     * Our virtual destructor.
     */
    cf32_to_sc16_impl::~cf32_to_sc16_impl()
    {
    }

    int
    cf32_to_sc16_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      sc16 *out = (sc16 *) output_items[0];

      // Do <+signal processing+>
      for(int i = 0; i < noutput_items; i++) {
        float re = in[i].real() * s;
        float im = in[i].imag() * s;
        re = branchless_clip(re, 32767);
        im = branchless_clip(im, 32767);
        out[i] = sc16(re, im);
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace fastpsk */
} /* namespace gr */
