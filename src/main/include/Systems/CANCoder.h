#pragma once

#include <ctre/phoenix.h>

namespace FRC7110 {
  
  class CANcode : public CANCoder {
  
    public:
      
      explicit CANcode(const int id, const double offset);

      void SetDistancePerPulse(const double DPP) const;

      double Get();
    
    private:

      const double m_offset;
  };
} // namespace FRC7110