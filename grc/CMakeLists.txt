# Copyright 2011 Free Software Foundation, Inc.
#
# This file was generated by gr_modtool, a tool from the GNU Radio framework
# This file is a part of gr-fastpsk
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
install(FILES
    fastpsk_agc.xml
    fastpsk_costas.xml
    fastpsk_mm_crec.xml
    fastpsk_qdelay.xml
    fastpsk_fir_filter_ssf.xml
    fastpsk_bert_sink.xml
    fastpsk_bert_source.xml
    fastpsk_deambiguity.xml
    fastpsk_npsk_slicer.xml
    fastpsk_deambiguity_cc.xml
    fastpsk_cf32_to_sc16.xml
    fastpsk_sc16_to_cf32.xml
    fastpsk_npsk_lockdet.xml DESTINATION share/gnuradio/grc/blocks
)
