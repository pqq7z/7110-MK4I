// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/MathUtil.h>
#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/filter/SlewRateLimiter.h>
#include <frc/Timer.h>
#include <wpi/numbers>

#include "Drivetrain.h"

class Robot : public frc::TimedRobot {
  public:
    void AutonomousInit() override {
      printf("-----------------------------------------------\n");
      timer.Reset();
      timer.Start();
    }

    void AutonomousPeriodic() override {
    #if 1
    if(timer.Get() <= 1_s) 
      m_swerve.Drive(0_mps, 0_mps, units::radians_per_second_t(wpi::numbers::pi), true);
    else
      m_swerve.Drive(0_mps, 0_mps, units::radians_per_second_t(0), false);
    #else
      if (timer.Get() <= 1.5_s) m_swerve.Drive(2_mps, 0_mps, units::radians_per_second_t(0), false);
      else  m_swerve.Drive(0_mps, 0_mps, units::radians_per_second_t(0), false);
    #endif
    // m_swerve.UpdateOdometry();
}

  void RobotInit() override { 
    printf("7110-MK4I-2 v0.4 %s %s\n ", __DATE__, __TIME__);
  }
 
  void TeleopPeriodic() override { DriveWithJoystick(true); }

 private:
  frc::XboxController m_controller{0};
  Drivetrain m_swerve;
  frc::Timer timer;

  // Slew rate limiters to make joystick inputs more gentle; 1/3 sec from 0
  // to 1.
  frc::SlewRateLimiter<units::scalar> m_xspeedLimiter{3 / 1_s};
  frc::SlewRateLimiter<units::scalar> m_yspeedLimiter{3 / 1_s};
  frc::SlewRateLimiter<units::scalar> m_rotLimiter{3 / 1_s};

  void DriveWithJoystick(bool fieldRelative) {
    // Get the x speed. We are inverting this because Xbox controllers return
    // negative values when we push forward.
    const auto xSpeed = -m_xspeedLimiter.Calculate(
                            frc::ApplyDeadband(m_controller.GetLeftY(), 0.2)) *
                        Drivetrain::kMaxSpeed;

    // Get the y speed or sideways/strafe speed. We are inverting this because
    // we want a positive value when we pull to the left. Xbox controllers
    // return positive values when you pull to the right by default.
    const auto ySpeed = m_yspeedLimiter.Calculate(
                            frc::ApplyDeadband(m_controller.GetLeftX(), 0.2)) *
                        Drivetrain::kMaxSpeed;

    // Get the rate of angular rotation. We are inverting this because we want a
    // positive value when we pull to the left (remember, CCW is positive in
    // mathematics). Xbox controllers return positive values when you pull to
    // the right by default.
    const auto rot = m_rotLimiter.Calculate(
                         frc::ApplyDeadband(m_controller.GetRightX(), 0.2)) *
                     Drivetrain::kMaxAngularSpeed;

    m_swerve.Drive(xSpeed, ySpeed, rot, fieldRelative);
  }
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
