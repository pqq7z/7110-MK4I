#pragma once

#include <ctre/phoenix.h>
#include <wpi/numbers>
#include <string>

class CANcode {
    public:
        explicit CANcode(const int id, std::string str, const double offset) : m_Encoder(id, str), m_offset(offset){};
        //string is because cancoder wants the name of bus. I think this can be found on Phoenix tuner

        void SetDistancePerPulse(const double DPP){}

        double Get() {

            double degPos = m_Encoder.GetPosition() - m_offset;

            double radPos = (degPos/360)* 2 * wpi::numbers::pi - wpi::numbers::pi;

            return radPos; 
        }

    private:
        CANCoder m_Encoder;

        const double m_offset;
};