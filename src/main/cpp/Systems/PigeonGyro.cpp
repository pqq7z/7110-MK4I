// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Systems/PigeonGyro.h"

using namespace ctre::phoenix::sensors;
using namespace FRC7110;

pigeonGyro::pigeonGyro(int ID) {
  pigeon = new ctre::phoenix::sensors::PigeonIMU(ID);
  pigeon->ConfigFactoryDefault();
}

double pigeonGyro::GetAngle() const {
  if (pigeon->GetState() == PigeonIMU::Ready) {
    PigeonIMU::FusionStatus stat;
    pigeon->GetFusedHeading(stat);
    m_angle = stat.heading;
  } 
  return -m_angle;
}

double pigeonGyro::GetRate() const {
  if (pigeon->GetState() == PigeonIMU::Ready) {
    double rate[3];
    pigeon->GetRawGyro(rate);
    m_rate = rate[2];
  } 
  return m_rate;
}

void pigeonGyro::Reset() {
  pigeon->SetFusedHeading(0, 30);
  m_angle = m_rate = 0;
}

void pigeonGyro::Calibrate() {} // Gyro::Calibrate() is pure virtual