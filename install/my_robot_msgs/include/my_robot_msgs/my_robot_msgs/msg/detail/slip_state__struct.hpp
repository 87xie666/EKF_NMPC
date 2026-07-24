// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from my_robot_msgs:msg/SlipState.idl
// generated code does not contain a copyright notice

#ifndef MY_ROBOT_MSGS__MSG__DETAIL__SLIP_STATE__STRUCT_HPP_
#define MY_ROBOT_MSGS__MSG__DETAIL__SLIP_STATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__my_robot_msgs__msg__SlipState __attribute__((deprecated))
#else
# define DEPRECATED__my_robot_msgs__msg__SlipState __declspec(deprecated)
#endif

namespace my_robot_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SlipState_
{
  using Type = SlipState_<ContainerAllocator>;

  explicit SlipState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->eta_v = 0.0;
      this->eta_w = 0.0;
      this->beta = 0.0;
    }
  }

  explicit SlipState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->eta_v = 0.0;
      this->eta_w = 0.0;
      this->beta = 0.0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _eta_v_type =
    double;
  _eta_v_type eta_v;
  using _eta_w_type =
    double;
  _eta_w_type eta_w;
  using _beta_type =
    double;
  _beta_type beta;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__eta_v(
    const double & _arg)
  {
    this->eta_v = _arg;
    return *this;
  }
  Type & set__eta_w(
    const double & _arg)
  {
    this->eta_w = _arg;
    return *this;
  }
  Type & set__beta(
    const double & _arg)
  {
    this->beta = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    my_robot_msgs::msg::SlipState_<ContainerAllocator> *;
  using ConstRawPtr =
    const my_robot_msgs::msg::SlipState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<my_robot_msgs::msg::SlipState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<my_robot_msgs::msg::SlipState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      my_robot_msgs::msg::SlipState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<my_robot_msgs::msg::SlipState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      my_robot_msgs::msg::SlipState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<my_robot_msgs::msg::SlipState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<my_robot_msgs::msg::SlipState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<my_robot_msgs::msg::SlipState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__my_robot_msgs__msg__SlipState
    std::shared_ptr<my_robot_msgs::msg::SlipState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__my_robot_msgs__msg__SlipState
    std::shared_ptr<my_robot_msgs::msg::SlipState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SlipState_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->eta_v != other.eta_v) {
      return false;
    }
    if (this->eta_w != other.eta_w) {
      return false;
    }
    if (this->beta != other.beta) {
      return false;
    }
    return true;
  }
  bool operator!=(const SlipState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SlipState_

// alias to use template instance with default allocator
using SlipState =
  my_robot_msgs::msg::SlipState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace my_robot_msgs

#endif  // MY_ROBOT_MSGS__MSG__DETAIL__SLIP_STATE__STRUCT_HPP_
