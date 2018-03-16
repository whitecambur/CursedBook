#include"resource.h"

QPixmap*GameMenuPic;
QPixmap*HeroPic;
QPixmap*HeroStandPic[4];
QPixmap*HeroWalkPic[32];
QString NPCConversation[5]={
    "你好",
    "欢迎你",
    "我很高兴",
    "hhh",
    "#"
};
void LoadPic(){
    HeroPic=new QPixmap("./image/MapItems/Hero.png");
    GameMenuPic=new QPixmap("./image/UI/GameMenu.png");
    for(int i=0;i<4;i++){
        HeroStandPic[i]=new QPixmap(HeroPic->copy(50*i,0,50,50));
    }
    for(int i=0;i<32;i++){
        HeroWalkPic[i]=new QPixmap(HeroPic->copy(50*(i%8),50+50*(i/8),50,50));
    }
}
