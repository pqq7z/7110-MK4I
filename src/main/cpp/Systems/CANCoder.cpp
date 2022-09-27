#include "Systems/CANCoder.h"
#include <wpi/numbers>

using namespace hb;

CANcode::CANcode(const int ID, const double offset) : CANCoder(ID), m_offset(offset) {
  ConfigSensorInitializationStrategy(BootToAbsolutePosition);
  ConfigMagnetOffset(offset);
  printf("CANCoder: %i, reading %5.2f\n", ID, GetAbsolutePosition());
}

void CANcode::SetDistancePerPulse(const double DPP) const {}

double CANcode::Get() {
  return (GetAbsolutePosition()/360.0) * 2.0 * wpi::numbers::pi - wpi::numbers::pi; 
}