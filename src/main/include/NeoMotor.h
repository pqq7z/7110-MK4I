#pragma once

#include <rev/CANSparkMax.h>
#include <wpi/numbers>

class NeoMotor {
    public:
        explicit NeoMotor(const int ID, rev::CANSparkMax::MotorType Type) : m_Neo(ID, Type){};

        void SetDistancePerPulse(double DPP){}

        auto GetRate() {
            
            auto mps = (m_Encoder.GetVelocity()/60) * 1/6.75 * 2 * wpi::numbers::pi * 0.1016;

            // mps = motor rpm /60 (to make rps) * 1/6.75 (to account for gear ratio) * 2pi * 0.1016 (for wheel size)

            return mps;
        }

        void SetVoltage(units::volt_t Voltage) {
            m_Neo.SetVoltage(Voltage);
        }

    private:
        rev::CANSparkMax m_Neo;

        rev::SparkMaxRelativeEncoder m_Encoder = m_Neo.GetEncoder();
}; //This Is only for the Driving Motor
