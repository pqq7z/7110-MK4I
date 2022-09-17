#include "Systems/CANCoder.h"

using namespace FRC7110;

CANcode::CANcode(const int ID, const double offset) : CANCoder(ID), m_offset(offset){
  ConfigSensorInitializationStrategy(BootToAbsolutePosition);
  ConfigMagnetOffset(offset);
  printf("CANCoder: %i, reading %5.2f\n", ID, GetAbsolutePosition());
}

void CANcode::SetDistancePerPulse(const double DPP) const {}

double CANcode::Get() {
  double radPos = (GetAbsolutePosition()/360) * 2 * wpi::numbers::pi - wpi::numbers::pi;
  return radPos; 
}