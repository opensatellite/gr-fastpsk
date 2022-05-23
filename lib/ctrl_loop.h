#ifndef INCLUDED_FASTPSK_CTRL_LOOP_H
#define INCLUDED_FASTPSK_CTRL_LOOP_H

namespace gr {
  namespace fastpsk {

    class ctrl_loop {
      private:
        float rate;
        float rate_min;
        float rate_max;
        float kp;
        float ki;

      public:
        ctrl_loop();
        void set_rate(float _rate);
        void set_rate(float _rate, float dev);
        void set_bw(float bw, float damp);
        //usage: adj = ctrl_loop_work(&c, err);
        float work(float err); //return instant rate
    };

  }
}

#endif
