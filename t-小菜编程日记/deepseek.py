import pygame
import math

# 初始化 Pygame
pygame.init()
screen = pygame.display.set_mode((800, 600))
white = (255, 255, 255)
red = (255, 0, 0)

# 六边形参数
hex_center = [400, 300]  # 六边形中心
hex_side_length = 100    # 六边形边长
hex_angle = 0            # 六边形旋转角度
hex_rotation_speed = 1   # 旋转速度（度/帧）

# 小球参数
ball_pos = [400, 300]    # 小球初始位置（中心）
ball_vel = [5, 3]        # 小球初速度
ball_radius = 10         # 小球半径
min_velocity = 0.1       # 最小速度阈值
friction = 0.98          # 摩擦系数（每帧速度衰减）

# 向量操作函数
def vector_magnitude(v):
    return math.sqrt(v[0]**2 + v[1]**2)

def normalize_vector(v):
    mag = vector_magnitude(v)
    if mag == 0:
        return [0, 0]
    return [v[0] / mag, v[1] / mag]

def dot_product(v1, v2):
    return v1[0] * v2[0] + v1[1] * v2[1]

# 绘制六边形并返回顶点
def draw_hexagon(surface, color, center, size, angle_deg):
    points = []
    for i in range(6):
        angle_rad = math.radians(angle_deg + 60 * i)
        x = center[0] + size * math.cos(angle_rad)
        y = center[1] + size * math.sin(angle_rad)
        points.append([x, y])
    pygame.draw.polygon(surface, color, points, 2)  # 绘制边框
    return points

# 碰撞检测与响应
def check_and_handle_collision(pos, vel, hex_points):
    collision_occurred = False
    for i in range(len(hex_points)):
        p1 = hex_points[i]
        p2 = hex_points[(i + 1) % len(hex_points)]

        # 线段向量 AB 和 AP
        AB = [p2[0] - p1[0], p2[1] - p1[1]]
        AP = [pos[0] - p1[0], pos[1] - p1[1]]

        # 归一化 AB
        e = normalize_vector(AB)
        projection_length = dot_product(AP, e)

        # 确定最近点
        if projection_length < 0:
            closest_point = p1
        elif projection_length > vector_magnitude(AB):
            closest_point = p2
        else:
            closest_point = [p1[0] + e[0] * projection_length, p1[1] + e[1] * projection_length]

        # 距离检测
        PC = [pos[0] - closest_point[0], pos[1] - closest_point[1]]
        distance = vector_magnitude(PC)

        if distance < ball_radius:
            collision_occurred = True
            # 计算法向量
            normal = normalize_vector([-PC[1], PC[0]])  # 垂直于边的法向量
            if dot_product(normal, vel) > 0:  # 确保法线指向小球外
                normal = [-normal[0], -normal[1]]

            # 移动小球以消除重叠
            overlap = ball_radius - distance
            pos[0] += normal[0] * overlap
            pos[1] += normal[1] * overlap

            # 反射速度（弹性碰撞）
            v_dot_n = dot_product(vel, normal)
            vel[0] -= 2 * v_dot_n * normal[0]
            vel[1] -= 2 * v_dot_n * normal[1]

            # 应用摩擦力（沿切线方向衰减）
            tangent = [-normal[1], normal[0]]
            v_dot_t = dot_product(vel, tangent)
            vel[0] = v_dot_t * tangent[0] * friction + dot_product(vel, normal) * normal[0]
            vel[1] = v_dot_t * tangent[1] * friction + dot_product(vel, normal) * normal[1]

    return collision_occurred

# 主循环
def main():
    clock = pygame.time.Clock()
    running = True

    while running:
        screen.fill(white)

        # 处理事件
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # 更新六边形角度
        global hex_angle
        hex_angle += hex_rotation_speed
        hex_points = draw_hexagon(screen, red, hex_center, hex_side_length, hex_angle)

        # 移动小球
        ball_pos[0] += ball_vel[0]
        ball_pos[1] += ball_vel[1]

        # 碰撞检测和处理
        check_and_handle_collision(ball_pos, ball_vel, hex_points)

        # 应用摩擦力（全局衰减）
        ball_vel[0] *= friction
        ball_vel[1] *= friction

        # 检查速度是否低于阈值
        if vector_magnitude(ball_vel) < min_velocity:
            ball_vel[0] = 0
            ball_vel[1] = 0

        # 绘制小球
        pygame.draw.circle(screen, (0, 0, 255), (int(ball_pos[0]), int(ball_pos[1])), ball_radius)

        pygame.display.flip()
        clock.tick(60)

    pygame.quit()

if __name__ == "__main__":
    main()