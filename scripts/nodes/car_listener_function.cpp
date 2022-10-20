#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "firster/msg/metrics.hpp"     // CHANGE
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("car_listener_node")
  {
    subscription_ = this->create_subscription<firster::msg::Metrics>(          // CHANGE
      "car_chat", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const firster::msg::Metrics::SharedPtr msg) const       // CHANGE
  {
    RCLCPP_INFO(this->get_logger(), "I heard Ditance: '%f' Speed: '%f' Acceleration: '%f'", msg->distance, msg->speed, msg->acceleration);              // CHANGE
  }
  rclcpp::Subscription<firster::msg::Metrics>::SharedPtr subscription_;       // CHANGE
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
