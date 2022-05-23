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

#ifndef INCLUDED_FASTPSK_IMATH_H
#define INCLUDED_FASTPSK_IMATH_H

#include <gnuradio/gr_complex.h>
#include <fastpsk/icomplex.h>
//#include <iostream>

namespace gr {
  namespace fastpsk {
    #define saturate(X, MIN, MAX) ((X) > (MAX) ? (MAX) : ((X) < (MIN) ? (MIN) : (X)))

    static inline void
    fast_cc_multiply(gr_complex& out, const gr_complex cc1, const gr_complex cc2)
    {
        // The built-in complex.h multiply has significant NaN/INF checking that
        // considerably slows down performance.  While on some compilers the
        // -fcx-limit-range flag can be used, this fast function makes the math consistent
        // in terms of performance for the Costas loop.
        float o_r, o_i;

        o_r = (cc1.real() * cc2.real()) - (cc1.imag() * cc2.imag());
        o_i = (cc1.real() * cc2.imag()) + (cc1.imag() * cc2.real());

        out.real(o_r);
        out.imag(o_i);
    }

    static inline void
    fast_sc16_multiply(sc16& out, const sc16 cc1, const sc16 cc2)
    {
        // The built-in complex.h multiply has significant NaN/INF checking that
        // considerably slows down performance.  While on some compilers the
        // -fcx-limit-range flag can be used, this fast function makes the math consistent
        // in terms of performance for the Costas loop.
        int32_t o_r, o_i;

        o_r = (cc1.real() * cc2.real()) - (cc1.imag() * cc2.imag());
        o_i = (cc1.real() * cc2.imag()) + (cc1.imag() * cc2.real());

        //std::cout << (o_r >> 15) << "," << (o_i >> 15) << std::endl;

        out.real(o_r >> 15);
        out.imag(o_i >> 15);
    }
    /* This bounds x by +/- clip without a branch */
    static inline float branchless_clip(float x, float clip)
    {
        return 0.5 * (std::abs(x + clip) - std::abs(x - clip));
    }

    static inline sc16 sc16_expj(float phase, float scale) {
        float re, im;
        ::sincosf(phase, &im, &re);
        //return sc16(lroundf(re * scale), lroundf(im * scale));
        re *= scale; im *= scale;
        return sc16(re, im);
    }

    static inline sc16 sc16_expj(float phase) {
        return sc16_expj(phase, 32767.0f);
    }

    void sc16_normalize(sc16& x, float scale);
    void fc32_normalize(gr_complex& x);

    float fastinvsqrt(float x);
    double fastpow(double a, double b);
    float fastpowf(float a, float b);
  }
}

#endif
