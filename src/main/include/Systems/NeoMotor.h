#pragma once

#include <rev/CANSparkMax.h>

namespace FRC7110 {
  
  class NeoMotor : public rev::CANSparkMax, public rev::SparkMaxRelativeEncoder {

    public:

      explicit NeoMotor(const int ID, rev::CANSparkMax::MotorType Type);
      
      void SetDistancePerPulse(double DPP) const;
      
      double GetRate();

  };
} // namespace FRC7110
