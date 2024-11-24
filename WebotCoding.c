#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>  // Correct Webots sensor type
#include <stdio.h>                  // Include for snprintf

#define TIME_STEP 64
#define MAX_SPEED 6.28

// Declare motor and sensor tags
WbDeviceTag left_motor, right_motor;
WbDeviceTag ir_sensors[8];  // Assume 8 IR sensors for the e-puck
double sensor_values[8];    // Store sensor readings

// Function to initialize motors and sensors
void initialize_devices() {
  // Initialize motors
  left_motor = wb_robot_get_device("left wheel motor");
  right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor, INFINITY);  // Enable speed control
  wb_motor_set_position(right_motor, INFINITY);

  // Initialize proximity sensors
  for (int i = 0; i < 8; i++) {
    char sensor_name[16];
    snprintf(sensor_name, sizeof(sensor_name), "ps%d", i);  // e-puck proximity sensor names (ps0, ps1, ...)
    ir_sensors[i] = wb_robot_get_device(sensor_name);
    wb_distance_sensor_enable(ir_sensors[i], TIME_STEP);
  }
}

// Function to read sensor values
void read_sensors() {
  for (int i = 0; i < 8; i++) {
    sensor_values[i] = wb_distance_sensor_get_value(ir_sensors[i]);
  }
}

// Function to implement maze-following logic
void follow_maze() {
  read_sensors();

  // Proximity thresholds (values depend on sensor calibration)
  const double WALL_THRESHOLD = 80.0;

  // Left-hand rule: prioritize the left wall
  bool left_wall = sensor_values[5] > WALL_THRESHOLD || sensor_values[6] > WALL_THRESHOLD;
  bool front_wall = sensor_values[0] > WALL_THRESHOLD || sensor_values[7] > WALL_THRESHOLD;
  bool right_wall = sensor_values[1] > WALL_THRESHOLD || sensor_values[2] > WALL_THRESHOLD;

  double left_speed = 0.5 * MAX_SPEED;  // Default forward speed
  double right_speed = 0.5 * MAX_SPEED;

  if (front_wall) {
    // Turn right if there's a wall in front
    left_speed = 0.5 * MAX_SPEED;
    right_speed = -0.5 * MAX_SPEED;
  } else if (left_wall) {
    // Move forward if there's a wall on the left
    left_speed = 0.5 * MAX_SPEED;
    right_speed = 0.5 * MAX_SPEED;
  } else if (right_wall) {
    // Turn left if there's a wall on the right
    left_speed = -0.5 * MAX_SPEED;
    right_speed = 0.5 * MAX_SPEED;
  }

  // Set motor speeds
  wb_motor_set_velocity(left_motor, left_speed);
  wb_motor_set_velocity(right_motor, right_speed);
}

int main() {
  wb_robot_init();  // Initialize the robot

  // Initialize devices (motors and IR sensors)
  initialize_devices();

  while (wb_robot_step(TIME_STEP) != -1) {
    follow_maze();  // Execute maze-following logic at each time step
  }

  wb_robot_cleanup();  // Cleanup after the simulation ends

  return 0;
}
