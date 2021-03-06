#pragma once
#include "dsp/buffer.hpp"
#include "headers\enums.hpp"
#include <vector>

namespace YSE {
  namespace PATCHER {

    class pObject;
    struct inlet;

    

    struct outlet {
      outlet(pObject * obj, OUT_TYPE type);
      ~outlet();

      inline OUT_TYPE Type() const { return type; } 

      void SendBang();
      void SendFloat(float value);
      void SendBuffer(DSP::buffer * value);

      void Connect(inlet * in);
      void Disconnect(inlet * in);

    private:
      pObject * obj;
      OUT_TYPE type;

      std::vector<inlet*> connections;
    };

  }
}