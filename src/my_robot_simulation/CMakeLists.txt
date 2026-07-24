cmake_minimum_required(VERSION 3.8)
project(my_robot_simulation)

find_package(ament_cmake REQUIRED)

# 将 launch, config, models, worlds 文件夹安装到 share 目录
install(DIRECTORY 
  launch
  config
  models
  worlds
  DESTINATION share/${PROJECT_NAME}
)
install(PROGRAMS
  scripts/trajectory_recorder.py
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()