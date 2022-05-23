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


#ifndef INCLUDED_FASTPSK_DEAMBIGUITY_CC_H
#define INCLUDED_FASTPSK_DEAMBIGUITY_CC_H

#include <fastpsk/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace fastpsk {

    /*!
     * \brief <+description of block+>
     * \ingroup fastpsk
     *
     */
    class FASTPSK_API deambiguity_cc : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<deambiguity_cc> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of fastpsk::deambiguity_cc.
       *
       * To avoid accidental use of raw pointers, fastpsk::deambiguity_cc's
       * constructor is in a private implementation
       * class. fastpsk::deambiguity_cc::make is the public interface for
       * creating new instances.
       */
      static sptr make(int npsk, bool swap, bool diff);

      virtual void set_phase(int x) = 0;
      virtual void set_swap(bool en) = 0;
    };

  } // namespace fastpsk
} // namespace gr

#endif /* INCLUDED_FASTPSK_DEAMBIGUITY_CC_H */
