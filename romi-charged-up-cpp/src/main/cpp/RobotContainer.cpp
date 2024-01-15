// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/button/Trigger.h>

#include "commands/Autos.h"
#include "commands/ExampleCommand.h"

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
  m_drivetrain = Drivetrain();
  m_driveTimeCommand = DriveTimeCommand(0.5, units::second_t{3}, &m_drivetrain);

  // Configure the button bindings
  ConfigureBindings();
}

void RobotContainer::ConfigureBindings() {
  // Setting default command of m_drivetrain
  m_drivetrain.SetDefaultCommand(this->GetArcadeDriveCommand());
  
  // Configure your trigger bindings here

  // Schedule `ExampleCommand` when `exampleCondition` changes to `true`
  frc2::Trigger([this] {
    return m_subsystem.ExampleCondition();
  }).OnTrue(ExampleCommand(&m_subsystem).ToPtr());

  // Schedule `ExampleMethodCommand` when the Xbox controller's B button is
  // pressed, cancelling on release.
  m_driverController.B().OnTrue(this->GetDriveUntilDistCommand(units::meter_t(0.5)));
  m_driverController.A().OnTrue(&this->m_driveTimeCommand);


}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return autos::ExampleAuto(&m_subsystem);
}

frc2::CommandPtr RobotContainer::GetArcadeDriveCommand() {
  // RunCommand(std::function<void()> toRun, Requirements req = {})
  // Requirements(std::initializer_list<Subsystem*> reqs)
  return frc2::RunCommand(
    [this] {
      m_drivetrain.ArcadeDrive(
        -m_driverController.GetLeftY(),
        m_driverController.GetRightX());
    },
    {&m_drivetrain}
  ).ToPtr();
}

frc2::CommandPtr RobotContainer::GetDriveUntilDistCommand(units::meter_t dist) {
  // requires 4 arguments
  return frc2::FunctionalCommand(
    // initialize
    [this] { m_drivetrain.ResetEncoders(); },

    // execute
    [this] { m_drivetrain.ArcadeDrive(0.5, 0); },

    // end
    [this] (bool interrupted) { m_drivetrain.ArcadeDrive(0, 0); },

    // isfinished
    [this, dist] { return m_drivetrain.GetAverageDistance() >= dist; },

    // subsystems required
    {&m_drivetrain}
  ).ToPtr();

}
