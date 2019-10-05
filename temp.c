/*本程序用于迭代计算二位平板温度分布其中网格划分必须满足Δx=Δy*/

#include <stdio.h>
#define X 7                    //定义水平划分X-1个网格
#define Y 7                    //定义垂直划分Y-1个网格
#define MAX_DEVIATION 0.000001 //定义最大误差
#define F_PATH "./file.csv"    //可选保存的csv文件及位置

/*传入数组返回其中的最大值*/
double get_max(double deviations[X - 2][Y - 2])
{
    double max = deviations[0][0];
    int i, j;
    for (i = 0; i < X - 2; i++)
    {
        for (j = 0; j < Y - 2; j++)
        {
            if (deviations[i][j] > max)
            {
                max = deviations[i][j];
            }
        }
    }
    return max;
}

/*对双精度型浮点数取绝对值*/
double fbs(double num)
{
    if (num > 0)
    {
        return num;
    }
    else
    {
        return -num;
    }
}

/*打印X*Y的数组*/
void print_array(double temps[X][Y])
{
    int i, j;
    for (i = 0; i < X; i++)
    {
        printf("\n");
        for (j = 0; j < Y; j++)
        {
            printf("%f\t", temps[i][j]);
        }
    }
}

/*将X*Y的数组输出到文件F_PATH中*/
void save_csv(double temps[X][Y])
{
    int i, j;
    FILE *fp = NULL;
    fp = fopen(F_PATH, "w+");
    for (i = 0; i < X; i++)
    {
        for (j = 0; j < Y; j++)
        {
            if (j < Y - 1)
            {
                fprintf(fp, "%f,", temps[i][j]);
            }
            else
            {
                fprintf(fp, "%f", temps[i][j]);
            }
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    fp = NULL;
}

/*主函数入口*/
int main()
{
    double temps[X][Y];                                                         //定义温度矩阵
    int i, j;                                                                   //循环时的横纵坐标
    double up_temp = 0.0, down_temp = 0.0, left_temp = 100.0, right_temp = 0.0; //定义上下左右的边界温度
    double delt = fbs((left_temp - right_temp) / (X - 1));                      //左边界到右边界的温度步长

    /*为整个温度矩阵赋初始值*/
    for (i = 0; i < X; i++)
    {
        for (j = 0; j < Y; j++)
        {
            if (i == 0)
            {
                temps[i][j] = up_temp;
            }
            else
            {
                if (i == Y - 1)
                {
                    temps[i][j] = down_temp;
                }
                else
                {
                    temps[i][j] = left_temp - j * delt;
                }
            }
        }
    }

    /*做一个矩阵副本用于计算迭代前后的误差*/
    double tmp[X][Y];
    for (i = 0; i < X; i++)
    {
        for (j = 0; j < Y; j++)
        {
            tmp[i][j] = temps[i][j];
        }
    }

    /*开始迭代当误差deviation<MAX_DEVIATION时迭代停止其中tmp为迭代前的温度矩阵temps为迭代后的温度矩阵*/
    int counter = 0;                 //统计迭代次数
    double deviation = 1;            // 定义迭代前后的误差
    double deviations[X - 2][Y - 2]; // 除去边界外的矩阵
    while (deviation > MAX_DEVIATION)
    {

        for (i = 1; i < X - 1; i++)
        {
            for (j = 1; j < Y - 1; j++)
            {
                temps[i][j] = (temps[i - 1][j] + temps[i + 1][j] + temps[i][j - 1] + temps[i][j + 1]) / 4;
                deviations[i - 1][j - 1] = fbs((temps[i][j] - tmp[i][j]) / tmp[i][j]);
            }
        }
        deviation = get_max(deviations);
        for (i = 0; i < X; i++)
        {
            for (j = 0; j < Y; j++)
            {
                tmp[i][j] = temps[i][j];
            }
        }
        counter++;
    }
    print_array(temps);
    printf("\n%d\n", counter);

    //save_csv(temps); //保存为csv文件，文件名为F_PATH去掉注释即可保存
}