"""本程序用于迭代计算二位平板温度分布其中网格划分必须满足Δx=Δy"""
import numpy as np

# 设置划分的网格数(X-1)*(Y-1)，默认X=Y，修改该处的值可改变划分的网格数
X = Y = 7
# 设置收敛误差限
MAX_DEVIATION = 10**(-6)
# 上下左右的初始温度
LEFT_TEMP = 100
RIGHT_TEMP = 0
UP_TEMP = 0
DOWN_TEMP = 0

# 生成初始温度矩阵
temps = np.vstack([np.linspace(UP_TEMP, UP_TEMP, X), np.tile(
    np.linspace(LEFT_TEMP, RIGHT_TEMP, X), [Y-2, 1]), np.linspace(DOWN_TEMP, DOWN_TEMP, X)])

# 温度迭代计算函数，传入温度矩阵返回最大相对误差deviation及迭代一次后的矩阵tmp


def temp_iterator(temps):
    max_x, max_y = np.shape(temps)
    tmp = temps.copy()
    for x in range(1, max_x-1):
        for y in range(1, max_x-1):
            tmp[x][y] = (tmp[x-1][y]+tmp[x+1][y]+tmp[x][y-1]+tmp[x][y+1])/4
    deviation = (temps[1:max_x-1, 1:max_y-1]-tmp[1:max_x -
                                                 1, 1:max_y-1])/temps[1:max_x-1, 1:max_y-1]
    deviation = np.max(deviation)
    return deviation, tmp


# 统计迭代次数
counter = 0
# 循环迭代直到误差小于最大误差限
while True:
    deviation, temps = temp_iterator(temps)
    counter = counter + 1
    if deviation < MAX_DEVIATION:
        break
# 打印迭代次数及最终矩阵
np.set_printoptions(precision=3)
print(counter)
print(temps)
