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

#include "prbs.h"

namespace gr {
  namespace fastpsk {
    std::vector<char> prbs(int order, int tap1, int tap2) {
        uint32_t mask = (1<<order)-1;
      	std::vector<char> seq(mask);
      	uint32_t a = mask;
      	for(int i = 0; i < seq.size(); i++) {
      		seq[i] = a & 1;
      		int b = (((a >> (tap1-1)) ^ (a >> (tap2-1))) & 1);
              	a = ((a << 1) | b);
      	}
      	return seq;
    }

    std::vector<char> prbs7()  {return prbs(7,  7,  6 );}
    std::vector<char> prbs9()  {return prbs(9,  9,  5 );}
    std::vector<char> prbs11() {return prbs(11, 11, 9 );}
    std::vector<char> prbs15() {return prbs(15, 15, 14);}
    std::vector<char> prbs20() {return prbs(20, 20, 3 );}

    std::vector<char> prbsx(int x) {
      switch(x) {
        case 7:  return prbs7();
        case 9:  return prbs9();
        case 11: return prbs11();
        case 15: return prbs15();
        case 20: return prbs20();
        default:;
      }
      return std::vector<char>();
    }
  }
}
