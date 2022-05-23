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
#include "npsk_lockdet_impl.h"

namespace gr {
  namespace fastpsk {

    npsk_lockdet::sptr
    npsk_lockdet::make(int n, int npsk, float alpha, float thresh)
    {
      return gnuradio::get_initial_sptr
        (new npsk_lockdet_impl(n, npsk, alpha, thresh));
    }

    /*
     * The private constructor
     */
    npsk_lockdet_impl::npsk_lockdet_impl(int n, int npsk, float alpha, float thresh)
      : gr::sync_decimator("npsk_lockdet",
              gr::io_signature::make(1, 1, sizeof(sc16)),
              gr::io_signature::make(1, 1, sizeof(float)), n),
              d_n(n),
              d_npsk(npsk),
              d_alpha(alpha),
              d_thresh(thresh),
              d_err(0)
    {

    }

    /*
     * Our virtual destructor.
     */
    npsk_lockdet_impl::~npsk_lockdet_impl()
    {
    }

    const int npsk_lockdet_impl::scale = 8192;
    const int npsk_lockdet_impl::shift = 13;

    bool npsk_lockdet_impl::is_locked() {
      return d_err >= d_thresh;
    }

    int
    npsk_lockdet_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const sc16 *in = (const sc16 *) input_items[0];
      float *out = (float *) output_items[0];

      // Do <+signal processing+>
      //BPSK lock detector: abs(I)-abs(Q), I*I-Q*Q
      //QPSK lock detector: err = 2*abs(I*Q) - abs(I*I-Q*Q)
      //8PSK lock detector: atan2

      for(int i = 0; i < noutput_items; i++) {
        for(int j = 0; j < d_n; j++) {

        }
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace fastpsk */
} /* namespace gr */
