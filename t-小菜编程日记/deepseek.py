import pygame
import math

# 初始化pygame
pygame.init()

# 设置画布大小
WIDTH, HEIGHT = 800, 600
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("六边形和小球弹跳")

# 定义颜色
RED = (231, 76, 60)  # 六边形颜色
BLUE = (52, 152, 219)  # 小球颜色
WHITE = (255, 255, 255)  # 背景颜色

# 六边形参数
HEX_RADIUS = 100  # 六边形半径
HEX_CENTER = (WIDTH // 2, HEIGHT // 2)  # 六边形中心
hex_angle = 0  # 六边形旋转角度
hex_rotation_speed = 0.01  # 六边形旋转速度

# 小球参数
BALL_RADIUS = 10
ball_pos = [HEX_CENTER[0], HEX_CENTER[1]]  # 小球初始位置在六边形中心
ball_vel = [0, 0]  # 小球初始速度
gravity = 0.1  # 重力
friction = 0.99  # 摩擦系数

# 设置帧率
clock = pygame.time.Clock()

# 计算六边形的顶点
def draw_hexagon(center, radius, angle):
    points = []
    for i in range(6):
        x = center[0] + radius * math.cos(angle + i * math.pi / 3)
        y = center[1] + radius * math.sin(angle + i * math.pi / 3)
        points.append((x, y))
    pygame.draw.polygon(screen, RED, points)
    pygame.draw.polygon(screen, WHITE, points, 2)  # 添加边框
    return points

# 处理小球与六边形的碰撞
def handle_ball_collision(ball_pos, ball_vel, hex_points):
    for i in range(6):
        p1 = hex_points[i]
        p2 = hex_points[(i + 1) % 6]
        
        # 向量 AB 和 AC
        AB = [p2[0] - p1[0], p2[1] - p1[1]]
        AP = [ball_pos[0] - p1[0], ball_pos[1] - p1[1]]
        
        # 投影长度
        e = normalize_vector(AB)
        projection_length = e[0] * AP[0] + e[1] * AP[1]
        
        if projection_length < 0:
            closest_point = p1
        elif projection_length > vector_magnitude(AB):
            closest_point = p2
        else:
            closest_point = [p1[0] + e[0] * projection_length, p1[1] + e[1] * projection_length]
        
        # 向量 PC
        PC = [closest_point[0] - ball_pos[0], closest_point[1] - ball_pos[1]]
        distance = vector_magnitude(PC)
        
        if distance < BALL_RADIUS:
            # 计算法线
            normal = [-PC[1], PC[0]]
            normal = normalize_vector(normal)
            
            # 反射速度
            dot_product = ball_vel[0] * normal[0] + ball_vel[1] * normal[1]
            ball_vel[0] -= 2 * dot_product * normal[0]
            ball_vel[1] -= 2 * dot_product * normal[1]
            
            # 摩擦力
            ball_vel[0] *= friction
            ball_vel[1] *= friction
            
            # 移动小球以避免穿透
            overlap = BALL_RADIUS - distance
            ball_pos[0] += normal[0] * overlap
            ball_pos[1] += normal[1] * overlap

# 计算向量的大小
def vector_magnitude(v):
    return math.sqrt(v[0]**2 + v[1]**2)

# 规范化向量
def normalize_vector(v):
    mag = vector_magnitude(v)
    if mag == 0:
        return [0, 0]
    return [v[0] / mag, v[1] / mag]

# 更新小球的位置
def update_ball():
    ball_vel[1] += gravity  # 重力
    ball_pos[0] += ball_vel[0]
    ball_pos[1] += ball_vel[1]

# 检查小球是否在六边形内
def check_ball_in_hexagon(ball_pos, hex_points):
    for i in range(6):
        p1 = hex_points[i]
        p2 = hex_points[(i + 1) % 6]
        
        # 向量 AB 和 AC
        AB = [p2[0] - p1[0], p2[1] - p1[1]]
        AP = [ball_pos[0] - p1[0], ball_pos[1] - p1[1]]
        
        # 投影长度
        e = normalize_vector(AB)
        projection_length = e[0] * AP[0] + e[1] * AP[1]
        
        if projection_length < 0 or projection_length > vector_magnitude(AB):
            return False  # 小球在六边形外
        
    return True  # 小球在六边形内

# 主函数
def main():
    global ball_pos
    global ball_vel
    global hex_angle
    running = True
    while running:
        screen.fill(WHITE)

        # 事件处理
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # 更新六边形角度
        hex_angle += hex_rotation_speed

        # 绘制六边形并计算顶点
        hex_points = draw_hexagon(HEX_CENTER, HEX_RADIUS, hex_angle)

        # 更新小球的位置
        update_ball()

        # 检查小球是否与六边形发生碰撞
        handle_ball_collision(ball_pos, ball_vel, hex_points)

        # 如果小球跑出了六边形边界，重置其位置
        if not check_ball_in_hexagon(ball_pos, hex_points):
            ball_pos = [HEX_CENTER[0], HEX_CENTER[1]]  # 重新设置小球位置为六边形中心
            ball_vel = [0, 0]  # 重置速度

        # 绘制小球
        pygame.draw.circle(screen, BLUE, (int(ball_pos[0]), int(ball_pos[1])), BALL_RADIUS)

        pygame.display.flip()
        clock.tick(60)  # 设置帧率为60

    pygame.quit()

if __name__ == "__main__":
    main()
    print("new file")
