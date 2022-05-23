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
#include "qdelay_impl.h"

namespace gr {
  namespace fastpsk {

    qdelay::sptr
    qdelay::make(int delay)
    {
      return gnuradio::get_initial_sptr
        (new qdelay_impl(delay));
    }

    /*
     * The private constructor
     */
    qdelay_impl::qdelay_impl(int delay)
      : gr::sync_block("qdelay",
              gr::io_signature::make(1, 1, sizeof(sc16)),
              gr::io_signature::make(1, 1, sizeof(sc16)))
    {
      if(delay >= 0) {
        d = delay;
        dr = delay;
        di = 0;
        set_history(delay+1);
      } else {
        d = -delay;
        dr = 0;
        di = -delay;
        set_history(-delay+1);
      }
    }

    /*
     * Our virtual destructor.
     */
    qdelay_impl::~qdelay_impl()
    {
    }

    int
    qdelay_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const sc16 *in = (const sc16*) input_items[0];
      sc16 *out = (sc16 *) output_items[0];

      // Do <+signal processing+>
      for(int i = 0; i < noutput_items; i++) {
        out[i].real(in[i+dr].real());
        out[i].imag(in[i+di].imag());
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace fastpsk */
} /* namespace gr */
