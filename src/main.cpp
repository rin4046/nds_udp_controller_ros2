#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>

#include "nds_input.hpp"
#include "udp_receiver.hpp"

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared("nds_udp_controller_ros2");

  // Publisher and Message
  auto turtle1_cmd_vel = node->create_publisher<geometry_msgs::msg::Twist>(
      "/turtle1/cmd_vel", rclcpp::QoS(10));
  geometry_msgs::msg::Twist twist_msg;

  // UDPReceiver
  UDPReceiver receiver;
  receiver.open(54321);

  // NDSInput
  uint16_t keys;
  NDSInput input;

  while (rclcpp::ok()) {
    receiver.receive(keys);
    input = keys;
    twist_msg.linear.x = input.LEFT ? -2.0 : input.RIGHT ? 2.0 : 0.0;
    twist_msg.linear.y = input.UP ? 2.0 : input.DOWN ? -2.0 : 0.0;
    twist_msg.angular.z = input.L ? 2.0 : input.R ? -2.0 : 0.0;
    turtle1_cmd_vel->publish(twist_msg);
  }

  receiver.close();

  rclcpp::shutdown();

  return 0;
}
