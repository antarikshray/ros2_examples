#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "firster/msg/metrics.hpp"     // CHANGE

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("car_talker_node"), count_(0)
  {
    publisher_ = this->create_publisher<firster::msg::Metrics>("car_chat", 10);    // CHANGE
    timer_callback();
  }

private:
  void timer_callback()
  {
    auto message = firster::msg::Metrics();                               // CHANGE
    message.distance = this->count_++;
    message.speed = 4;
    message.acceleration = 0;                                        // CHANGE
    RCLCPP_INFO(this->get_logger(), "Publishing: Car Data");    // CHANGE
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<firster::msg::Metrics>::SharedPtr publisher_;         // CHANGE
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  std::make_shared<MinimalPublisher>();
  rclcpp::shutdown();
  return 0;
}
