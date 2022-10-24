#include <iostream>
#include <graphics.h>
#include <conio.h>
using namespace std;
#define H 22
#define W 22
#define Block_Size 20

int block[H][W] = {-1};
int isFailure = 0;
int food_i,food_j,moveDirection;

void initialize(){
    for(int i = 0; i < 5 ; i++)
        block[H/2][W/2 - i] = i+1;

    food_i = rand() % (H-5) + 2;
    food_j = rand() % (W-5) + 2;
    moveDirection = 80;
    initgraph(W * Block_Size , H * Block_Size);
    setlinecolor(RGB(200,200,200));
    BeginBatchDraw();
}

void move(){
    int i,j,max = 0;
    int newHead_i,newHead_j,oldHead_i,oldHead_j,oldTail_i,oldTail_j;
    for(i=0 ;i<H ;i++)
        for(j=0 ;j<W ;j++){
            if(block[i][j] > 0)
                block[i][j]++;
            else
                continue;
            if(block[i][j] == 2){
                oldHead_i = i;
                oldHead_j = j;
            }
            if(max < block[i][j]){
                max = block[i][j];
                oldTail_i = i;
                oldTail_j = j;
            }
        }
    newHead_i = oldHead_i;
    newHead_j = oldHead_j;
    //72 UP 80 DOWN 75 LEFT 77 RIGHT
    switch (moveDirection) {
        case 72: newHead_i = oldHead_i - 1;
            break;
        case 80: newHead_i = oldHead_i + 1;
            break;
        case 75: newHead_j = oldHead_j - 1;
            break;
        case 77: newHead_j = oldHead_j + 1;
            break;
        default:
            break;
    }
    if (newHead_i < 1 || newHead_i >= H || newHead_j < 1 || newHead_j >= W || block[newHead_i][newHead_j])
    {
        isFailure = 1;
        return;
    }
    block[newHead_i][newHead_j] = 1;
    if (newHead_i == food_i && newHead_j == food_j)
    {
        food_i = rand() % (H-5) + 2;
        food_j = rand() % (W-5) + 2;
    }
    else
        block[oldTail_i][oldTail_j] = 0;

}

void show(){
    cleardevice();
    int i,j;
    for(i=0 ;i<H ;i++){
        for(j=0 ;j<W ;j++){
            if(block[i][j] > 0)
                setfillcolor(HSVtoRGB(block[i][j]*10,0.9,1));
            else
                setfillcolor(RGB(150,150,150));
            fillrectangle(j * Block_Size, i * Block_Size, (j+1) * Block_Size , (i+1) * Block_Size);
        }
    }

    setfillcolor(RGB(0,255,0));
    fillrectangle(food_j * Block_Size , food_i * Block_Size , (food_j+1) * Block_Size , (food_i+1)* Block_Size);
    if (isFailure)
    {
        setbkmode(TRANSPARENT);
        settextcolor(RGB(255,0,0));
        settextstyle(80,0,_T("宋体"));
        outtextxy(240,220,_T("Fail"));
    }
    FlushBatchDraw();
}

void updateWithoutInput(){
    if (isFailure)
        return;
    static int waitIndex = 1;
    waitIndex ++;
    if(waitIndex == 100){
        move();
        waitIndex = 1;
    }
//    move();
//    Sleep(100);
}

void updateWithInput(){
    if(_kbhit()&&isFailure == 0)
        if (getch() == 224)
        {
            moveDirection = getch();
            move();
        }
}

int main() {
    initialize();
    while(1)
    {
        show();
        updateWithoutInput();
        updateWithInput();
    }
    cout << "Hello, World!" << endl;
    return 0;
}
