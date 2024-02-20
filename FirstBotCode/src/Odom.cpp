#include "main.h"


	float diameter = 4.125f;//diameter of the omni wheels for distance measuring

	float radius = diameter * 0.5;//radius of the omni wheel for distance measuring

	float pi =  3.14;//just a shorter  pi for easier processing which is at 3.14

    int LeftMotorEncoder; // takes the encoder values from the the left motors and averages them

    int RightMotorEncoder; // takes the encoder values from the the left motors and averages them

    int calculatedFlywheelRPM;// calculates the rpm based on the gear ratio i added

    const int Tolerance = 36;//fixed variable for the error to try to get the motors degrees in this range

    float kP; //nothin... this isnt here at all im not lazy...
    float kI; // universals for DriveTrain PID
    float kD;



Odom::Odom(){//calls the variables inside class
    float FkD;
    float FKi;
    float FkP;//universals for FlywheelPID
    float FKa;
    int RightMotorEncoder;
    int LeftMotorEncoder;
    float PID;
    float error;
}
  
int Odom::sgn(int val) { //signum function
    if (val > 0){
        return (1);
    }else if (val < 0) {
        return (-1);
    }else {
        return (0);
    }}
int abs(float Value){//absolute value
    if(Value < 0){
        return -Value;
    }else {
        return Value;
    }
}

void OdomTracking(){ //tracks the motors without any limits because i said so
    
    pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);

        float kP = 30;
        float kI = 0.1;
        float kD = 0.3;
    while (true){
        LeftMotorEncoder = FrontLeftMotor.get_encoder_units() + BackLeftMotor.get_encoder_units() / 2;
        RightMotorEncoder = FrontRightMotor.get_encoder_units() + BackRightMotor.get_encoder_units()/2;
    }
    

}
void Odom::Forward(float WantedDistance){ //distance in inches
	// for every 360degrees, the wheel will go its circumference
    bool TargetMet;
	pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);

	FrontLeftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);//when told to stop. itll stay right where its at and not coast
	BackLeftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	FrontRightMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	BackRightMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);




	float circumference =pi*diameter;//funny geometry calculation

	float distancePerDegree = circumference/360;//more funny calculations

	float AngleInDegrees = WantedDistance/distancePerDegree;// forwards angle movement
    bool variablebug = false; //i belive this is the way to go about fixing funny variables... dunno how it does it but it does it
    float P;
    float I;
    float D;
    float LastError;//gets the error from the last loop
    float LeftTarget;
    float RightTarget;
    LeftTarget = AngleInDegrees + LeftMotorEncoder;
    RightTarget = AngleInDegrees + RightMotorEncoder;
    
while ((abs(error) > Tolerance) && !variablebug){//PID Loop W
    error = ((LeftTarget - LeftMotorEncoder) + (RightTarget - RightMotorEncoder))/2;
    P = error * kP;
    I = (I+error) *kI;
    D = (error-LastError)*kD; //PID live time Calculation
    PID = P + I + D;
	FrontLeftMotor.move_voltage(PID);
	BackLeftMotor.move_voltage(PID);
	FrontRightMotor.move_voltage(PID);
	BackRightMotor.move_voltage(PID);

    pros::delay(20);// delays the loop from calling everything else, helps to keep things cool inside the brain and saves battery

    if (error == LastError){//helps fix stuf
            MainController.print(0,0,"PID Error!");
            variablebug = true;
        }
    LastError = error;//haha heres where it gets the last error

    }


}
void Odom::Rotate(float DegreesToRotate){//you spin me right round baby right round like a record baby round round round round
    
    bool TargetMet;
	pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);

	float circumference =pi*diameter;//weird turning calculations
	float DistanceToMoveOnCircumference = DegreesToRotate/360  * circumference;
	float DegreesToMove = DistanceToMoveOnCircumference / diameter * 360;
    bool variablebug = false; //i belive this is the way to go about fixing 
	float P;
    float I;
    float D;
    float kP = 0.3;
    float kI = 0.3;
    float kD = 0.3;
    float LastError;
    float LeftTarget;
    float RightTarget;
    LeftTarget = -DegreesToMove + LeftMotorEncoder;
    RightTarget = DegreesToMove + RightMotorEncoder;
while ((abs(error) > Tolerance )&& !variablebug){//PID Loop W
    error = ((LeftTarget - LeftMotorEncoder) + (RightTarget - RightMotorEncoder))/2;
    P = error * kP;
    I = (I+error) * kI;
    D = (error-LastError) * kD; 
    PID = P + I + D;
	FrontLeftMotor.move_voltage(PID);
	BackLeftMotor.move_voltage(PID);
	FrontRightMotor.move_voltage(-PID);
	BackRightMotor.move_voltage(-PID);
    
    pros::delay(20);    
    if (error == LastError){
            MainController.print(0,0,"PID Error!");
            variablebug = true;
    }
    LastError = error;
    }
} 

void Odom::RunFlywheel(int target){

pros::Motor CataMotor(5);

int prevCalculatedFlywheelRPM;//different PID only its now just a P and no I and D
const int FlywheelGearRatio = 7; //look here it is!
float K;
float P;
float DT;// delta Target RPM
int prevTarget; // for delta calculations
float Output;//voltage for the motors to use
float error;// the distance from the target
float Time;
float a;
float DeadLength;
while (true){
    

    calculatedFlywheelRPM = CataMotor.get_actual_velocity() * FlywheelGearRatio;//calc for flywheel rpm
    int accel = calculatedFlywheelRPM - prevCalculatedFlywheelRPM; //  glorified deltaRPM
	float FF = FKi * sgn(calculatedFlywheelRPM) + FkD * calculatedFlywheelRPM + FKa * accel;  //FF calc(cant say what it is lmao)
	error = target - calculatedFlywheelRPM;//error
	Output = P*FF;//motor output
    CataMotor.move_voltage(Output);
    while (target == 0){//cool motor cooling feature when not needed
        CataMotor.move_voltage(0); // helps keep the motors not try to apply voltage to stop it
        Output = 0;
    }
    pros::delay(250); // allows for deltas to properly work
    prevCalculatedFlywheelRPM = calculatedFlywheelRPM;
    Time += 1;

    }
}