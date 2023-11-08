#include "main.h"
//(port,pros::E_MOTOR_GEARSET(06=600rpm,18=200rpm,36=100rpm)is Reversed?(bool))
//motor encoders(counts = raw value, degress, rotations)
//both fronts should be reversed
void initialize() {

pros::Motor FrontLeft_initializer(1, pros::E_MOTOR_GEARSET_06, false,pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor FrontRightMotor_initializer(2,pros::E_MOTOR_GEARSET_06, false,pros:: E_MOTOR_ENCODER_COUNTS);
//front Motors


//Back Motors
pros::Motor BackLeftMotor_initializer(3, pros::E_MOTOR_GEARSET_06, false,pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor BackRightMotor_initializer(4, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::Controller MainController (pros::E_CONTROLLER_MASTER); // controller Init

pros::Motor ArmMotor_initializer(5, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor SecondArmMotor_initializer(6, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor ClawLeftMotor_initializer(7, pros::E_MOTOR_GEARSET_36, false,pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor ClawRightMotor_initializer(8, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::ADIDigitalIn PowerSavingButton (1);

}


