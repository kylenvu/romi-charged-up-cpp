// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TeleopArcadeDrive.h"

TeleopArcadeDrive::TeleopArcadeDrive(
  Drivetrain* subsystem,
  std::function<double()> xAxisSupplier,
  std::function<double()> zAxisSupplier)
  : m_drivetrain{subsystem},
    xAxisSupplier{xAxisSupplier},
    zAxisSupplier{zAxisSupplier} {
  
  /*
  // constructor uniform initialization is equivalent to below
  this->m_drivetrain = subsystem;
  this->xAxisSupplier = xAxisSupplier;
  this->zAxisSupplier = zAxisSupplier;
  */

  // Use addRequirements() here to declare subsystem dependencies.
  this->AddRequirements(subsystem);
}

// Called when the command is initially scheduled.
void TeleopArcadeDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TeleopArcadeDrive::Execute() {
  m_drivetrain->ArcadeDrive(xAxisSupplier(), zAxisSupplier());

  // () operator invokes the std::function (aka lambda)
}

// Called once the command ends or is interrupted.
void TeleopArcadeDrive::End(bool interrupted) {}

// Returns true when the command should end.
bool TeleopArcadeDrive::IsFinished() {
  return false;
}
