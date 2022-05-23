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

#include "imath.h"

namespace gr {
  namespace fastpsk {

    float fastinvsqrt(float x)
    {
        float y;
        asm
        (
            "rsqrtss %[x], %%xmm0;"   // EVAL rsqrtss of "x" and store result in xmm0
            "movss %%xmm0, %[y];"     // LOAD value from xmm0 into y
            :
            : [ x ] "m" ( x ),
              [ y ] "m" ( y )
              /*[ [asmSymbolicName] ] constraint (cvariablename)
                                         'm' -- memory operand
              */
            : "xmm0"
        );
        return y;
    }

    float fastpowf(float a, float b)
    {
        union {
            float    f;
            uint32_t u;
        } temp;
        temp.f = a;
        temp.u = (uint32_t)(b * (float)(temp.u - 1064866808) + 1064866808);
        return temp.f;
    }

    double fastpow(double a, double b)
    {
        union { double d; long long x; } u = { a };
        u.x = (long long)(b * (u.x - 4607182418800017409LL) + 4606794787981043020LL);
        return u.d;
    }

    void sc16_normalize(sc16& x, float scale) {
        int32_t re2 = x.real() * x.real();
        int32_t im2 = x.imag() * x.imag();
        float magsqr = re2 + im2;
        float mag = fastinvsqrt(magsqr);
        //x.real(lroundf(x.real() * mag * scale));
        //x.imag(lroundf(x.imag() * mag * scale));
        x.real(x.real() * mag * scale);
        x.imag(x.imag() * mag * scale);
    }

    void fc32_normalize(gr_complex& x) {
        float magsqr = x.real() * x.real() + x.imag() * x.imag();
        float mag = fastinvsqrt(magsqr);
        x.real(x.real() * mag);
        x.imag(x.imag() * mag);
    }
  }
}
