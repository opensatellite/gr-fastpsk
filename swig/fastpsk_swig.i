/* -*- c++ -*- */

#define FASTPSK_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "fastpsk_swig_doc.i"

%{
#include "fastpsk/agc.h"
#include "fastpsk/costas.h"
#include "fastpsk/mm_crec.h"
#include "fastpsk/qdelay.h"
#include "fastpsk/fir_filter_ssf.h"
#include "fastpsk/bert_sink.h"
#include "fastpsk/bert_source.h"
#include "fastpsk/deambiguity.h"
#include "fastpsk/npsk_slicer.h"
#include "fastpsk/deambiguity_cc.h"
#include "fastpsk/cf32_to_sc16.h"
#include "fastpsk/sc16_to_cf32.h"
#include "fastpsk/npsk_lockdet.h"
%}


%include "fastpsk/agc.h"
GR_SWIG_BLOCK_MAGIC2(fastpsk, agc);
%include "fastpsk/costas.h"
GR_SWIG_BLOCK_MAGIC2(fastpsk, costas);
%include "fastpsk/mm_crec.h"
GR_SWIG_BLOCK_MAGIC2(fastpsk, mm_crec);
%include "fastpsk/qdelay.h"
GR_SWIG_BLOCK_MAGIC2(fastpsk, qdelay);

%include "fastpsk/fir_filter_ssf.h"
GR_SWIG_BLOCK_MAGIC2(fastpsk, fir_filter_ssf);
%include "fastpsk/bert_sink.h"
GR_SWIG_BLOCK_MAGIC2(fastpsk, bert_sink);
%include "fastpsk/bert_source.h"
GR_SWIG_BLOCK_MAGIC2(fastpsk, bert_source);
%include "fastpsk/deambiguity.h"
GR_SWIG_BLOCK_MAGIC2(fastpsk, deambiguity);

%include "fastpsk/npsk_slicer.h"
GR_SWIG_BLOCK_MAGIC2(fastpsk, npsk_slicer);
%include "fastpsk/deambiguity_cc.h"
GR_SWIG_BLOCK_MAGIC2(fastpsk, deambiguity_cc);
%include "fastpsk/cf32_to_sc16.h"
GR_SWIG_BLOCK_MAGIC2(fastpsk, cf32_to_sc16);
%include "fastpsk/sc16_to_cf32.h"
GR_SWIG_BLOCK_MAGIC2(fastpsk, sc16_to_cf32);
%include "fastpsk/npsk_lockdet.h"
GR_SWIG_BLOCK_MAGIC2(fastpsk, npsk_lockdet);
