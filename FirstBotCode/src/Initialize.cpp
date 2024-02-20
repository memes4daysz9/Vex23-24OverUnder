#include "main.h"
using namespace std;//gets the funny file system info
void initialize() {
    pros::Task OdomTask(OdomTracking); //multithreading W
    pros::Task ScreenTask(ScreenStats);
    pros::ADIDigitalOut FirstWingMan(1 ,'a');//solonoid calling
	pros::ADIDigitalOut SecondWingMan(2 ,'b');
    FirstWingMan.set_value(LOW);//da kenny fix
    SecondWingMan.set_value(LOW);
    //MotorsInitialization
    pros::Motor FrontLeftMotor_initializer(1, pros::E_MOTOR_GEARSET_18, false,pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor FrontRightMotor_initializer(2,pros::E_MOTOR_GEARSET_18, true,pros:: E_MOTOR_ENCODER_COUNTS);//initializes the motors... not sure if they are working as of this moment
    pros::Motor BackLeftMotor_initializer(3, pros::E_MOTOR_GEARSET_18, false,pros::E_MOTOR_ENCODER_COUNTS);//drivetrain motors
    pros::Motor BackRightMotor_initializer(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
    //others
    pros::Motor CataMotor_initializer(5, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor Intake_initializer(6, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);//other motors
    pros::Motor LeftShotBlock_initializer(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor RightShotBlock_initializer(8, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);

    if (pros::usd::is_installed()){ // filesystem currently not avaliable... definitly at worlds if somehow i make it
        ofstream CurrentLog ("/usd/LogData.txt");
    }
}
