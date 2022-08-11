#pragma once

#include <ctre/phoenix.h>
#include <wpi/numbers>

namespace FRC7110{
    class CANcode {
        public:
            explicit CANcode(const int id, const double offset) : m_ID(id), m_offset(offset){};
            //string is because cancoder wants the name of bus. I think this can be found on Phoenix tuner

            void SetDistancePerPulse(const double DPP){}

            double Get() {

                double degPos = m_Encoder.GetPosition() - m_offset;

                double radPos = (degPos/360)* 2 * wpi::numbers::pi - wpi::numbers::pi;

                return radPos; 
            }

        private:
            const int m_ID;

            CANCoder m_Encoder{m_ID};

            const double m_offset;
    };
} //namespace FRC7110