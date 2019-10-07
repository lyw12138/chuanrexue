/*���������ڵ��������λƽ���¶ȷֲ��������񻮷ֱ������㦤x=��y*/

#include <stdio.h>
#include <math.h>
#define X 7                    //����ˮƽ����X-1������
#define Y 7                    //���崹ֱ����Y-1������
#define MAX_DEVIATION 0.000001 //����������
#define F_PATH "./file.csv"    //��ѡ�����csv�ļ���λ��

/*�������鷵�����е����ֵ*/
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

/*��ӡX*Y������*/
void print_array(double temps[X][Y])
{
    int i, j;
    for (i = 0; i < X; i++)
    {
        printf("\n");
        for (j = 0; j < Y; j++)
        {
            printf("%.2f\t", temps[i][j]);
        }
    }
}

/*��X*Y������������ļ�F_PATH��*/
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

/*���������*/
int main()
{
    double temps[X][Y];                                                         //�����¶Ⱦ���
    int i, j;                                                                   //ѭ��ʱ�ĺ�������
    double up_temp = 0.0, down_temp = 0.0, left_temp = 100.0, right_temp = 0.0; //�����������ҵı߽��¶�
    double delt = fabs((left_temp - right_temp) / (X - 1));                     //��߽絽�ұ߽���¶Ȳ���

    /*Ϊ�����¶Ⱦ��󸳳�ʼֵ*/
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
    printf("��ʼ�¶ȳ�Ϊ:");
    print_array(temps);

    /*��һ�����󸱱����ڼ������ǰ������*/
    double tmp[X][Y];
    for (i = 0; i < X; i++)
    {
        for (j = 0; j < Y; j++)
        {
            tmp[i][j] = temps[i][j];
        }
    }

    /*��ʼ���������deviation<MAX_DEVIATIONʱ����ֹͣ����tmpΪ����ǰ���¶Ⱦ���tempsΪ��������¶Ⱦ���*/
    int counter = 0;                 //ͳ�Ƶ�������
    double deviation = 1;            // �������ǰ������
    double deviations[X - 2][Y - 2]; // ��ȥ�߽���ľ���
    while (deviation > MAX_DEVIATION)
    {

        for (i = 1; i < X - 1; i++)
        {
            for (j = 1; j < Y - 1; j++)
            {
                temps[i][j] = (temps[i - 1][j] + temps[i + 1][j] + temps[i][j - 1] + temps[i][j + 1]) / 4;
                deviations[i - 1][j - 1] = fabs((temps[i][j] - tmp[i][j]) / tmp[i][j]);
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
    printf("\n�����¶ȳ�Ϊ:");
    print_array(temps);
    printf("\n��������Ϊ:%d\n", counter);
    printf("���ε�����������������Ϊ:%f", MAX_DEVIATION);

    //save_csv(temps); //����Ϊcsv�ļ����ļ���ΪF_PATHȥ��ע�ͼ��ɱ���
}