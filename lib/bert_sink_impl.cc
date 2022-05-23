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
#include "bert_sink_impl.h"
#include "prbs.h"

namespace gr {
  namespace fastpsk {

    bert_sink::sptr
    bert_sink::make(int order)
    {
      return gnuradio::get_initial_sptr
        (new bert_sink_impl(order));
    }

    /*
     * The private constructor
     */
    bert_sink_impl::bert_sink_impl(int order)
      : gr::sync_block("bert_sink",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(0, 0, 0)),
              d_order(order),
              phase(0),
              sync(false),
              loss_cnt(0),
              errcnt(0),
              bitcnt(0),
              counter(0),
              debug(0),
              d_update_time(1000.0),
              d_last_update(boost::posix_time::min_date_time)
    {
      char *debug_str = std::getenv("FASTPSK_DEBUG");
      if(debug_str) {
        debug = std::max(atoi(debug_str), 1024);
        std::cout << "bert: debug=" << debug << std::endl;
      }

      message_port_register_out(pmt::mp("ber"));

      pn = prbsx(order);

      n = 128;
      sync_th = n * 9 / 10; //sync thresh: 90% of 128
      loss_th = n / 2;      //loss thresh: 50% of 128
      set_output_multiple(n);
    }

    /*
     * Our virtual destructor.
     */
    bert_sink_impl::~bert_sink_impl()
    {
    }

    int
    bert_sink_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];

      // Do <+signal processing+>
      for(int i = 0; i < noutput_items / n; i++) {
        int accum = 0;
        //error test
        for(int j = 0; j < n; j++) {
          accum += in[j] ^ pn[phase];
          phase++;
          if(phase >= pn.size()) {
            phase = 0;
          }
        }
        in += n;
        //sync test
        if(sync) {
          if(accum >= loss_th) {
            sync = false;
          }
          errcnt += accum;
          bitcnt += n;
        } else {
          if(accum <= n - sync_th) {
            sync = true;
            errcnt = 0;
            bitcnt = 0;
          } else {
            phase++;
            if(phase >= pn.size()) {
              phase = 0;
            }
          }
        }
        //debug print
        if(debug > 0) {
          counter+=n;
          if(counter >= debug) {
            counter = 0;
            if(sync) {
              double ber = bitcnt > 0 ? (double)errcnt / bitcnt : 0.0;
              std::cout << "bert: ber=" << ber << ", errs=" << errcnt << ", bits=" << bitcnt << std::endl;
            } else {
              std::cout << "bert: sync loss, phase=" << phase << std::endl;
            }
          }
        }
      }

      boost::posix_time::ptime now(
                  boost::posix_time::microsec_clock::local_time());
      boost::posix_time::time_duration diff = now - d_last_update;
      if (diff.total_milliseconds() > d_update_time)
      {
          d_last_update = now;
          double ber = bitcnt > 0 ? (double)errcnt / bitcnt : 0.0;
          pmt::pmt_t d = pmt::make_dict();
          d = pmt::dict_add(d, pmt::mp("sync_lock"),  pmt::mp(sync));
          if(sync) {
            d = pmt::dict_add(d, pmt::mp("error_bits"), pmt::mp(errcnt));
            d = pmt::dict_add(d, pmt::mp("total_bits"), pmt::mp(bitcnt));
            d = pmt::dict_add(d, pmt::mp("ber"), pmt::mp(ber));
          }
          message_port_pub(pmt::mp("ber"), pmt::cons(d, pmt::PMT_NIL));
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace fastpsk */
} /* namespace gr */
