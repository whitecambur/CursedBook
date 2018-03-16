#include "common.h"

NPC::NPC()
{
    MapX=0;
    MapY=0;
    ConversationStep=0;
}
NPC::NPC(int type,int MapNum,int x,int y,int Toward,int taskstep)
{
    MyType=type;
    MapCur=MapNum;
    MapX=x;
    MapY=y;
    MyToward=Toward;
    TaskStep=taskstep;
    ConversationStep=0;
}

int NPC::GetTouch(int TouchType, MapItem *Toucher, int HurtData, int addons, int addonsData)
{
    if(TouchType == TalkVisit){
        if(addons!=0){
            this->MyType = addons;
        }
        switch(addonsData){
        case UP:MyToward=DOWN;break;
        case DOWN:MyToward=UP;break;
        case LEFT:MyToward=RIGHT;break;
        case RIGHT:MyToward=LEFT;break;
        }
        Root->GetCoversation(NPCConversation[ConversationStep],MyType,this);
        if(NPCConversation[ConversationStep]=="#"){
            ConversationStep=0;
        }
    }
    return 0;
}
void NPC::Action()
{
    DrawX=250+50*MapX;
    DrawY=50+50*MapY;
}
void NPC::advance(int run)
{
    if(run==0){
        ConversationStep++;
    }
}

void NPC::paint(QPainter *painter)
{
    painter->fillRect(DrawX,DrawY,50,50,Qt::red);
}
