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
#include "costas_impl.h"
#include "imath.h"
#include <gnuradio/expj.h>
#include <gnuradio/math.h>

namespace gr {
  namespace fastpsk {

    costas::sptr
    costas::make(int n, int order, float loop_bw, float max_deviation)
    {
      return gnuradio::get_initial_sptr
        (new costas_impl(n, order, loop_bw, max_deviation));
    }

    const int costas_impl::scale = 8192;

    /*
     * The private constructor
     */
    costas_impl::costas_impl(int n, int order, float loop_bw, float max_deviation)
      : gr::sync_block("costas",
              gr::io_signature::make(1, 1, sizeof(sc16)),
              gr::io_signature::make2(1, 2, sizeof(sc16), sizeof(float))),
              d_n(n),
              d_order(order),
              d_maxdev(max_deviation),
              ctrl(),
              phase(sc16(32767, 0)),
              phi(gr_complex(1, 0)),
              phase_inc(0),
              counter(0),
              debug(0)
    {
      char *debug_str = std::getenv("FASTPSK_DEBUG");
      if(debug_str) {
        debug = std::max(atoi(debug_str), 1024);
        std::cout << "costas: debug=" << debug << std::endl;
      }

      ctrl.set_rate(0.0f, d_maxdev);
      ctrl.set_bw(loop_bw, 1.0f);
      set_output_multiple(n);
    }

    /*
     * Our virtual destructor.
     */
    costas_impl::~costas_impl()
    {
    }

    void costas_impl::set_rate(float x) {
      ctrl.set_rate(x, d_maxdev);
    }

static inline int64_t err_calc(const sc16 *x, int n, int order) {
      static const int32_t K = 27146;  //(sqrt(2) - 1) * 65536
      int64_t err = 0;
      switch(order) {
        case 2:
          for(int i = 0; i < n; i++) {
            //int32_t ri = x[i].real() * x[i].imag();
            //err += (ri >> 14);
            err += ((x[i].real() >= 0) ? 1 : -1) * x[i].imag();
          }
          break;
        case 4:
          for(int i = 0; i < n; i++) {
            err += ((x[i].real() >= 0) ? 1 : -1) * x[i].imag() -
                   ((x[i].imag() >= 0) ? 1 : -1) * x[i].real();
          }
          break;
        case 8:
          for(int i = 0; i < n; i++) {
            if(std::abs(x[i].real()) >= std::abs(x[i].imag())) {
              int32_t rk = x[i].real() * K;
              int16_t rscaled = rk >> 16;
              err += ((x[i].real() >= 0 ? 1 : -1) * x[i].imag() -
                      (x[i].imag() >= 0 ? 1 : -1) * rscaled);
            } else {
              int32_t ik = x[i].imag() * K;
              int16_t iscaled = ik >> 16;
      	      err += ((x[i].real() >= 0 ? 1 : -1) * iscaled -
      		            (x[i].imag() >= 0 ? 1 : -1) * x[i].real());
            }
          }
          break;
        default:;
      }
      return err;
    }

    int
    costas_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const sc16 *in = (const sc16 *) input_items[0];
      sc16 *out = (sc16 *) output_items[0];
      float *errout = NULL;
      if(output_items.size() > 1)
        errout = (float *)output_items[1];

      // Do <+signal processing+>
      fc32_normalize(phi);
      for(int j = 0; j < noutput_items / d_n; j++) {
        //sc16 phase_rot = sc16_expj(-phase_inc);
        gr_complex rot = gr_expj(-phase_inc);
        for(int i = 0; i < d_n; i++) {
          //out[i].real(lroundf(in[i].real() * phi.real() - in[i].imag() * phi.imag()));
          //out[i].imag(lroundf(in[i].real() * phi.imag() + in[i].imag() * phi.real()));
          out[i].real(in[i].real() * phi.real() - in[i].imag() * phi.imag());
          out[i].imag(in[i].real() * phi.imag() + in[i].imag() * phi.real());
          fast_cc_multiply(phi, phi, rot);

          //fast_sc16_multiply(out[i], in[i], phase);
          //fast_sc16_multiply(phase, phase, phase_rot);
        }
        //sc16_normalize(phase, 32767.0f);

        int64_t err = err_calc(out, d_n, d_order);
        float ferr = err;
        ferr /= (scale * d_n);
        if(errout) {
          for(int i = 0; i < d_n; i++) {
            errout[i] = ferr;
          }
          errout += d_n;
        }

        phase_inc = ctrl.work(ferr);

        if(debug > 0) {
          counter++;
          if(counter >= debug) {
            counter = 0;
            std::cout << "costas: " << ferr << "," << phase_inc << std::endl;
          }
        }

        in += d_n;
        out += d_n;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace fastpsk */
} /* namespace gr */
