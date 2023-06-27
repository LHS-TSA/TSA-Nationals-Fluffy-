#include "main.h"
#include <cmath>
#include <sstream>
// parameters are 2 lettes, first letter defines weather its front(f) or back(b)
// the second letter defines left(l) or right(r).
//pros::IMU gyro(20);
float ratio = 600.0/127.0;
void setDrive(float left, float right)
{
  front_left_drive.move_velocity(left);
  back_left_drive.move_velocity(left);
  back_left_drive_top.move_velocity(left);
  front_right_drive.move_velocity(right);
  back_right_drive.move_velocity(right);
  back_right_drive_top.move_velocity(right);
}

void setDriveMotors()
{
   float power_L = (con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
   float power_R = (con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
   float L  = power_L; 
   float R  = power_R;
   setDrive(L * ratio, R * ratio);
}

void setIntake(int power)
{
  intake.move_velocity(power);
}

int hold_power = 0;
void setIntakeMotors()
{
  if(con.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
  {
      hold_power = 600;
  }
  else if (con.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
  {
      hold_power = -600;
  }
  else if (con.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
  {
    hold_power = 0;
  }
  setIntake(hold_power);
}

void stop()
{
  setDrive(0,0);
}
// true = clockwise ++, false = counter clockwise --

void rotateToAngle(float targetAngle, bool direction)
{
  
  if(direction){
    
    float currentHeading = gyro.get_heading();
    float angleDifference = 10;
    float initialDifference;
    if (targetAngle < 180 && currentHeading > 180 && currentHeading < 359.999)
    {
      initialDifference = fabs(currentHeading - 360) + targetAngle;
    }else{
      initialDifference = fabs(targetAngle - currentHeading);
    }
    
      while(angleDifference > 1){
      currentHeading = gyro.get_heading();
      if (targetAngle < 180 && currentHeading > 180 && currentHeading < 359.999)
      {
        angleDifference = fabs(currentHeading - 360) + targetAngle;
      }else{
          angleDifference = fabs(targetAngle - currentHeading);
        }

        float drivepower = 150 * (angleDifference / initialDifference);
        if(drivepower < 45){
          drivepower = 45;
        }
        // con.print(0,0,"%d", (int)drivepower);
        
        setDrive(drivepower, -drivepower);
        con.print(0, 8, "%d/%d", initialDifference, angleDifference);
      }
      con.print(0,0, "%d", (int)gyro.get_heading());
      stop();
  }else{
      float currentHeading = gyro.get_heading();
      float angleDifference = 10;
      float initialDifference;
      if (targetAngle > 180 && currentHeading < 180 && currentHeading >= 0)
      {
        initialDifference = fabs(currentHeading - 360) + targetAngle;
      }
      else
      {
        initialDifference = fabs(targetAngle - currentHeading);
      }

      while (angleDifference > 1)
      {
        currentHeading = gyro.get_heading();
        if (targetAngle > 180 && currentHeading < 180 && currentHeading >= 0)
        {
          angleDifference = fabs(currentHeading - 360) + targetAngle;
        }
        else
        {
          angleDifference = fabs(targetAngle - currentHeading);
        }

        float drivepower = 150 * (angleDifference / initialDifference);
        if (drivepower < 25)
        {
          drivepower = 25;
        }
        // con.print(0,0,"%d", (int)drivepower);

        setDrive(-drivepower, drivepower);
        con.print(0, 8, "%d/%d", initialDifference, angleDifference);
      }
      con.print(0, 0, "%d", (int)gyro.get_heading());
      stop();
  }
//   bool cc = false;
//   // Determine the current heading
//   float currentHeading = gyro.get_heading();
//   float angleDifference = fabs(targetAngle - currentHeading);
//   float initialDifference = angleDifference;
//   // Calculate the difference between the current and target angles
//   if (360 - (targetAngle + 180) < 0)
//   {
//     cc = true;
//     initialDifference = fabs(targetAngle - currentHeading + 360);
//     con.print(1,0,"hi");
//   }
  
//   // Set the desired drive power based on the angle difference
//   float drivePower = 600 * (angleDifference / initialDifference);
  
  
//   con.clear();
//   // Rotate until the angle difference is within the acceptable range
//   while (angleDifference > 1)
//   {
    
    
//     pros::delay(10);
//     if(!cc){
//       setDrive(drivePower, -drivePower);
//     }else{
//       setDrive(-drivePower, drivePower);
//     }
//     // Update the current heading and angle difference
//     currentHeading = gyro.get_heading();
//     con.print(0,0, "%d", (int)gyro.get_heading());
//     con.print(2, 0, "%d", (int)angleDifference);
//     if(cc && currentHeading < 180 && currentHeading > 0){
//       angleDifference = fabs(currentHeading - targetAngle +360);
//     }else{
//       angleDifference = fabs(currentHeading - targetAngle);
//     }
//     // angleDifference = fabs(targetAngle - currentHeading);

    
//     drivePower = 600 * (angleDifference /initialDifference);
//     if(drivePower < 50){
//       drivePower = 50;
//     }
//   }
//   con.print(0, 0, "%d", (int)gyro.get_heading());
//   // Stop the drive motors after reaching the target angle
//   stop();
// }

//   void rt(float angle)
//   {
//     while (fabs(gyro.get_heading() - angle) > 5)
//     {
//       setDrive(100,-100);
//       pros::lcd::print(1, "%d", gyro.get_heading());
      
//       pros::delay(10);
//   }
//     pros::delay(10);
//     stop();
}

void fire_pist(){
  if(con.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && con.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
  {
    Piston.set_value(127); 
  }
}