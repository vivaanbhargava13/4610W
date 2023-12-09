#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
inertial topfrontleft = inertial(PORT8);
motor topbackright = motor(PORT20, ratio6_1, true);
motor topbackleft = motor(PORT3, ratio6_1, false);
motor frontleft = motor(PORT17, ratio6_1, true);
motor frontright = motor(PORT9, ratio6_1, false);
motor backright = motor(PORT12, ratio6_1, false);
motor backleft = motor(PORT4, ratio6_1, true);
motor intake = motor(PORT2, ratio18_1, false);
motor catapult = motor(PORT1, ratio18_1, false);
digital_out leftwing = digital_out(Brain.ThreeWirePort.A);
digital_out intakepistonb = digital_out(Brain.ThreeWirePort.B);
digital_out rightwing = digital_out(Brain.ThreeWirePort.H);
optical Opticall = optical(PORT10);
controller Controller1 = controller(primary);
rotation RotationRight = rotation(PORT13, false);
rotation RotationLeft = rotation(PORT14, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}