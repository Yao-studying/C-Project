#define _CRT_SECURE_NO_WARNINGS
#include "data.h"

int map[Line][Clom] = {}; // ��ʼ���ڰ����ݵ�����,�����ڻ��ƺ�������
MOUSEMSG mouse;           // ����һ�������Ϣ����
int score = 0;            // �÷ֳ�ʼ��

// ���ƺ���(����������������ֵ�Ƿ�Ϊ0,Ϊ0����ư׿�)
void Draw(int Map[Line][Clom])
{
    // ����
    cleardevice();

    // �����׷���
    for (int i = 0; i < Line; i++)
    {
        for (int j = 0; j < Clom; j++)
        {
            if (map[i][j] == 0)
            {
                // ���һ�е�����ɫ
                setlinecolor(BLACK);
                if (i == Line - 1)
                    setlinecolor(GREEN);

                fillrectangle(j * 75, i * 125, 75 + j * 75, 125 + i * 125);
            }
        }
    }

    // ÿ��ˢ�½����0.3s����
    Sleep(300);
}

// ���к���
void Run()
{
    // ȫ������һ��
    for (int i = Line; i > 1; i--)
    {
        for (int j = 0; j < Clom; j++)
        {
            map[i - 1][j] = map[i - 2][j];
        }
    }

    // ��һ��ȫ��,���������һ����
    for (int j = 0; j < Clom; j++)
    {
        map[0][j] = 0;
    }
    map[0][rand() % Clom] = 1;
}

int main()
{

    // 1.��������,���÷����߿���ɫΪ��,�����������,���Ʊ���    ��λ:px(����)
    initgraph(GameWidth, GameHeight);
    srand((unsigned)time(NULL));

    // 2.����ɫ����,��ɫ�����½����ײ��ȴ��û����
    for (int q = 0; q < Line; q++)
    {
        Run();
        Draw(map);
    }

    // 3.������������Ϣ
    while (1)
    {
        mouse = GetMouseMsg();
        if (mouse.uMsg == WM_LBUTTONDOWN)
        {
            // 1.����������껻���map�����±�(mouse.y / 125,mouse.x / 75)
            // add:y������,������׸��,��Ϊһ�����Ϊ ���� ��Ӧ xy

            // 2.�жϸ�������0����1:��0-->break;��1-->runһ��,��һ��
            if (map[mouse.y / 125][mouse.x / 75] == 1 && mouse.y / 125 == 6)
            {
                Run();
                Draw(map);
                ++score;
            }
            else
            {
                printf("ʧ����!�������յ÷�Ϊ%d", score);
                break;
            }
        }
        else if (mouse.uMsg == WM_RBUTTONDOWN)
        {
            printf("����������Ϸ,���յ÷�Ϊ%d", score);
            break;
        }
    }

    return 0;
}