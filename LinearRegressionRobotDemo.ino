//
// LinearRegressionRobotDemo.ino
//
// programmed by George Andrews
//
#include "MeccaBrain.h"

//
// Servo pin definitions are below.
//
#define RIGHT_ELBOW_SERVO_PIN 21
#define RIGHT_SHOULDER_SERVO_PIN 22
#define LEFT_ELBOW_SERVO_PIN 23
#define LEFT_SHOULDER_SERVO_PIN 24

//
// Servo objects are below.
//
MeccaBrain right_elbow_servo(RIGHT_ELBOW_SERVO_PIN);
MeccaBrain right_shoulder_servo(RIGHT_SHOULDER_SERVO_PIN);
MeccaBrain left_elbow_servo(LEFT_ELBOW_SERVO_PIN);
MeccaBrain left_shoulder_servo(LEFT_SHOULDER_SERVO_PIN);

//
// Below are the timing-related variables.
//
unsigned long previous_millis = 0;

//
// This is the number of training data entries.
//
const int num_data_entries = 6;

//
// Here is the training data.
//
float data[num_data_entries][2] =
{
  {0.0, 0.0},
  {0.1, 0.1},
  {0.2, 0.2},
  {0.3, 0.3},
  {0.4, 0.4},
  {0.5, 0.5}
};

//
// Here are our parameters theta_0 and theta_1.
//
float old_theta_0;
float old_theta_1;
float theta_0;
float theta_1;

//
// Below is the step size.
//
float alpha;

//
// Sets all the required values.
//
void SetParameters()
{
  old_theta_0 = 0;
  old_theta_1 = 0;
  theta_0 = 0.1;
  theta_1 = 0.5;
  alpha = 0.01;
}

//
// Evaluates the hypothesis function.
//
float EvaluateHypothesis(float x_i)
{
  float result = theta_0 + (theta_1 * x_i);
  return result;
}

//
// Calculate sum for theta_0.
//
float CalculateTheta0Sum()
{
  float result = 0;
  
  // loop through data array
  for (int i = 0; i < num_data_entries; i++)
  {
    // now get difference of h(x) - y
    float local_difference = EvaluateHypothesis(data[i][0]) - data[i][1];
    result += local_difference;
  }
  
  return result;
}

//
// Calculate sum for theta_1.
//
float CalculateTheta1Sum()
{
  float result = 0;
  
  // loop through data array
  for (int i = 0; i < num_data_entries; i++)
  {
    // get (h(x) - y)x
    float local_difference = EvaluateHypothesis(data[i][0]) - data[i][1];
    local_difference *= data[i][0];
    result += local_difference;
  }
  
  return result;
}

//
// Updates the parameters.
//
void UpdateParameters()
{
  // assign new values to old values so we have the updated values
  old_theta_0 = theta_0;
  old_theta_1 = theta_1;
  
  //--------------------
  // Update theta_0
  //--------------------
  theta_0 = old_theta_0 - ((alpha / num_data_entries) * CalculateTheta0Sum());
  
  //--------------------
  // Update theta_1
  //--------------------
  theta_1 = old_theta_1 - ((alpha / num_data_entries) * CalculateTheta1Sum());
}

void setup()
{
  // set our parameters
  SetParameters();
}

void loop()
{
  // prepare value of position from values theta_0 and theta_1
  byte learned_position = (byte)theta_0;
  learned_position += (byte)theta_1 * 0xFF;
  
  // move motors
  left_elbow_servo.setServoPosition(0, learned_position);
  right_elbow_servo.setServoPosition(0, learned_position);
  left_elbow_servo.communicate();
  right_elbow_servo.communicate();
  
  // update our parameters
  UpdateParameters();
  
  // wait for everything to process before looping again
  delay(500);
}
