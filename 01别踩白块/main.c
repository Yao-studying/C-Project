#define _CRT_SECURE_NO_WARNINGS
#include "data.h"

int map[Line][Clom] = {}; // 初始化黑白数据的数组,必须在绘制函数上面
MOUSEMSG mouse;           // 定义一个鼠标信息变量
int score = 0;            // 得分初始化

// 绘制函数(遍历传入的数组各个值是否为0,为0则绘制白块)
void Draw(int Map[Line][Clom])
{
    // 清屏
    cleardevice();

    // 遍历白方块
    for (int i = 0; i < Line; i++)
    {
        for (int j = 0; j < Clom; j++)
        {
            if (map[i][j] == 0)
            {
                // 最后一行调成绿色
                setlinecolor(BLACK);
                if (i == Line - 1)
                    setlinecolor(GREEN);

                fillrectangle(j * 75, i * 125, 75 + j * 75, 125 + i * 125);
            }
        }
    }

    // 每次刷新界面给0.3s缓冲
    Sleep(300);
}

// 运行函数
void Run()
{
    // 全部下移一行
    for (int i = Line; i > 1; i--)
    {
        for (int j = 0; j < Clom; j++)
        {
            map[i - 1][j] = map[i - 2][j];
        }
    }

    // 第一行全白,并随机设置一个黑
    for (int j = 0; j < Clom; j++)
    {
        map[0][j] = 0;
    }
    map[0][rand() % Clom] = 1;
}

int main()
{

    // 1.创建界面,设置方块线框颜色为黑,设置随机规则,绘制背景    单位:px(像素)
    initgraph(GameWidth, GameHeight);
    srand((unsigned)time(NULL));

    // 2.出白色背景,黑色方块下降到底部等待用户点击
    for (int q = 0; q < Line; q++)
    {
        Run();
        Draw(map);
    }

    // 3.持续监测鼠标信息
    while (1)
    {
        mouse = GetMouseMsg();
        if (mouse.uMsg == WM_LBUTTONDOWN)
        {
            // 1.将鼠标点击坐标换算成map数组下标(mouse.y / 125,mouse.x / 75)
            // add:y才是行,这个容易搞混,因为一般会以为 行列 对应 xy

            // 2.判断该数组是0还是1:是0-->break;是1-->run一次,加一分
            if (map[mouse.y / 125][mouse.x / 75] == 1 && mouse.y / 125 == 6)
            {
                Run();
                Draw(map);
                ++score;
            }
            else
            {
                printf("失误了!您的最终得分为%d", score);
                break;
            }
        }
        else if (mouse.uMsg == WM_RBUTTONDOWN)
        {
            printf("您放弃了游戏,最终得分为%d", score);
            break;
        }
    }

    return 0;
}