import os

def generate_pipe_map():
    # 地图尺寸: 600x200像素 (按0.05m分辨率，代表 30m x 10m 的空间)
    width, height = 600, 200
    
    # 初始化全图为 205 (灰色，表示未知区域)
    pixels = bytearray([205] * (width * height))
    
    # 管道尺寸对应的像素位置
    # 长度 20m -> 400像素 (X: 100 到 500)
    # 宽度 1.2m -> 24像素 (Y: 88 到 112)
    x_min, x_max = 100, 500
    y_min, y_max = 88, 112
    
    for y in range(height):
        for x in range(width):
            # 1. 管道内部道路 (255 白色，表示可通行)
            if x_min < x < x_max and y_min < y < y_max:
                pixels[y * width + x] = 255
            # 2. 管道两侧墙壁 (0 黑色，表示致命障碍物)
            elif (x_min <= x <= x_max) and (y == y_min or y == y_max):
                pixels[y * width + x] = 0
            elif (y_min <= y <= y_max) and (x == x_min or x == x_max):
                pixels[y * width + x] = 0

    # 写入标准 PGM 图片文件
    with open('pipe_map.pgm', 'wb') as f:
        f.write(b"P5\n")
        f.write(f"{width} {height}\n".encode())
        f.write(b"255\n")
        f.write(pixels)

    # 写入 Nav2 需要的 YAML 配置文件
    yaml_content = """image: pipe_map.pgm
resolution: 0.05
origin: [-5.0, -5.0, 0.0]
negate: 0
occupied_thresh: 0.65
free_thresh: 0.25
"""
    with open('pipe_map.yaml', 'w') as f:
        f.write(yaml_content)

if __name__ == '__main__':
    generate_pipe_map()
    print("✅ 成功生成真实管道地图：pipe_map.pgm 和 pipe_map.yaml")