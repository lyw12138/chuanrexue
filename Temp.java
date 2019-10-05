/*本程序用于迭代计算二位平板温度分布其中网格划分必须满足Δx=Δy*/
public class Temp {
    public static void main(String[] args) {
        double MAX_DEVIATION = 0.000001;// 定义最大误差
        int X = 7, Y = 7;// 定义水平划分X-1个网格，垂直划分Y-1个网格，修改该处的值可改变网格划分的数量
        double[][] temps = new double[X][Y];// 定义温度矩阵
        int i, j;// 循环时的横纵坐标
        double up_temp = 0.0, down_temp = 0.0, left_temp = 100.0, right_temp = 0.0;// 定义上下左右的边界温度
        double delt = Math.abs((left_temp - right_temp) / (X - 1));// 左边界到右边界的温度步长

        /* 为整个温度矩阵赋初始值 */
        for (i = 0; i < X; i++) {
            for (j = 0; j < Y; j++) {
                if (i == 0) {
                    temps[i][j] = up_temp;
                } else {
                    if (i == Y - 1) {
                        temps[i][j] = down_temp;
                    } else {
                        temps[i][j] = left_temp - j * delt;
                    }
                }
            }
        }

        /* 做一个矩阵副本用于计算迭代前后的误差 */
        double[][] tmp = new double[X][Y];
        for (i = 0; i < temps.length; i++) {
            tmp[i] = temps[i].clone();
        }

        int counter = 0;// 统计迭代次数
        double deviation = 1;// 定义迭代前后的误差
        double[][] deviations = new double[X - 2][Y - 2];// 除边界外的矩阵
        /* 开始迭代当误差deviation<MAX_DEVIATION时迭代停止其中tmp为迭代前的温度矩阵temps为迭代后的温度矩阵 */
        while (deviation >= MAX_DEVIATION) {
            for (i = 1; i < X - 1; i++) {
                for (j = 1; j < Y - 1; j++) {
                    temps[i][j] = (temps[i - 1][j] + temps[i + 1][j] + temps[i][j - 1] + temps[i][j + 1]) / 4;
                    deviations[i - 1][j - 1] = Math.abs((temps[i][j] - tmp[i][j]) / tmp[i][j]);
                }
            }
            counter++;
            deviation = get_max(deviations);
            for (i = 0; i < X; i++) {
                for (j = 0; j < Y; j++) {
                    tmp[i][j] = temps[i][j];
                }
            }
            for (i = 0; i < X; i++) {
                for (j = 0; j < Y; j++) {
                    System.out.printf("%f\t", temps[i][j]);
                }
                System.out.println();
            }
        }
        /* 打印最终结果 */
        for (i = 0; i < X; i++) {
            for (j = 0; j < Y; j++) {
                System.out.printf("%f\t", temps[i][j]);
            }
            System.out.println();
        }
        System.out.println(counter);
    }

    /* 定义静态方法传入二维数组返回其中的最大值 */
    public static double get_max(double[][] deviations) {
        int Y = deviations.length;
        int X = deviations[0].length;
        double max = deviations[0][0];
        int i, j;
        for (i = 0; i < X; i++) {
            for (j = 0; j < Y; j++) {
                if (deviations[i][j] > max) {
                    max = deviations[i][j];
                }
            }
        }
        return max;
    }
}