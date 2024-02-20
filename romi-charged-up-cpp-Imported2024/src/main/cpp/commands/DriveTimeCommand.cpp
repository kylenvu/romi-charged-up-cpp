// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/DriveTimeCommand.h"

DriveTimeCommand::DriveTimeCommand(double speed, units::second_t time, Drivetrain* subsystem)
  : m_speed{speed},
    m_duration{time},
    m_drivetrain{subsystem} {
  
  // Apparently this isn't needed; maybe the "zero-state" is a valid state
  // m_timer = frc::Timer();
  // E.g., empty std::vector is set to null so when you call push_back(),
  // it will initialize the vector and then push_back the data

  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(subsystem);
}

// Called when the command is initially scheduled.
void DriveTimeCommand::Initialize() {
  m_timer.Start();
  m_drivetrain->ArcadeDrive(0, 0);
}

// Called repeatedly when this Command is scheduled to run
void DriveTimeCommand::Execute() {
  m_drivetrain->ArcadeDrive(m_speed, 0);
}

// Called once the command ends or is interrupted.
void DriveTimeCommand::End(bool interrupted) {
  m_drivetrain->ArcadeDrive(0, 0);
  m_timer.Stop();
  m_timer.Reset();
}

// Returns true when the command should end.
bool DriveTimeCommand::IsFinished() {
  return m_timer.HasElapsed(m_duration);
}
