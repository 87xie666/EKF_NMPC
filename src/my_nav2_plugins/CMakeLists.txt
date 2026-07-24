cmake_minimum_required(VERSION 3.8)
project(my_nav2_plugins)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(nav2_core REQUIRED)
find_package(pluginlib REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(nav2_costmap_2d REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(my_robot_msgs REQUIRED)

# ==========================================
# 注意：在实际编译前，请确保已经运行过 scripts/generate_nmpc.py
# 并且 src/ 目录下存在生成的 nmpc_solver.c 文件。
# 若只是为了通过初始 C++ 编译测试，可以先将 nmpc_solver.c 从源码列表中注释掉。
# ==========================================
add_library(slip_nmpc_plugin SHARED
  src/slip_aware_nmpc.cpp
  # src/nmpc_solver.c  <-- 运行 python 脚本后取消注释
)

target_include_directories(slip_nmpc_plugin PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

ament_target_dependencies(slip_nmpc_plugin
  rclcpp
  nav2_core
  pluginlib
  geometry_msgs
  nav_msgs
  nav2_costmap_2d
  tf2_ros
  my_robot_msgs
)

# 注册 pluginlib 的 XML 文件
pluginlib_export_plugin_description_file(nav2_core slip_nmpc_plugin.xml)

install(TARGETS slip_nmpc_plugin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY include/
  DESTINATION include
)

install(FILES slip_nmpc_plugin.xml
  DESTINATION share/${PROJECT_NAME}
)

ament_export_dependencies(rclcpp nav2_core pluginlib my_robot_msgs)
ament_package()