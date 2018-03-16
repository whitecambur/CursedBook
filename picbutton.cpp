#include "common.h"

GameController * PicButton::Root=NULL;
enum ButtonStatus{
    Normal=1,
    MouseOn,
    MousePress,
};

PicButton::PicButton(int num,int value)
{
    ButtonType=num;
    MyValue=value;
    Status=Normal;
    w=200,h=50;
}
void PicButton::setPos(int x, int y){
    DrawX=x,DrawY=y;
}

void PicButton::GetFundData(GameController * controller)
{
    Root=controller;
}
void PicButton::paint(QPainter *painter){
    QRect a(DrawX,DrawY,w,h);
    switch(Status){
    case Normal:painter->fillRect(a,Qt::yellow);break;
    case MouseOn:painter->fillRect(a,Qt::blue);break;
    case MousePress:painter->fillRect(a,Qt::green);break;
    }
}
