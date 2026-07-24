#ifndef MY_NAV2_PLUGINS__SLIP_AWARE_NMPC_HPP_
#define MY_NAV2_PLUGINS__SLIP_AWARE_NMPC_HPP_

#include <string>
#include <vector>
#include <memory>
#include <mutex>

#include "rclcpp/rclcpp.hpp"
#include "nav2_core/controller.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"
#include "nav_msgs/msg/path.hpp"
#include "my_robot_msgs/msg/slip_state.hpp"

namespace my_nav2_plugins
{

class SlipAwareNMPC : public nav2_core::Controller
{
public:
  SlipAwareNMPC() = default;
  ~SlipAwareNMPC() override = default;

  // Nav2 核心生命周期接口
  void configure(
    const rclcpp_lifecycle::LifecycleNode::WeakPtr & parent,
    std::string name, std::shared_ptr<tf2_ros::Buffer> tf,
    std::shared_ptr<nav2_costmap_2d::Costmap2DROS> costmap_ros) override;

  void cleanup() override;
  void activate() override;
  void deactivate() override;

  // 接收全局路径规划器 (如 A*) 传来的参考轨迹
  void setPlan(const nav_msgs::msg::Path & path) override;

  // 核心控制循环 (例如 10Hz/20Hz 调用一次)
  geometry_msgs::msg::TwistStamped computeVelocityCommands(
    const geometry_msgs::msg::PoseStamped & pose,
    const geometry_msgs::msg::Twist & velocity,
    nav2_core::GoalChecker * goal_checker) override;

  void setSpeedLimit(const double & speed_limit, const bool & percentage) override;

private:
  // EKF 话题的回调函数
  void slipCallback(const my_robot_msgs::msg::SlipState::SharedPtr msg);

  rclcpp_lifecycle::LifecycleNode::SharedPtr node_;
  std::string plugin_name_;
  std::shared_ptr<tf2_ros::Buffer> tf_;
  std::shared_ptr<nav2_costmap_2d::Costmap2DROS> costmap_ros_;

  // 订阅 EKF 输出的自适应参数
  rclcpp::Subscription<my_robot_msgs::msg::SlipState>::SharedPtr slip_sub_;

  nav_msgs::msg::Path global_plan_;

  // 打滑状态变量与线程锁
  std::mutex slip_mutex_;
  double current_eta_v_ = 1.0;
  double current_eta_w_ = 1.0;
  double current_beta_ = 0.0;
};

}  // namespace my_nav2_plugins

#endif  // MY_NAV2_PLUGINS__SLIP_AWARE_NMPC_HPP_