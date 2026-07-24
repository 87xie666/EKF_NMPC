import casadi as ca
import os

def generate_mpc():
    # 系统与预测时域参数
    N = 20
    dt = 0.1
    
    # 状态变量 [x, y, theta]
    x = ca.SX.sym('x')
    y = ca.SX.sym('y')
    theta = ca.SX.sym('theta')
    states = ca.vertcat(x, y, theta)
    n_states = states.numel()
    
    # 控制变量 [v, w]
    v = ca.SX.sym('v')
    w = ca.SX.sym('w')
    controls = ca.vertcat(v, w)
    n_controls = controls.numel()
    
    # 滑移参数 (外部传入)
    eta_v = ca.SX.sym('eta_v')
    eta_w = ca.SX.sym('eta_w')
    beta  = ca.SX.sym('beta')
    params = ca.vertcat(eta_v, eta_w, beta)
    
    # 打滑运动学模型
    rhs = ca.vertcat(
        eta_v * v * ca.cos(theta + beta),
        eta_v * v * ca.sin(theta + beta),
        eta_w * w
    )
    f = ca.Function('f', [states, controls, params], [rhs])
    
    # 优化问题构建
    U = ca.SX.sym('U', n_controls, N)
    X = ca.SX.sym('X', n_states, N+1)
    P = ca.SX.sym('P', n_states + 3) # [x0, y0, theta0, eta_v, eta_w, beta]
    
    cost = 0
    g = []
    
    # 初始状态约束
    g.append(X[:, 0] - P[0:3])
    
    # 权重矩阵
    Q = ca.diag([10.0, 10.0, 1.0])
    R = ca.diag([0.5, 0.1])
    
    for k in range(N):
        st = X[:, k]
        con = U[:, k]
        p_slip = P[3:6]
        
        # 简化版代价：使其尽量靠近原点（工程中应改为跟随局部参考轨迹）
        cost += ca.mtimes([st.T, Q, st]) + ca.mtimes([con.T, R, con])
        
        # 欧拉法前向积分约束
        st_next_euler = st + dt * f(st, con, p_slip)
        g.append(X[:, k+1] - st_next_euler)
        
    g = ca.vertcat(*g)
    OPT_variables = ca.vertcat(ca.reshape(X, -1, 1), ca.reshape(U, -1, 1))
    
    nlp = {'f': cost, 'x': OPT_variables, 'g': g, 'p': P}
    opts = {
        'ipopt.print_level': 0,
        'print_time': 0,
        'ipopt.tol': 1e-3,
        'ipopt.max_iter': 50
    }
    
    solver = ca.nlpsol('nmpc_solver', 'ipopt', nlp, opts)
    
    output_file = "nmpc_solver.c"
    solver.generate_dependencies(output_file)
    print(f"[{output_file}] has been generated successfully. Move it to the src/ directory.")

if __name__ == '__main__':
    generate_mpc()