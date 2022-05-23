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

#ifndef INCLUDED_FASTPSK_PRBS_H
#define INCLUDED_FASTPSK_PRBS_H

#include <stdint.h>
#include <vector>

namespace gr {
  namespace fastpsk {
    std::vector<char> prbs(int order, int tap1, int tap2);
    std::vector<char> prbsx(int x);
    std::vector<char> prbs7();
    std::vector<char> prbs9();
    std::vector<char> prbs11();
    std::vector<char> prbs15();
    std::vector<char> prbs20();
  }
}

#endif
