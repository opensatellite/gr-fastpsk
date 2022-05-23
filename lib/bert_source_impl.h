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

#ifndef INCLUDED_FASTPSK_BERT_SOURCE_IMPL_H
#define INCLUDED_FASTPSK_BERT_SOURCE_IMPL_H

#include <fastpsk/bert_source.h>
#include "prbs.h"

namespace gr {
  namespace fastpsk {

    class bert_source_impl : public bert_source
    {
     private:
      std::vector<char> pn;
      int phase;

     public:
      bert_source_impl(int order);
      ~bert_source_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace fastpsk
} // namespace gr

#endif /* INCLUDED_FASTPSK_BERT_SOURCE_IMPL_H */
