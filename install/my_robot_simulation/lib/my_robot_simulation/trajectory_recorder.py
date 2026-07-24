import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry
import csv

class TrajectoryRecorder(Node):
    def __init__(self):
        super().__init__('trajectory_recorder')
        self.subscription = self.create_subscription(Odometry, '/odom', self.odom_callback, 10)
        self.file = open('agv_trajectory_data.csv', 'w', newline='')
        self.writer = csv.writer(self.file)
        # 直接输出标准的 X, Y 轴，无需后续在 Origin 里再做数据清洗
        self.writer.writerow(['Time_s', 'Pos_X_m', 'Pos_Y_m', 'Yaw_rad']) 

    def odom_callback(self, msg):
        t = msg.header.stamp.sec + msg.header.stamp.nanosec * 1e-9
        x = msg.pose.pose.position.x
        y = msg.pose.pose.position.y
        # 提取 yaw 的逻辑可根据需要加入
        self.writer.writerow([f"{t:.3f}", f"{x:.4f}", f"{y:.4f}", "0.0"])

    def destroy_node(self):
        self.file.close()
        super().destroy_node()

def main():
    rclpy.init()
    recorder = TrajectoryRecorder()
    rclpy.spin(recorder)
    recorder.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()