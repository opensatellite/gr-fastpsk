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

#ifndef INCLUDED_FASTPSK_MM_CREC_IMPL_H
#define INCLUDED_FASTPSK_MM_CREC_IMPL_H

#include <fastpsk/mm_crec.h>
#include "ctrl_loop.h"

namespace gr {
  namespace fastpsk {

    class mm_crec_impl : public mm_crec
    {
     private:
      int d_n;
      float d_sps;
      float d_maxdev;
      ctrl_loop ctrl;
      sc16 in1;
      float phase;
      float phase_inc;
      int debug;
      int counter;

     public:
      mm_crec_impl(int n, float sps, float loop_bw, float max_deviation);
      ~mm_crec_impl();

      static const int scale;

      void set_rate(float x);

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace fastpsk
} // namespace gr

#endif /* INCLUDED_FASTPSK_MM_CREC_IMPL_H */
