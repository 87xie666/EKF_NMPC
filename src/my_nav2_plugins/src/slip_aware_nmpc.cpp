#include "my_nav2_plugins/slip_aware_nmpc.hpp"
#include "pluginlib/class_list_macros.hpp"
#include "tf2/utils.h"
#include <cmath>

namespace my_nav2_plugins
{

void SlipAwareNMPC::configure(
  const rclcpp_lifecycle::LifecycleNode::WeakPtr & parent,
  std::string name, std::shared_ptr<tf2_ros::Buffer> tf,
  std::shared_ptr<nav2_costmap_2d::Costmap2DROS> costmap_ros)
{
  node_ = parent.lock();
  plugin_name_ = name;
  tf_ = tf;
  costmap_ros_ = costmap_ros;

  RCLCPP_INFO(node_->get_logger(), "Configuring Slip-Aware NMPC Plugin...");

  // 订阅 EKF 估计器传来的滑移状态参数
  slip_sub_ = node_->create_subscription<my_robot_msgs::msg::SlipState>(
    "/ekf/slip_estimation", 10,
    std::bind(&SlipAwareNMPC::slipCallback, this, std::placeholders::_1));
}

void SlipAwareNMPC::cleanup()
{
  slip_sub_.reset();
}

void SlipAwareNMPC::activate()
{
  RCLCPP_INFO(node_->get_logger(), "Activating Slip-Aware NMPC...");
}

void SlipAwareNMPC::deactivate()
{
  RCLCPP_INFO(node_->get_logger(), "Deactivating Slip-Aware NMPC...");
}

void SlipAwareNMPC::setPlan(const nav_msgs::msg::Path & path)
{
  global_plan_ = path;
}

void SlipAwareNMPC::setSpeedLimit(const double & speed_limit, const bool & percentage)
{
  (void)speed_limit;
  (void)percentage;
}

void SlipAwareNMPC::slipCallback(const my_robot_msgs::msg::SlipState::SharedPtr msg)
{
  std::lock_guard<std::mutex> lock(slip_mutex_);
  current_eta_v_ = msg->eta_v;
  current_eta_w_ = msg->eta_w;
  current_beta_ = msg->beta;
}

geometry_msgs::msg::TwistStamped SlipAwareNMPC::computeVelocityCommands(
  const geometry_msgs::msg::PoseStamped & pose,
  const geometry_msgs::msg::Twist & velocity,
  nav2_core::GoalChecker * /*goal_checker*/)
{
  (void)velocity; // 在更复杂的 NMPC 中可作为初始状态输入

  // 1. 获取当前机器人位姿 (x, y, yaw)
  double current_x = pose.pose.position.x;
  double current_y = pose.pose.position.y;
  double current_yaw = tf2::getYaw(pose.pose.orientation);

  // 2. 获取最新的滑移参数 (保证线程安全)
  double eta_v, eta_w, beta;
  {
    std::lock_guard<std::mutex> lock(slip_mutex_);
    eta_v = current_eta_v_;
    eta_w = current_eta_w_;
    beta = current_beta_;
  }

  // Debug 打印，验证参数是否顺利传递
  RCLCPP_DEBUG(node_->get_logger(), 
    "State - x:%.2f y:%.2f yaw:%.2f | Slip - eta_v:%.2f eta_w:%.2f beta:%.2f",
    current_x, current_y, current_yaw, eta_v, eta_w, beta);

  // 3. 构建求解器输入参数 P = [x0, y0, theta0, eta_v, eta_w, beta]
  std::vector<double> p_params = {current_x, current_y, current_yaw, eta_v, eta_w, beta};

  // -------------------------------------------------------------------
  // [此处是与 C 语言求解器交互的区域]
  // 实际工程中，你需要调用 CasADi 生成的 nmpc_solver 接口。
  // 伪代码流程：
  // 1. 将 p_params 映射到 nmpc_solver_arg
  // 2. nmpc_solver(arg, res, iw, w, 0); 
  // 3. 从 res 数组中提取最优控制序列的第一步 [v_opt, w_opt]
  // -------------------------------------------------------------------
  
  double v_opt = 0.5;  // 占位符：来自优化器
  double w_opt = 0.0;  // 占位符：来自优化器

  // 4. 打包控制指令并发布给底盘
  geometry_msgs::msg::TwistStamped cmd_vel;
  cmd_vel.header.frame_id = "base_link";
  cmd_vel.header.stamp = node_->now();
  cmd_vel.twist.linear.x = v_opt;
  cmd_vel.twist.angular.z = w_opt;

  return cmd_vel;
}

}  // namespace my_nav2_plugins

// 将该类注册为标准的 ROS 2 Nav2 控制器插件
PLUGINLIB_EXPORT_CLASS(my_nav2_plugins::SlipAwareNMPC, nav2_core::Controller)