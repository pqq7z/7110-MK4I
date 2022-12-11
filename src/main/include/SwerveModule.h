// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/Encoder.h>
#include <frc/controller/PIDController.h>
#include <frc/controller/ProfiledPIDController.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/kinematics/SwerveModuleState.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <units/angular_velocity.h>
#include <units/time.h>
#include <units/velocity.h>
#include <units/voltage.h>
#include <wpi/numbers>

#include "Systems/NeoMotor.h"
#include "Systems/CANCoder.h"

class SwerveModule {
 public:
  SwerveModule(int driveMotorChannel, int turningMotorChannel,
               int turningEncoderChannel, double offset);
  frc::SwerveModuleState GetState();
  void SetDesiredState(const frc::SwerveModuleState& state);

 private:
  static constexpr double kWheelRadius = 0.1016;
  static constexpr int kEncoderResolution = 4096;

  static constexpr auto kModuleMaxAngularVelocity =
      wpi::numbers::pi * 1_rad_per_s;  // radians per second
  static constexpr auto kModuleMaxAngularAcceleration =
      wpi::numbers::pi * 2_rad_per_s / 1_s;  // radians per second^2

  hb::NeoMotor m_driveMotor;
  hb::NeoMotor m_turningMotor;
  hb::CANcode m_turningEncoder;

  double m_drivechannel;

  frc2::PIDController m_drivePIDController{0.5, 0.01, 0.005};
  frc::ProfiledPIDController<units::radians> m_turningPIDController{
      1.0,
      0.0,
      0.0,
      {kModuleMaxAngularVelocity, kModuleMaxAngularAcceleration}};
    
    // static value was arrived to through testing, its the minimum voltage for motors to move. 
    // velocity value is calculated by taking the maximum voltage of the motor(12) and dividing it by the maximum speed
    // this essential means that for every 2.67 volts, the motor should be pushing the robot at 1 mps
    frc::SimpleMotorFeedforward<units::meters> m_driveFeedforward{0.1_V, 2.67_V / 1_mps}; 

};
