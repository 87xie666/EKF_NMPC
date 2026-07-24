import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    pkg_dir = get_package_share_directory('my_robot_simulation')
    map_file = os.path.join(pkg_dir, 'maps', 'pipe_map.yaml')

    # 1. 静态 TF 发布 (提供完美的算法验证环境，无定位跳变)
    static_tf = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        arguments=['0', '0', '0', '0', '0', '0', 'map', 'odom'],
        output='screen'
    )

    # 2. 地图服务器节点
    map_server = Node(
        package='nav2_map_server',
        executable='map_server',
        name='map_server',
        output='screen',
        parameters=[{'yaml_filename': map_file, 'use_sim_time': True}]
    )

    # 3. 激活地图服务器的生命周期管理器
    lifecycle_manager = Node(
        package='nav2_lifecycle_manager',
        executable='lifecycle_manager',
        name='lifecycle_manager_map',
        output='screen',
        parameters=[
            {'use_sim_time': True},
            {'autostart': True},
            {'node_names': ['map_server']}
        ]
    )

    return LaunchDescription([
        static_tf,
        map_server,
        lifecycle_manager
    ])
