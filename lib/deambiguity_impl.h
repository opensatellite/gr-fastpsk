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

#ifndef INCLUDED_FASTPSK_DEAMBIGUITY_IMPL_H
#define INCLUDED_FASTPSK_DEAMBIGUITY_IMPL_H

#include <fastpsk/deambiguity.h>
#include <fastpsk/icomplex.h>

namespace gr {
  namespace fastpsk {

    class deambiguity_impl : public deambiguity
    {
     private:
      std::vector<sc16> rotate;
      sc16 d_phase;
      bool d_swap;
      bool d_diff;

     public:
      deambiguity_impl(int npsk, bool swap, bool diff);
      ~deambiguity_impl();

      static const int scale;
      static const int shift;

      void set_phase(int x);
      void set_swap(bool en);

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace fastpsk
} // namespace gr

#endif /* INCLUDED_FASTPSK_DEAMBIGUITY_IMPL_H */
