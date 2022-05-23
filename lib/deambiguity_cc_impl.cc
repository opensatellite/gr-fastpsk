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
#include <gnuradio/expj.h>
#include "deambiguity_cc_impl.h"

namespace gr {
  namespace fastpsk {

    deambiguity_cc::sptr
    deambiguity_cc::make(int npsk, bool swap, bool diff)
    {
      return gnuradio::get_initial_sptr
        (new deambiguity_cc_impl(npsk, swap, diff));
    }

    /*
     * The private constructor
     */
    deambiguity_cc_impl::deambiguity_cc_impl(int npsk, bool swap, bool diff)
      : gr::sync_block("deambiguity_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex))),
              d_phase(gr_complex(1.0, 0.0)),
              d_swap(false),
              d_diff(diff)
    {
      if(diff) {
        set_history(2);
      } else {
        for(int i = 0; i < npsk; i++) {
          float phase = 2.0 * M_PI * i / npsk;
          gr_complex p = gr_expj(phase);
          rotate.push_back(p);
        }
      }
    }

    /*
     * Our virtual destructor.
     */
    deambiguity_cc_impl::~deambiguity_cc_impl()
    {
    }

    void deambiguity_cc_impl::set_phase(int x) {
      d_phase = rotate[x];
    }

    void deambiguity_cc_impl::set_swap(bool en) {
      d_swap = en;
    }

    int
    deambiguity_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      if(d_diff) {
        for(int i = 0; i < noutput_items; i++) {
          //in[i+1] * conj(in[i])
          float o_r = (in[i+1].real() * in[i].real()) + (in[i+1].imag() * in[i].imag());
          float o_i = (in[i+1].imag() * in[i].real()) - (in[i+1].real() * in[i].imag());
          if(d_swap) {
            out[i].real(o_i);
            out[i].imag(o_r);
          } else {
            out[i].real(o_r);
            out[i].imag(o_i);
          }
        }
      } else {
        for(int i = 0; i < noutput_items; i++) {
          float o_r = (in[i].real() * d_phase.real()) - (in[i].imag() * d_phase.imag());
          float o_i = (in[i].real() * d_phase.imag()) + (in[i].imag() * d_phase.real());
          if(d_swap) {
            out[i].real(o_i);
            out[i].imag(o_r);
          } else {
            out[i].real(o_r);
            out[i].imag(o_i);
          }
        }
      }

      // Do <+signal processing+>

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace fastpsk */
} /* namespace gr */
