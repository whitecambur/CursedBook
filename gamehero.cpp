#include"common.h"
const int HeroWalkTime = 0.8*TimeUnit;
const int HeroDyingTime = TimeUnit;
const int HeroRetreatTime = TimeUnit;
enum HeroStatus{
    Attack = 5,
};

Hero::Hero(){
    MapX = 5;
    MapY = 5;
    MyTimer=0;
    MyType=Type_Hero;
    MyToward=UP;
    MyMap->AddItem(this,MapX,MapY);
    Status = Stand;
    MaxHP=HP=100;
    isPoisoned=0;
    PoisonedTimer=0;
}
int Hero::GetTouch(int TouchType, MapItem *Toucher, int HurtData, int addons, int addonsData)
{
    if(TouchType==AtkVisit)
    {
        if(addons == Recover){
            IncreaseHP(HurtData);
            return 0;
        }
        int MagDamage = GetMagic(HurtData);
        int PhyDamage = GetPhysic(HurtData);
        int Damage = FinaDamage(MagDamage,PhyDamage,PhyDef,MagDef) + addons==RealDamage?addonsData:0;
        if(HeadArmor->ArmorAddons==Resistence){
            Damage=Damage/2;
        }
        DecreaseHP(Damage);
        switch(addons)
        {
        case BloodSuck:Toucher->GetTouch(AtkVisit,this,Damage,Recover);break;
        case Poison:break;
        }
        if(addons!=StrikeBack&&Toucher!=NULL)
        {

        }
    }else if(TouchType==WatchVisit)
    {
        return 1;
    }
    return 0;
}
void Hero::paint(QPainter *painter)
{
    switch(Status){
    case Stand:painter->drawPixmap(DrawX,DrawY,50,50,*HeroStandPic[MyToward-1]);break;
    case Walk:painter->drawPixmap(DrawX,DrawY,50,50,*HeroWalkPic[(MyToward-1)*8+HeroWalkTime-MyTimer-1]);break;
    }
}
void Hero::Action()
{
    DrawX=50*MapX+250;
    DrawY=50*MapY+50;
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
    }else{
        switch(Status){
        case Walk:
            if(MyTimer == HeroWalkTime/2){
                switch(MyToward)
                {
                case UP:
                    if(MyMap->GetTouch(MapX,MapY-1,WalkVisit,this)==true)
                    {
                        MyMap->RemoveItem(MapX,MapY);
                        if(MapY==0){
                            MapY=MapMaxY-1;
                        }else{
                            MapY--;
                        }
                        MyMap->AddItem(this,MapX,MapY);
                    }else
                    {
                        Status=Retreat;
                        MyTimer=HeroRetreatTime/2;
                    }
                    DrawY-=25;
                    break;
                case DOWN:
                    if(MyMap->GetTouch(MapX,MapY+1,WalkVisit,this)==true)
                    {
                        MyMap->RemoveItem(MapX,MapY);
                        if(MapY==MapMaxY-1){
                            MapY=0;
                        }else{
                            MapY++;
                        }
                        MyMap->AddItem(this,MapX,MapY);
                    }else
                    {
                        Status=Retreat;
                        MyTimer=HeroRetreatTime/2;
                    }
                    DrawY+=25;
                    break;
                case LEFT:
                    if(MyMap->GetTouch(MapX-1,MapY,WalkVisit,this)==true)
                    {
                        MyMap->RemoveItem(MapX,MapY);
                        if(MapX==0){
                            MapX=MapMaxX-1;
                        }else{
                            MapX--;
                        }
                        MyMap->AddItem(this,MapX,MapY);
                    }else
                    {
                        Status=Retreat;
                        MyTimer=HeroRetreatTime/2;
                    }
                    DrawX-=25;
                    break;
                case RIGHT:
                    if(MyMap->GetTouch(MapX+1,MapY,WalkVisit,this)==true)
                    {
                        MyMap->RemoveItem(MapX,MapY);
                        if(MapX==MapMaxX-1){
                            MapX=0;
                        }else{
                            MapX++;
                        }
                        MyMap->AddItem(this,MapX,MapY);
                    }else
                    {
                        Status=Retreat;
                        MyTimer=HeroRetreatTime/2;
                    }
                    DrawX+=25;
                    break;
                }
            }else if(MyTimer > HeroWalkTime/2){
                switch(MyToward){
                case UP:DrawY-=(HeroWalkTime-MyTimer)*50/HeroWalkTime;break;
                case DOWN:DrawY+=(HeroWalkTime-MyTimer)*50/HeroWalkTime;break;
                case LEFT:DrawX-=(HeroWalkTime-MyTimer)*50/HeroWalkTime;break;
                case RIGHT:DrawX+=(HeroWalkTime-MyTimer)*50/HeroWalkTime;break;
                }
            }else{
                switch(MyToward){
                case UP:DrawY+=(MyTimer)*50/HeroWalkTime;break;
                case DOWN:DrawY-=(MyTimer)*50/HeroWalkTime;break;
                case LEFT:DrawX+=(MyTimer)*50/HeroWalkTime;break;
                case RIGHT:DrawX-=(MyTimer)*50/HeroWalkTime;break;
                }
            }
            break;
        }
        MyTimer--;
    }
}
int Hero::HeroWalk(int Toward)
{
    if(Status==Stand){
        MyToward=Toward;
        switch(Toward)
        {
        case UP:
            if(MyMap->GetTouch(MapX,MapY-1,WalkVisit,this)==true)
            {
                Status=Walk;
                MyTimer=HeroWalkTime;
                return 1;
            }else
            {
                return 0;
            }
            break;
        case DOWN:
            if(MyMap->GetTouch(MapX,MapY+1,WalkVisit,this)==true)
            {
                Status=Walk;
                MyTimer=HeroWalkTime;
                return 1;
            }else
            {
                return 0;
            }
            break;
        case LEFT:
            if(MyMap->GetTouch(MapX-1,MapY,WalkVisit,this)==true)
            {
                Status=Walk;
                MyTimer=HeroWalkTime;
                return 1;
            }else
            {
                return 0;
            }
            break;
        case RIGHT:
            if(MyMap->GetTouch(MapX+1,MapY,WalkVisit,this)==true)
            {
                Status=Walk;
                MyTimer=HeroWalkTime;
                return 1;
            }else
            {
                return 0;
            }
            break;
        }
        return 0;
    }else{
        return 0;
    }
}
int Hero::HeroAttack(int Toward)
{
    if(Status==Stand){
        MyToward=Toward;
        Status = Attack;
        if(MyWeapon==NULL)
        {
            return 0;
        }else{
            MyTimer=MyWeapon->AtkSpeed;
            return 1;
        }
    }else{
        return 0;
    }
}
int Hero::HeroTalk()
{
    if(Status==Stand){
        switch(MyToward){
        case UP:MyMap->GetTouch(MapX,MapY-1,TalkVisit,this,0,NONE,UP);break;
        case DOWN:MyMap->GetTouch(MapX,MapY+1,TalkVisit,this,0,NONE,DOWN);break;
        case LEFT:MyMap->GetTouch(MapX-1,MapY,TalkVisit,this,0,NONE,LEFT);break;
        case RIGHT:MyMap->GetTouch(MapX+1,MapY,TalkVisit,this,0,NONE,RIGHT);break;
        }
    }
    return 0;
}
void Hero::EquipEquipments(int EquipmentNum, int Part)
{

}
void Hero::IncreaseHP(int data)
{
    HP+=data;
    if(HP>MaxHP)HP=MaxHP;
}
void Hero::DecreaseHP(int data)
{
    HP-=data;
    if(HP<0)HP=0;
}
void Hero::Poisoned()
{
    PoisonedTimer--;
    if(PoisonedTimer%TimeUnit==1){
        DecreaseHP(isPoisoned);
    }
    if(PoisonedTimer==0)isPoisoned=0;
}
void Hero::HPDownToZero()
{
    Status = Dying;
    MyTimer = HeroDyingTime;
}
int Hero::GetMyX()
{
    return MapX;
}

int Hero::GetMyY()
{
    return MapY;
}

