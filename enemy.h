#ifndef ENEMY_H
#define ENEMY_H

class MapItem;
enum EnemyStatus
{
    Stand,                  //静止
    Walk,                   //走路
    Retreat,                //退却
    Stuned,                 //昏迷
    Dying,                  //死亡
};

class Enemy:public MapItem              //怪物基类
{
public:
    Enemy();
    virtual int GetTouch(int TouchType,MapItem*Toucher,int HurtData = 0,int addons = 0,int addonsData = 0);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) = 0;
    virtual void AIAction() = 0;                //怪物开始行动
protected:
    virtual void BePoisoned(int data);          //怪物进入中毒状态
    virtual void Poisoned();                    //怪物处于中毒状态
    virtual void BeStuned();                    //怪物进入昏迷状态
    virtual void BeKnockBack(int Toward);       //怪物面临击退时的情况
    virtual void BePenetrate(int data);         //怪物面临分裂时的情况
    virtual void BeDeath(int data);             //怪物面临致死时的情况
    virtual void StrikingBack();                //怪物反击
    virtual void HPDownToZero();                //怪物没血时的情况
    virtual void EnemyWalk();                   //怪物行走
    virtual void EnemyRetreat();                //怪物退却
    virtual void EnemyConcreteAction()=0;       //怪物的具体行为
    void Action();                              //怪物行动
    void IncreaseHP(int data);              //怪物血量增加
    void DecreaseHP(int data);              //怪物血量减少
    int DieTime;                            //怪物死亡所需时间
    int WalkTime;                           //怪物走路所需时间
    int RetreatTime;                        //怪物退却所需时间
    char*Name;                              //怪物名称
    int MaxHP;                              //怪物最大血量
    int HP;                                 //怪物血量
    int Status;                             //怪物状态
    int isPoisoned;                         //怪物是否中毒(值为中毒伤害)
    int PoisonedTimer;                      //中毒状态计时器
    int PhyAtk;                             //怪物物理攻击力
    int MagAtk;                             //怪物魔法攻击力
    int PhyDef;                             //怪物防御力
    int MagDef;                             //怪物魔抗值
};

#endif // ENEMY_H
