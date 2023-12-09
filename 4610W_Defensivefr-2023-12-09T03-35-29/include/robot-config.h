using namespace vex;

extern brain Brain;

// VEXcode devices
extern inertial topfrontleft;
extern motor topbackright;
extern motor topbackleft;
extern motor frontleft;
extern motor frontright;
extern motor backright;
extern motor backleft;
extern motor intake;
extern motor catapult;
extern digital_out leftwing;
extern digital_out intakepistonb;
extern digital_out rightwing;
extern optical Opticall;
extern controller Controller1;
extern rotation RotationRight;
extern rotation RotationLeft;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );