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
#include "interpolator_taps_i.h"
#include "mm_crec_impl.h"
#include "imath.h"

#include <cstdio>

namespace gr {
  namespace fastpsk {

    mm_crec::sptr
    mm_crec::make(int n, float sps, float loop_bw, float max_deviation)
    {
      return gnuradio::get_initial_sptr
        (new mm_crec_impl(n, sps, loop_bw, max_deviation));
    }

    const int mm_crec_impl::scale = 8192;

    /*
     * The private constructor
     */
    mm_crec_impl::mm_crec_impl(int n, float sps, float loop_bw, float max_deviation)
      : gr::block("mm_crec",
              gr::io_signature::make(1, 1, sizeof(sc16)),
              gr::io_signature::make2(1, 2, sizeof(sc16), sizeof(float))),
              d_n(n),
              d_sps(sps),
              d_maxdev(max_deviation),
              ctrl(),
              in1(sc16(0, 0)),
              phase(0),
              phase_inc(sps),
              counter(0),
              debug(0)
    {
      char *debug_str = std::getenv("FASTPSK_DEBUG");
      if(debug_str) {
        debug = std::max(atoi(debug_str), 1024);
        std::cout << "mm_crec: debug=" << debug << std::endl;
      }

      set_output_multiple(d_n);
      set_relative_rate (1.0 / sps);
      ctrl.set_rate(sps, max_deviation);
      ctrl.set_bw(loop_bw, 1.0f);
    }

    /*
     * Our virtual destructor.
     */
    mm_crec_impl::~mm_crec_impl()
    {
    }

    void mm_crec_impl::set_rate(float x) {
      ctrl.set_rate(x, d_maxdev);
    }

    void
    mm_crec_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      unsigned ninputs = ninput_items_required.size();
      for(unsigned i=0; i < ninputs; i++)
	      ninput_items_required[i] = (int) ceil((noutput_items * d_sps) + hb_ntaps);
    }

static inline sc16 filter(const int hb_taps[], const sc16 *x, int n)
{
  sc16 out;
  int64_t re = 0, im = 0;
  for(int i = 0; i < n; i++) {
    re += hb_taps[i] * x[i].real();
    im += hb_taps[i] * x[i].imag();
  }
  out.real(re >> 15);
  out.imag(im >> 15);
  return out;
}

#define SLICE(X)  (((X) < 0) ? -1 : 1)

//x0 = latest sample, x1 = old sample
static inline int64_t err_calc(sc16 x0, sc16 x1) {
  int64_t re = SLICE(x1.real()) * x0.real() - SLICE(x0.real()) * x1.real();
  int64_t ie = SLICE(x1.imag()) * x0.imag() - SLICE(x0.imag()) * x1.imag();
  //printf("%d,%d,%d\n", re, ie, re+ie);
  return re+ie;
}

    int
    mm_crec_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const sc16 *in = (const sc16 *) input_items[0];
      sc16 *out = (sc16 *) output_items[0];
      float *errout = NULL;
      if(output_items.size() > 1)
        errout = (float *)output_items[1];

      int ii = 0;
      int oo = 0;
      int ni = ninput_items[0] - hb_ntaps;

      for(oo = 0; oo < noutput_items / d_n; oo++) {
        float newphase = phase + d_n * phase_inc;
        int inewphase = newphase;
        if(ii + inewphase >= ni) {
          //std::cout << "mm_crec: ii = " << ii << ", ni = " << ni << std::endl;
          break;
        }

        //printf("phase=%f, inc=%f, ", phase, phase_inc);
        for(int i = 0; i < d_n; i++) {
          float phase1 = phase + i * phase_inc;
          unsigned idx = phase1 * hb_nsteps;
          unsigned iidx = idx >> 7;
          unsigned fidx = idx & 127;
          //std::cout << "fidx = " << fidx << ", iidx = " << iidx << std::endl;
          out[i] = filter(hb_taps[hb_nsteps - 1 - fidx], &in[iidx], hb_ntaps);
        }
        phase = fmodf(newphase, 1.0f);

        //printf("out[0]=(%d,%d), ", out[0].real(), out[0].imag());
        int64_t err = err_calc(out[0], in1);
        for(int i = 1; i < d_n; i++) {
          err += err_calc(out[i], out[i-1]);
        }
        in1 = out[d_n - 1];
        float ferr = err;
        ferr /= (scale * d_n);

        if(errout) {
          for(int i = 0; i < d_n; i++) {
            errout[i] = ferr;
          }
          errout += d_n;
        }
        phase_inc = saturate(ctrl.work(ferr), 0, d_sps*2);

        if(debug > 0) {
          counter++;
          if(counter >= debug) {
            counter = 0;
            std::cout << "mm_crec: " << ferr << "," << phase_inc << "," << phase << std::endl;
          }
        }

        in += inewphase;
        out += d_n;
        ii += inewphase;
      }

      consume_each(ii);
      return oo * d_n;
    }

  } /* namespace fastpsk */
} /* namespace gr */
