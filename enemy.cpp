#include "common.h"

Enemy::Enemy()
{
    Status=Stand;
    isPoisoned=0;
    PoisonedTimer=0;
    WalkTime = 1;
    DieTime = 1;
    RetreatTime = 1;
}
int Enemy::GetTouch(int TouchType,MapItem*Toucher,int HurtData,int addons,int addonsData)
{
    if(TouchType == WatchVisit)
    {
        return 1;
    }else if(TouchType == AtkVisit || TouchType == HeroAtkVisit)
    {
        if(addons == Recover){
            IncreaseHP(HurtData);
            return 0;
        }
        int MagDamage = GetMagic(HurtData);
        int PhyDamage = GetPhysic(HurtData);
        if(addons == Contrapose && this->MyType == addonsData)
        {
            MagDamage = MagDamage*2;
            PhyDamage = PhyDamage*2;
        }
        int Damage = FinaDamage(MagDamage,PhyDamage,PhyDef,MagDef) + addons==RealDamage?addonsData:0;
        DecreaseHP(Damage);
        switch(addons)
        {
        case BloodSuck:Toucher->GetTouch(AtkVisit,this,Damage,Recover);break;
        case Death:BeDeath(addonsData);break;
        case Poison:BePoisoned(addonsData);break;
        case Stun:BeStuned();break;
        case Knockback:BeKnockBack(addonsData);break;
        case PenetrateEnemy:BePenetrate(HurtData*addonsData/100);break;
        }
        if(addons!=StrikeBack&&addons!=PenetrateDamage&&Toucher!=NULL)
        {
            StrikingBack();
        }
    }else if(TouchType == WatchVisit)
    {
        return 1;
    }
    return 0;
}
void Enemy::Action()
{
    if(isPoisoned)Poisoned();
    if(HP==0){
        HPDownToZero();
    }
    if(MyTimer==0)
    {
        if(Status==Dying)
        {
            MyTimer = -1;
            value = 0;
        }else
        {
            Status=Stand;
        }
    }else
    {
        EnemyWalk();
        EnemyRetreat();
        if(MyTimer == 1)
            EnemyConcreteAction();
        MyTimer--;
    }
}
void Enemy::BeDeath(int data)
{
    int num = 100;
    if(num<data)DecreaseHP(HP);
}
void Enemy::BeKnockBack(int Toward)
{
    switch(Toward)
    {
    case UP:
        MyToward=DOWN;
        if(MyMap->GetTouch(MapX,MapY-1,WalkVisit,this)==true){
            MyMap->RemoveItem(MapX,MapY);
            MapY--;
            MyMap->AddItem(this,MapX,MapY);
            Status=Retreat;
            MyTimer=RetreatTime;
        }else{
           DecreaseHP(10);
        }
        break;
    case DOWN:
        MyToward=UP;
        if(MyMap->GetTouch(MapX,MapY+1,WalkVisit,this)==true){
            MyMap->RemoveItem(MapX,MapY);
            MapY++;
            MyMap->AddItem(this,MapX,MapY);
            Status=Retreat;
            MyTimer=RetreatTime;
        }else{
            DecreaseHP(10);
        }
        break;
    case LEFT:
        MyToward=RIGHT;
        if(MyMap->GetTouch(MapX-1,MapY,WalkVisit,this)==true){
            MyMap->RemoveItem(MapX,MapY);
            MapX--;
            MyMap->AddItem(this,MapX,MapY);
            Status=Retreat;
            MyTimer=RetreatTime;
        }else{
            DecreaseHP(10);
        }
        break;
    case RIGHT:
        MyToward=LEFT;
        if(MyMap->GetTouch(MapX+1,MapY,WalkVisit,this)==true){
            MyMap->RemoveItem(MapX,MapY);
            MapX++;
            MyMap->AddItem(this,MapX,MapY);
            Status=Retreat;
            MyTimer=RetreatTime;
        }else{
            DecreaseHP(10);
        }
        break;
    }
}
void Enemy::BePenetrate(int data){
    MyMap->GetTouch(this->MapX,this->MapY-1,HeroAtkVisit,this,data,PenetrateDamage);
    MyMap->GetTouch(this->MapX,this->MapY+1,HeroAtkVisit,this,data,PenetrateDamage);
    MyMap->GetTouch(this->MapX-1,this->MapY,HeroAtkVisit,this,data,PenetrateDamage);
    MyMap->GetTouch(this->MapX+1,this->MapY,HeroAtkVisit,this,data,PenetrateDamage);
}
void Enemy::BePoisoned(int data){
    isPoisoned=data;
    PoisonedTimer=PoisonedTime;
}
void Enemy::BeStuned()
{
    Status=Stuned;
    MyTimer=StunTime;
}
void Enemy::Poisoned()
{
    PoisonedTimer--;
    if(PoisonedTimer%TimeUnit==1){
        DecreaseHP(isPoisoned);
    }
    if(PoisonedTimer==0)isPoisoned=0;
}
void Enemy::StrikingBack()
{

}
void Enemy::HPDownToZero()
{
    Status = Dying;
    MyTimer = DieTime;
    MyMap->RemoveItem(MapX,MapY);
}
void Enemy::EnemyWalk()
{
    if(MyTimer == WalkTime/2){
        switch(MyToward)
        {
        case UP:
            if(MyMap->GetTouch(MapX,MapY-1,WalkVisit,this)==true)
            {
                MyMap->RemoveItem(MapX,MapY);
                MapY--;
                MyMap->AddItem(this,MapX,MapY);
            }else
            {
                Status=Retreat;
                MyTimer=RetreatTime/2;
            }
            break;
        case DOWN:
            if(MyMap->GetTouch(MapX,MapY+1,WalkVisit,this)==true)
            {
                MyMap->RemoveItem(MapX,MapY);
                MapY++;
                MyMap->AddItem(this,MapX,MapY);
            }else
            {
                Status=Retreat;
                MyTimer=RetreatTime/2;
            }
            break;
        case LEFT:
            if(MyMap->GetTouch(MapX-1,MapY,WalkVisit,this)==true)
            {
                MyMap->RemoveItem(MapX,MapY);
                MapX--;
                MyMap->AddItem(this,MapX,MapY);
            }else
            {
                Status=Retreat;
                MyTimer=RetreatTime/2;
            }
            break;
        case RIGHT:
            if(MyMap->GetTouch(MapX+1,MapY,WalkVisit,this)==true)
            {
                MyMap->RemoveItem(MapX,MapY);
                MapX++;
                MyMap->AddItem(this,MapX,MapY);
            }else
            {
                Status=Retreat;
                MyTimer=RetreatTime/2;
            }
            break;
        }
    }else if(MyTimer > WalkTime/2){

    }else{

    }
}
void Enemy::EnemyRetreat()
{

}
void Enemy::IncreaseHP(int data)
{
    HP+=data;
    if(HP>MaxHP)HP=MaxHP;
}
void Enemy::DecreaseHP(int data)
{
    HP-=data;
    if(HP<0)HP=0;
}
