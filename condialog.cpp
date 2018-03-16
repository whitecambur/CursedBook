#include "common.h"

ConDialog::ConDialog(QWidget*p)
{
    //setParent(p);
}
void ConDialog::SetMessage(int PicNum,QString&msg){
    MyPicNum = PicNum;
    MyMsg = msg;
}
void ConDialog::paintEvent(QPaintEvent *event){
     QPainter painter(this);
     int a = MyMsg.length()/8;
     for(int i=0;i<=a;i++){
        painter.drawText(50,50+30*i,MyMsg.mid(i*8,8));
     }
}
