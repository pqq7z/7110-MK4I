#pragma once

#include <ctre/phoenix.h>
#include <wpi/numbers>
#include <string>

#if 1
#define _CONFIG_0_ //to make switching between these easier
namespace FRC7110{
    class CANcode {
        public:
            explicit CANcode(const int id, std::string busName, const double offset) : m_Encoder(id, busName), m_offset(offset){};
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
}//namespace FRC7110
#else
#define _CONFIG_1_
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
}//namespace FRC7110
#endif