import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import ExecuteProcess
from launch_ros.actions import Node
import xacro

def generate_launch_description():
    pkg_dir = get_package_share_directory('my_robot_simulation')
    
    # ========================================================
    # 【核心修复点】自动将工作空间的 models 文件夹路径添加给 Gazebo
    # ========================================================
    models_dir = os.path.join(pkg_dir, 'models')
    if 'GAZEBO_MODEL_PATH' in os.environ:
        os.environ['GAZEBO_MODEL_PATH'] += ':' + models_dir
    else:
        os.environ['GAZEBO_MODEL_PATH'] = models_dir
        
    # 1. 物理世界路径
    world_file = os.path.join(pkg_dir, 'worlds', 'pipe_inspection.world')
    
    # 2. 小车模型路径
    xacro_file = os.path.join(pkg_dir, 'models', 'my_ugv_robot', 'urdf', 'agv.urdf.xacro')
    
    # 解析 xacro 文件
    doc = xacro.parse(open(xacro_file))
    xacro.process_doc(doc)
    robot_description = {'robot_description': doc.toxml()}

    # 启动 Gazebo
    gazebo = ExecuteProcess(
        cmd=['gazebo', '--verbose', world_file, '-s', 'libgazebo_ros_init.so', '-s', 'libgazebo_ros_factory.so'],
        output='screen'
    )

    # 启动 robot_state_publisher，广播 TF
    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='both',
        parameters=[robot_description, {'use_sim_time': True}]
    )

    # 在 Gazebo 中生成小车实体
    spawn_entity = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        # 【修改这里】：将 -x 0.0 改为 -x 2.0
        arguments=['-topic', 'robot_description', '-entity', 'my_agv', '-x', '2.0', '-y', '0.0', '-z', '0.2'],
        output='screen'
    )

    return LaunchDescription([
        gazebo,
        robot_state_publisher_node,
        spawn_entity
    ])