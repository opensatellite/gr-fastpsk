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


#ifndef INCLUDED_FASTPSK_MM_CREC_H
#define INCLUDED_FASTPSK_MM_CREC_H

#include <fastpsk/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace fastpsk {

    /*!
     * \brief <+description of block+>
     * \ingroup fastpsk
     *
     */
    class FASTPSK_API mm_crec : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<mm_crec> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of fastpsk::mm_crec.
       *
       * To avoid accidental use of raw pointers, fastpsk::mm_crec's
       * constructor is in a private implementation
       * class. fastpsk::mm_crec::make is the public interface for
       * creating new instances.
       */
      static sptr make(int n, float sps, float loop_bw, float max_deviation);
    };

  } // namespace fastpsk
} // namespace gr

#endif /* INCLUDED_FASTPSK_MM_CREC_H */
