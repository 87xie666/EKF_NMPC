cmake_minimum_required(VERSION 3.8)
project(my_robot_msgs)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 查找必要的构建依赖
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)

# 声明需要生成的自定义消息文件
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/SlipState.msg"
  DEPENDENCIES std_msgs
)

# 导出运行时依赖
ament_export_dependencies(rosidl_default_runtime)

ament_package()