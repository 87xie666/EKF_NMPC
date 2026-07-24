import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node

def generate_launch_description():
    pkg_dir = get_package_share_directory('my_robot_simulation')
    nav2_bringup_dir = get_package_share_directory('nav2_bringup')
    nav2_params_file = os.path.join(pkg_dir, 'config', 'nav2_params.yaml')

    # 1. 启动你的打滑观测器 (感知层)
    slip_estimator_node = Node(
        package='slip_estimator',
        executable='slip_ekf_node',
        name='slip_ekf_node',
        output='screen'
    )

    # 2. 启动 Nav2 栈 (注入你的参数文件)
    nav2_bringup = IncludeLaunchDescription(
    PythonLaunchDescriptionSource(os.path.join(nav2_bringup_dir, 'launch', 'navigation_launch.py')),
    launch_arguments={
        'use_sim_time': 'True', # 请务必确认这里是字符串 'True' 或 'true'
        'params_file': nav2_params_file,
        'autostart': 'True'
    }.items()
    )

    # 3. 启动 RViz2 进行调试与可视化
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen',
        arguments=['-d', os.path.join(pkg_dir, 'config', 'rviz2_config.rviz')],
        parameters=[{'use_sim_time': True}]
    )

    return LaunchDescription([
        slip_estimator_node,
        nav2_bringup,
        rviz_node
    ])