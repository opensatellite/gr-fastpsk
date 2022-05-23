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

#ifndef INCLUDED_FASTPSK_BERT_SINK_IMPL_H
#define INCLUDED_FASTPSK_BERT_SINK_IMPL_H

#include <fastpsk/bert_sink.h>

namespace gr {
  namespace fastpsk {

    class bert_sink_impl : public bert_sink
    {
     private:
      int n;
      int d_order;
      std::vector<char> pn;
      int phase;
      bool sync;
      int sync_th;
      int loss_cnt;
      int loss_th;
      uint64_t errcnt;
      uint64_t bitcnt;
      uint64_t counter;
      uint64_t debug;
      double d_update_time;
      boost::posix_time::ptime d_last_update;

     public:
      bert_sink_impl(int order);
      ~bert_sink_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace fastpsk
} // namespace gr

#endif /* INCLUDED_FASTPSK_BERT_SINK_IMPL_H */
