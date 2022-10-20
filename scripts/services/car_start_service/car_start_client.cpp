#include "rclcpp/rclcpp.hpp"
#include "firster/srv/start_car.hpp"        // CHANGE

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
/*
  if (argc != 4) { // CHANGE
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: start car with distance, speed and acceleration");      // CHANGE
      return 1;
  }
*/
  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("car_start_client_node"); // CHANGE
  rclcpp::Client<firster::srv::StartCar>::SharedPtr client =                        // CHANGE
    node->create_client<firster::srv::StartCar>("car_start");                  // CHANGE

  auto request = std::make_shared<firster::srv::StartCar::Request>();               // CHANGE
  request->distance = atoll(argv[1]);
  request->speed = atoll(argv[2]);
  request->acceleration = atoll(argv[3]);               // CHANGE

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);
  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result) ==
    rclcpp::executor::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Car Start Status: %d", result.get()->feedback);
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service car_start");    // CHANGE
  }

  rclcpp::shutdown();
  return 0;
}
