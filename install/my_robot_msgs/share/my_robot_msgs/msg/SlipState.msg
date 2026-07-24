# 带有时间戳和坐标系信息的标准头文件
std_msgs/Header header

# 纵向速度执行效率 (范围通常为 0.0 ~ 1.0, 1.0表示完美抓地无打滑)
float64 eta_v  

# 转向执行效率 (范围通常为 0.0 ~ 1.0)
float64 eta_w  

# 侧滑角 Sideslip angle (单位：rad，质心实际运动方向与车头朝向的夹角)
float64 beta