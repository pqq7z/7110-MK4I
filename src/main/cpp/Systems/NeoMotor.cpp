#include "Systems/NeoMotor.h"
#include <wpi/numbers>

using namespace FRC7110;

NeoMotor::NeoMotor(const int ID, rev::CANSparkMax::MotorType Type)
: rev::CANSparkMax(ID, Type), rev::SparkMaxRelativeEncoder(GetEncoder()){}

void NeoMotor::SetDistancePerPulse(double DPP) const {}

double NeoMotor::GetRate() {
  return (GetVelocity()/60) * 1.0/6.75 * 2 * wpi::numbers::pi * 0.1016;
}