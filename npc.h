#ifndef NPC_H
#define NPC_H

class MapItem;
class NPC:public MapItem
{
public:
    NPC();
    NPC(int type,int MapNum,int x,int y,int Toward,int taskstep);
    int GetTouch(int TouchType,MapItem*Toucher,int HurtData = 0,int addons = 0,int addonsData = 0);
    void paint(QPainter *painter);
    void Action();
    void advance(int run);
private:
    int ConversationStep;                       //对话进行进度
    int TaskStep;                               //NPC内置进度
};

#endif // NPC_H
