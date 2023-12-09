/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Student                                          */
/*    Created:      Fri Dec 08 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// topfrontleft         inertial      8               
// topbackright         motor         20              
// topbackleft          motor         3               
// frontleft            motor         17              
// frontright           motor         9               
// backright            motor         12              
// backleft             motor         4               
// intake               motor         2               
// catapult             motor         1               
// leftwing             digital_out   A               
// intakepistonb        digital_out   B               
// rightwing            digital_out   H               
// Opticall             optical       10              
// Controller1          controller                    
// RotationRight        rotation      13              
// RotationLeft         rotation      14              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "functions.h"
using namespace vex;


void stupidsplitluca() {
  catapult.setStopping(hold);
  frontleft.setStopping(coast);
  frontright.setStopping(coast);
  backleft.setStopping(coast);
  backright.setStopping(coast);
  topbackleft.setStopping(coast);
  topbackright.setStopping(coast);
  while (true) {
      float movement = (Controller1.Axis3.position()) + (Controller1.Axis1.position());
      float movement1 = (Controller1.Axis3.position()) - (Controller1.Axis1.position());
      frontleft.spin(forward, movement, pct);
      frontright.spin(forward, movement1, pct);
      //back dt
      backleft.spin(forward, movement, pct);
      backright.spin(forward, movement1, pct);
      // ------------
      topbackleft.spin(forward, movement, pct);
      topbackright.spin(forward, movement1, pct);
      // ------------
    if (Controller1.ButtonR2.pressing()) {
      (intake.spin(forward, 90, pct));
    } else if (Controller1.ButtonR1.pressing()) {
      (intake.spin(reverse, 90, pct));
    } else {
      intake.stop();
    }
    if (Controller1.ButtonY.pressing()) {
      (catapult.spin(reverse, 90, pct));
    } else {
      catapult.stop();
    }
    //pnue intake
    if (Controller1.ButtonX.pressing()) {
        intakepistonb.set(false);
    } else {
        intakepistonb.set(true);
    }
    //pnue wings
    if (Controller1.ButtonUp.pressing()) {
        leftwing.set(true);
        rightwing.set(true);
    } else {
        leftwing.set(false);
        rightwing.set(false);
    }
  }
}

void forwardPIDD(float setpoint) {
  float error = setpoint - backleft.position(degrees);
  float power;
  float i = 1;
  double kP = 0.11;
  while (abs(error) > i) {
    error = setpoint - backleft.position(degrees);
    power = error * kP;
    Brain.Screen.printAt(60, 15, "%f", backleft.position(degrees));
    topbackleft.spin(forward, power, pct);
    topbackright.spin(forward, power, pct);
    backleft.spin(forward, power, pct);
    backright.spin(forward, power, pct);
    frontleft.spin(forward, power, pct);
    frontright.spin(forward, power, pct);
  }
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(60, 15, "%f", backleft.position(degrees));
  frontleft.stop(coast);
  frontright.stop(coast);
  backleft.stop(coast);
  backright.stop(coast);
  topbackleft.stop(coast);
  topbackright.stop(coast);
}

void fkpcut(float setpoint) {
  float error = setpoint - backleft.position(degrees);
  float power;
  float i = 0;
  double kP = 0.09;
  while (abs(error) > i) {
    error = setpoint - backleft.position(degrees);
    power = error * kP;
    Brain.Screen.printAt(60, 15, "%f", backleft.position(degrees));
    topbackleft.spin(forward, power, pct);
    topbackright.spin(forward, power, pct);
    backleft.spin(forward, power, pct);
    backright.spin(forward, power, pct);
    frontleft.spin(forward, power, pct);
    frontright.spin(forward, power, pct);
  }
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(60, 15, "%f", backleft.position(degrees));
  frontleft.stop(coast);
  frontright.stop(coast);
  backleft.stop(coast);
  backright.stop(coast);
  topbackleft.stop(coast);
  topbackright.stop(coast);
}

void autofire() {
  while (true) {
  if (Opticall.hue() < 105 && Opticall.hue() > 65) {
    catapult.spin(forward, 50, pct);
    Brain.Screen.print("Hue: %.2f", Opticall.hue());
    Brain.Screen.setCursor(2,2);
  }
  else {
    catapult.stop();
    Brain.Screen.print("Hue: %.2f", Opticall.hue());
    Brain.Screen.setCursor(2,2);
  }

}
  wait(10, msec);
  Brain.Screen.clearScreen();
}

void sensordisplays () {
  while (true) {
    Brain.Screen.printAt(15, 15, "%f", RotationRight.position(degrees));
    Brain.Screen.printAt(30, 30, "%f", RotationLeft.position(degrees));
    Brain.Screen.printAt(45, 45, "%f", topfrontleft.heading(degrees));
    Brain.Screen.printAt(60, 60, "Hue: %.2f", Opticall.hue());
    wait(10,msec);
    Brain.Screen.clearScreen();
  }
}

void clearmotors () {
  frontleft.resetPosition();
  frontright.resetPosition();
  backleft.resetPosition();
  backright.resetPosition();
  topbackleft.resetPosition();
  topbackright.resetPosition();
}

void clearall() {
  frontleft.resetPosition();
  frontright.resetPosition();
  backleft.resetPosition();
  backright.resetPosition();
  topbackleft.resetPosition();
  topbackright.resetPosition();
  topfrontleft.resetHeading();
  RotationLeft.resetPosition();
  RotationRight.resetPosition();
}

void setwings(int setpoint) {
  leftwing.set(setpoint);
  rightwing.set(setpoint);
}

void setintake(int setpoint) {
  intakepistonb.set(setpoint);
}

void setall(int setpoint) {
  leftwing.set(setpoint);
  rightwing.set(setpoint);
  intakepistonb.set(setpoint);
}

void pre() {
  clearall();
  // thread d(autofire);
  Controller1.Screen.setCursor(2,2);
  Controller1.Screen.print("Calibrating sensors...");
  intakepistonb.set(false);
  topfrontleft.calibrate();
  wait(2.5, seconds);
  Controller1.Screen.setCursor(2,2);
  Controller1.Screen.print("      We're live!        ");
}

// forwardPIDD is move forward, -setpoint for move backward
// turnPID is turn, -setpoint for turning right
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // stupidsplitluca();
  pre();
  thread a(sensordisplays);
  //begin route
  forwardPIDD(950);
  clearmotors();
  wait(.2, seconds);
  clearall();
  forwardPIDD(-550);
  clearall();
  turnPID(101, 10, -1);
  clearall();
  forwardPIDD(225);
  wait(.2, seconds);
  clearall();
  intakepistonb.set(true);
  wait(.2,seconds);
  intake.spin(forward, 100, pct);
  wait(1.5, seconds);
  intake.stop();
  clearall();
  forwardPIDD(-1750);
  clearall();
  rightwing.set(true);
  clearall();
  forwardPIDD(-500);
  clearall();
  rightwing.set(false);
  turnPID(190, 25, -1);
  forwardPIDD(750);
}