cmake_minimum_required(VERSION 3.5)
project(firster)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(firster REQUIRED)

find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
    "msg/Metrics.msg"
    "srv/StartCar.srv"
)

add_executable(talker scripts/nodes/publisher_member_function.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

add_executable(listener scripts/nodes/subscriber_member_function.cpp)
ament_target_dependencies(listener rclcpp std_msgs)

add_executable(car_listener scripts/nodes/car_listener_function.cpp)
ament_target_dependencies(car_listener rclcpp firster)

add_executable(car_talker scripts/nodes/car_talker_function.cpp)
ament_target_dependencies(car_talker rclcpp firster)

add_executable(car_start_server scripts/services/car_start_service/car_start_server.cpp)
ament_target_dependencies(car_start_server rclcpp firster)

add_executable(car_start_client scripts/services/car_start_service/car_start_client.cpp)
ament_target_dependencies(car_start_client rclcpp firster)

install(TARGETS
  talker
  listener
  car_listener
  car_talker
  car_start_server
  car_start_client
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
