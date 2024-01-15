// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/Timer.h>
#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>
#include <units/time.h>

#include "subsystems/Drivetrain.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending Command
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class DriveTimeCommand
    : public frc2::CommandHelper<frc2::Command, DriveTimeCommand> {
 public:
  DriveTimeCommand() = default;
  DriveTimeCommand(double speed, units::second_t time, Drivetrain* subsystem);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  double m_speed;
  units::second_t m_duration;
  Drivetrain* m_drivetrain;
  frc::Timer m_timer;
};
