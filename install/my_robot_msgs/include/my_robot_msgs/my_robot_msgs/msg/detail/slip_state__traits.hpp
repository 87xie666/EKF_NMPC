// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from my_robot_msgs:msg/SlipState.idl
// generated code does not contain a copyright notice

#ifndef MY_ROBOT_MSGS__MSG__DETAIL__SLIP_STATE__TRAITS_HPP_
#define MY_ROBOT_MSGS__MSG__DETAIL__SLIP_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "my_robot_msgs/msg/detail/slip_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace my_robot_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const SlipState & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: eta_v
  {
    out << "eta_v: ";
    rosidl_generator_traits::value_to_yaml(msg.eta_v, out);
    out << ", ";
  }

  // member: eta_w
  {
    out << "eta_w: ";
    rosidl_generator_traits::value_to_yaml(msg.eta_w, out);
    out << ", ";
  }

  // member: beta
  {
    out << "beta: ";
    rosidl_generator_traits::value_to_yaml(msg.beta, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SlipState & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: eta_v
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "eta_v: ";
    rosidl_generator_traits::value_to_yaml(msg.eta_v, out);
    out << "\n";
  }

  // member: eta_w
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "eta_w: ";
    rosidl_generator_traits::value_to_yaml(msg.eta_w, out);
    out << "\n";
  }

  // member: beta
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "beta: ";
    rosidl_generator_traits::value_to_yaml(msg.beta, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SlipState & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace my_robot_msgs

namespace rosidl_generator_traits
{

[[deprecated("use my_robot_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const my_robot_msgs::msg::SlipState & msg,
  std::ostream & out, size_t indentation = 0)
{
  my_robot_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use my_robot_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const my_robot_msgs::msg::SlipState & msg)
{
  return my_robot_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<my_robot_msgs::msg::SlipState>()
{
  return "my_robot_msgs::msg::SlipState";
}

template<>
inline const char * name<my_robot_msgs::msg::SlipState>()
{
  return "my_robot_msgs/msg/SlipState";
}

template<>
struct has_fixed_size<my_robot_msgs::msg::SlipState>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<my_robot_msgs::msg::SlipState>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<my_robot_msgs::msg::SlipState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MY_ROBOT_MSGS__MSG__DETAIL__SLIP_STATE__TRAITS_HPP_
