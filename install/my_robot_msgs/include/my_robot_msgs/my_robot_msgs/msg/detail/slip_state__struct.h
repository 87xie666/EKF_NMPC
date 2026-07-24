// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_robot_msgs:msg/SlipState.idl
// generated code does not contain a copyright notice

#ifndef MY_ROBOT_MSGS__MSG__DETAIL__SLIP_STATE__STRUCT_H_
#define MY_ROBOT_MSGS__MSG__DETAIL__SLIP_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in msg/SlipState in the package my_robot_msgs.
/**
  * 带有时间戳和坐标系信息的标准头文件
 */
typedef struct my_robot_msgs__msg__SlipState
{
  std_msgs__msg__Header header;
  /// 纵向速度执行效率 (范围通常为 0.0 ~ 1.0, 1.0表示完美抓地无打滑)
  double eta_v;
  /// 转向执行效率 (范围通常为 0.0 ~ 1.0)
  double eta_w;
  /// 侧滑角 Sideslip angle (单位：rad，质心实际运动方向与车头朝向的夹角)
  double beta;
} my_robot_msgs__msg__SlipState;

// Struct for a sequence of my_robot_msgs__msg__SlipState.
typedef struct my_robot_msgs__msg__SlipState__Sequence
{
  my_robot_msgs__msg__SlipState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_robot_msgs__msg__SlipState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_ROBOT_MSGS__MSG__DETAIL__SLIP_STATE__STRUCT_H_
