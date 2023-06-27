#include "main.h"
 int power = -127;
 bool primed = false;
void setCataMotor(){
    
    if(limitSwitch.get_value()&& primed == false){
        
        power = 0;
        primed = true;
    }
    if(con.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && primed == true){
        Catapult.move(-127);
        pros::delay(80);
        Catapult.move(0);
        
        primed = false;
        pros::delay(45);
    }
    if (primed == false)
    {
        power = -127;
    }
    
    Catapult.move(power);
    
}

void auton_shoot(){
    Catapult.move(-127);
    pros::delay(500);
    stop();
    while(!limitSwitch.get_value()){
        Catapult.move(-127);
    }
    // pros::delay(85);
    Catapult.move(0);
}
