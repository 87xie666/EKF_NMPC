#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include "my_robot_msgs/msg/slip_state.hpp"
#include <cmath>
#include <algorithm>

class SlipEstimatorNode : public rclcpp::Node
{
public:
  SlipEstimatorNode() : Node("slip_estimator_node")
  {
    // 1. 订阅轮式里程计 (获取底盘理论执行的速度 v_odom, w_odom)
    odom_sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
      "/odom", 10, std::bind(&SlipEstimatorNode::odomCallback, this, std::placeholders::_1));
    
    // 2. 订阅 IMU (获取真实的物理角速度和加速度)
    imu_sub_ = this->create_subscription<sensor_msgs::msg::Imu>(
      "/imu/data", 10, std::bind(&SlipEstimatorNode::imuCallback, this, std::placeholders::_1));

    // 3. 发布滑移状态给 NMPC
    slip_pub_ = this->create_publisher<my_robot_msgs::msg::SlipState>("/ekf/slip_estimation", 10);
    
    // 4. 定时器：以 50Hz (20ms) 频率运行状态估算逻辑
    timer_ = this->create_wall_timer(
      std::chrono::milliseconds(20), std::bind(&SlipEstimatorNode::estimateAndPublish, this));

    RCLCPP_INFO(this->get_logger(), "Slip Estimator Node has been started.");
  }

private:
  void odomCallback(const nav_msgs::msg::Odometry::SharedPtr msg) {
    v_odom_ = msg->twist.twist.linear.x;
    w_odom_ = msg->twist.twist.angular.z;
  }

  void imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg) {
    a_y_imu_ = msg->linear_acceleration.y; // 侧向加速度 (用于评估侧滑)
    w_imu_ = msg->angular_velocity.z;      // 实际偏航角速度
  }

  void estimateAndPublish()
  {
    double raw_eta_w = 1.0;
    double raw_beta = 0.0;
    double raw_eta_v = 1.0;

    // ==========================================
    // 核心观测器数学逻辑
    // ==========================================

    // 1. 转向效率 eta_w = 实际角速度 / 指令角速度
    // 设定死区阈值以防除以零
    if (std::abs(w_odom_) > 0.05) {
      raw_eta_w = std::abs(w_imu_ / w_odom_);
    } else {
      raw_eta_w = 1.0;
    }

    // 2. 侧滑角 beta 估算
    // 物理学原理：小车转弯且侧向抓地力不足时，侧向加速度 a_y 会增大
    // 简化运动学近似：beta ≈ atan(a_y / v_x - w_z)
    if (v_odom_ > 0.1) {
      // 0.1为调参经验系数，代表传感器噪声和侧向刚度比例
      raw_beta = std::atan2(a_y_imu_ * 0.1, v_odom_); 
    } else {
      raw_beta = 0.0; 
    }

    // 3. 纵向效率估算
    // 在真实科研中，这里需要融合如 AMCL, 激光里程计(LOAM) 等高精度全局定位速度
    // 在此仅作恒定打滑近似 (或者你可以通过 v_imu / v_odom 计算)
    raw_eta_v = 0.95; 

    // ==========================================
    // 一阶低通滤波 (非常关键：防止NMPC由于噪声而发散)
    // ==========================================
    double alpha = 0.2; // 滤波系数，取值范围 (0, 1)。越小越平滑，但延迟越大
    
    filtered_eta_w_ = alpha * raw_eta_w + (1.0 - alpha) * filtered_eta_w_;
    filtered_beta_  = alpha * raw_beta  + (1.0 - alpha) * filtered_beta_;
    filtered_eta_v_ = alpha * raw_eta_v + (1.0 - alpha) * filtered_eta_v_;

    // ==========================================
    // 数据限幅 (Hard Bounds) 保护控制器
    // ==========================================
    filtered_eta_w_ = std::clamp(filtered_eta_w_, 0.1, 1.0);
    filtered_beta_  = std::clamp(filtered_beta_, -0.6, 0.6); // 侧滑角最大限制在约 ±34度
    filtered_eta_v_ = std::clamp(filtered_eta_v_, 0.1, 1.0);

    // ==========================================
    // 发布 ROS 2 消息
    // ==========================================
    my_robot_msgs::msg::SlipState slip_msg;
    slip_msg.header.stamp = this->now();
    slip_msg.header.frame_id = "base_link";
    slip_msg.eta_w = filtered_eta_w_;
    slip_msg.beta = filtered_beta_;
    slip_msg.eta_v = filtered_eta_v_;

    slip_pub_->publish(slip_msg);
  }

  // 传感器数据缓存
  double v_odom_ = 0.0;
  double w_odom_ = 0.0;
  double a_y_imu_ = 0.0;
  double w_imu_ = 0.0;
  
  // 滤波器内部状态
  double filtered_eta_w_ = 1.0;
  double filtered_beta_ = 0.0;
  double filtered_eta_v_ = 1.0;
  
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;
  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
  rclcpp::Publisher<my_robot_msgs::msg::SlipState>::SharedPtr slip_pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  // 创建并自旋节点
  rclcpp::spin(std::make_shared<SlipEstimatorNode>());
  rclcpp::shutdown();
  return 0;
}