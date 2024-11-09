#include<stdio.h>
#include<graphics.h>
#include<windows.h>
#include<time.h>

//全局数据
#define GameWidth 450
#define GameHeight 875
#define Line 7
#define Clom 6

//界面生成函数
void Draw(int Map[Line][Clom]);
//运行函数
void Run();