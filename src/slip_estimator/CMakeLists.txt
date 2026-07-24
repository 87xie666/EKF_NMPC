cmake_minimum_required(VERSION 3.8)
project(slip_estimator)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(my_robot_msgs REQUIRED)

# 编译 C++ 节点
add_executable(slip_ekf_node src/slip_ekf_node.cpp)

# 链接依赖库
ament_target_dependencies(slip_ekf_node
  rclcpp
  nav_msgs
  sensor_msgs
  my_robot_msgs
)

# 安装可执行文件到 lib 目录，以便 ros2 run 可以找到它
install(TARGETS slip_ekf_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()