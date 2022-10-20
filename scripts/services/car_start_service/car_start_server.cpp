#include <bits/stdc++.h>
#include "rclcpp/rclcpp.hpp"
#include "firster/srv/start_car.hpp"     // CHANGE

#include <memory>

using namespace std;

void start_car(const std::shared_ptr<firster::srv::StartCar::Request> request,     // CHANGE
          std::shared_ptr<firster::srv::StartCar::Response>       response)  // CHANGE
{
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\ndistance: %f" " speed: %f" " acceleration: %f",   // CHANGE
                request->distance, request->speed, request->acceleration);                                          // CHANGE
  
  string str = "ros2 run firster car_talker";
  const char* command = str.c_str();
  system(command);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%d]", (bool)response->feedback);
  response->feedback=true;
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("car_start_server_node");  // CHANGE

  rclcpp::Service<firster::srv::StartCar>::SharedPtr service =                 // CHANGE
    node->create_service<firster::srv::StartCar>("car_start",  &start_car);     // CHANGE

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to start car");      // CHANGE

  rclcpp::spin(node);
  rclcpp::shutdown();
}
