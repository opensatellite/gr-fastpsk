#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "imath.h"
#include "ctrl_loop.h"

namespace gr {
  namespace fastpsk {

    ctrl_loop::ctrl_loop() :
      rate(0),
      rate_min(0),
      rate_max(0),
      kp(0),
      ki(0)
    {}

    void ctrl_loop::set_rate(float _rate)
    {
      rate = _rate;
    }

    void ctrl_loop::set_rate(float _rate, float dev)
    {
    	rate = _rate;
    	rate_min = rate - dev;
    	rate_max = rate + dev;
    }

    void ctrl_loop::set_bw(float bw, float damp)
    {
    	float denom = (1.0 + 2.0*damp*bw + bw*bw);
    	kp = (4*damp*bw) / denom;
    	ki = (4*bw*bw) / denom;
    }

    float ctrl_loop::work(float err)
    {
      rate = saturate(rate + ki * err, rate_min, rate_max);
      return rate + kp * err;
    }

  }
}
