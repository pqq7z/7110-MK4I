#include "Systems/NeoMotor.h"
#include <wpi/numbers>

using namespace hb;

NeoMotor::NeoMotor(const int ID, rev::CANSparkMax::MotorType Type)
: rev::CANSparkMax(ID, Type), rev::SparkMaxRelativeEncoder(GetEncoder()), m_ID(ID){
  SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
}

void NeoMotor::SetDistancePerPulse(double DPP) const {}

double NeoMotor::GetRate() {
  // if (m_ID == 6) printf("%d: %5.2f\n", m_ID, ((GetVelocity()/60) * 1.0/6.75 * 2 * wpi::numbers::pi * 0.05092958));
  return ((GetVelocity()/60) * (1.0/6.75) * wpi::numbers::pi * 2 * 0.05092958);
}