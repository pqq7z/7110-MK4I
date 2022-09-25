#pragma once

#include <frc/interfaces/Gyro.h>
#include <ctre/phoenix/sensors/PigeonIMU.h>

namespace FRC7110 {

  class pigeonGyro : public frc::Gyro {
  public:
    explicit pigeonGyro(int ID);

    double GetAngle() const override;

    double GetRate() const override;

    void Reset() override;

    void Calibrate() override;

  private:
    ctre::phoenix::sensors::PigeonIMU* pigeon;
    mutable double m_angle;
    mutable double m_rate;
  };
} // namespace FRC7110
