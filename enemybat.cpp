#include "common.h"
enum EnemyBatStatus
{
    Attack=5,
};
int EnemyBat::AttTime = TimeUnit;
EnemyBat::EnemyBat(int X,int Y)
{
    Name = "蝙蝠";
    MapX=X,MapY=Y;
    MyType = Type_EnemyBat;
    DieTime = 0.5*TimeUnit;
    WalkTime = TimeUnit;
    RetreatTime = 0.5*TimeUnit;
    HP=MaxHP=20;
    MyToward = DOWN;
    PhyAtk = 5;
    MagAtk = 1;
    PhyDef = 0;
    MagDef = 0;
}
void EnemyBat::AIAction()
{
    if(Status==Stand)
    {
        if(Root->GetHeroX()==MapX+1){
            MyToward=RIGHT;
            Status=Attack;
            MyTimer=AttTime;
        }else if(Root->GetHeroX()==MapX-1){
            MyToward=LEFT;
            Status=Attack;
            MyTimer=AttTime;
        }else if(Root->GetHeroY()==MapY+1){
            MyToward=DOWN;
            Status=Attack;
            MyTimer=AttTime;
        }else if(Root->GetHeroY()==MapY-1){
            MyToward=UP;
            Status=Attack;
            MyTimer=AttTime;
        }else
        {
            if(Root->GetHeroX()>MapX)
            {
                MyToward=RIGHT;
                Status=Walk;
                MyTimer=WalkTime;
            }
            if(Root->GetHeroX()<MapX)
            {
                MyToward=LEFT;
                Status=Walk;
                MyTimer=WalkTime;
            }
            if(Root->GetHeroY()>MapY)
            {
                MyToward=DOWN;
                Status=Walk;
                MyTimer=WalkTime;
            }
            if(Root->GetHeroY()<MapY)
            {
                MyToward=UP;
                Status=Walk;
                MyTimer=WalkTime;
            }
            if(Status==Stand){

            }
        }
    }
}
void EnemyBat::EnemyConcreteAction()
{
    switch(Status)
    {
    case Attack:
        switch(MyToward){
        case UP:MyMap->GetTouch(MapX,MapY-1,AtkVisit,this,PreDamage(PhyAtk,MagAtk));break;
        case DOWN:MyMap->GetTouch(MapX,MapY+1,AtkVisit,this,PreDamage(PhyAtk,MagAtk));break;
        case LEFT:MyMap->GetTouch(MapX-1,MapY,AtkVisit,this,PreDamage(PhyAtk,MagAtk));break;
        case RIGHT:MyMap->GetTouch(MapX+1,MapY,AtkVisit,this,PreDamage(PhyAtk,MagAtk));break;
        }
        break;
    }
}
void EnemyBat::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

}
