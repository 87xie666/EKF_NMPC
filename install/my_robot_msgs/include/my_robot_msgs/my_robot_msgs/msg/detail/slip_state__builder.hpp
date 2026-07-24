// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_robot_msgs:msg/SlipState.idl
// generated code does not contain a copyright notice

#ifndef MY_ROBOT_MSGS__MSG__DETAIL__SLIP_STATE__BUILDER_HPP_
#define MY_ROBOT_MSGS__MSG__DETAIL__SLIP_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_robot_msgs/msg/detail/slip_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_robot_msgs
{

namespace msg
{

namespace builder
{

class Init_SlipState_beta
{
public:
  explicit Init_SlipState_beta(::my_robot_msgs::msg::SlipState & msg)
  : msg_(msg)
  {}
  ::my_robot_msgs::msg::SlipState beta(::my_robot_msgs::msg::SlipState::_beta_type arg)
  {
    msg_.beta = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_robot_msgs::msg::SlipState msg_;
};

class Init_SlipState_eta_w
{
public:
  explicit Init_SlipState_eta_w(::my_robot_msgs::msg::SlipState & msg)
  : msg_(msg)
  {}
  Init_SlipState_beta eta_w(::my_robot_msgs::msg::SlipState::_eta_w_type arg)
  {
    msg_.eta_w = std::move(arg);
    return Init_SlipState_beta(msg_);
  }

private:
  ::my_robot_msgs::msg::SlipState msg_;
};

class Init_SlipState_eta_v
{
public:
  explicit Init_SlipState_eta_v(::my_robot_msgs::msg::SlipState & msg)
  : msg_(msg)
  {}
  Init_SlipState_eta_w eta_v(::my_robot_msgs::msg::SlipState::_eta_v_type arg)
  {
    msg_.eta_v = std::move(arg);
    return Init_SlipState_eta_w(msg_);
  }

private:
  ::my_robot_msgs::msg::SlipState msg_;
};

class Init_SlipState_header
{
public:
  Init_SlipState_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SlipState_eta_v header(::my_robot_msgs::msg::SlipState::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_SlipState_eta_v(msg_);
  }

private:
  ::my_robot_msgs::msg::SlipState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_robot_msgs::msg::SlipState>()
{
  return my_robot_msgs::msg::builder::Init_SlipState_header();
}

}  // namespace my_robot_msgs

#endif  // MY_ROBOT_MSGS__MSG__DETAIL__SLIP_STATE__BUILDER_HPP_
