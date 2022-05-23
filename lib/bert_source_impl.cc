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
#include "bert_source_impl.h"

namespace gr {
  namespace fastpsk {

    bert_source::sptr
    bert_source::make(int order)
    {
      return gnuradio::get_initial_sptr
        (new bert_source_impl(order));
    }

    /*
     * The private constructor
     */
    bert_source_impl::bert_source_impl(int order)
      : gr::sync_block("bert_source",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, sizeof(char))),
              phase(0)
    {
      pn = prbsx(order);
    }

    /*
     * Our virtual destructor.
     */
    bert_source_impl::~bert_source_impl()
    {
    }

    int
    bert_source_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      char *out = (char *) output_items[0];

      // Do <+signal processing+>
      for(int i = 0; i < noutput_items; i++) {
        out[i] = pn[phase];
        phase++;
        if(phase >= pn.size()) {
          phase = 0;
        }
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace fastpsk */
} /* namespace gr */
