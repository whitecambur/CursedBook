#include "common.h"

GameBag::GameBag(GameController*Controller)
{
    Root=Controller;
}
void GameBag::paint(QPainter *painter)
{

}
void GameBag::IncreaseSoulChip(int data){
    SoulChip+=data;
}

void GameBag::IncreaseSkeletonCoin(int data)
{
    SkeletonCoin+=data;
}

bool GameBag::isEnoughSoulChip(int data)
{
    if(SoulChip>=data){
        SoulChip-=data;
        return true;
    }else{
        return false;
    }
}

bool GameBag::isEnoughSkeletonCoin(int data)
{
    if(SkeletonCoin>=data){
        SkeletonCoin-=data;
        return true;
    }else{
        return false;
    }
}

void GameBag::CursorMove(int Toward)
{
    switch(Toward){
    case UP:BagCursor<5?BagCursor+=15:BagCursor-=5;break;
    case DOWN:BagCursor>=15?BagCursor-=15:BagCursor+=5;break;
    case LEFT:BagCursor%5==0?BagCursor+=4:BagCursor--;break;
    case RIGHT:BagCursor%5==4?BagCursor-=4:BagCursor++;break;
    }
}

bool GameBag::GetItem(int ItemType)
{
    bool flag=false;
    for(int i=0;i<BagItemNum&&flag==false;i++){
        if(Items[i].BagItemType==ItemType){
            Items[i].Num++;
            flag=true;
        }
    }
    if(flag==false){
        if(BagItemNum<20){
            Items[BagItemNum].BagItemType=ItemType;
            Items[BagItemNum].Num=1;
            BagItemNum++;
            flag=true;
        }
    }
    return flag;
}
bool GameBag::isOwnItem(int ItemType,int Num,bool isConsume)
{
    int i=0;
    bool flag=false;
    for(i=0;i<BagItemNum&&flag==false;i++){
        if(Items[i].BagItemType==ItemType){
            flag=true;
        }
    }
    if(i==BagItemNum)return false;
    if(Items[i].Num<Num)return false;
    if(isConsume==1){
        Items[i].Num-=Num;
        if(Items[i].Num==0){
            BagItemNum--;
            Items[i]=Items[BagItemNum];
            Items[BagItemNum].BagItemType=NONE;
            Items[BagItemNum].Num=0;
        }
    }
    return true;
}
void GameBag::UseItem()
{
    switch(Items[BagCursor].BagItemType){
    case SmallRecoverDrug:
        if(RecoverItemColdTimer==0){
            Root->GetHero()->IncreaseHP(60);
            Items[BagCursor].Num--;
            RecoverItemColdTimer=3;
        }
        break;
    case MidRecoverDrug:
        if(RecoverItemColdTimer==0){
            Root->GetHero()->IncreaseHP(100);
            Items[BagCursor].Num--;
            RecoverItemColdTimer=3;
        }
        break;
    case BigRecoverDrug:
        if(RecoverItemColdTimer==0){
            Root->GetHero()->IncreaseHP(150);
            Items[BagCursor].Num--;
            RecoverItemColdTimer=3;
        }
        break;
    case HandBomb:
        Items[BagCursor].Num--;
        break;
    }
    if(Items[BagCursor].Num==0){
        BagItemNum--;
        Items[BagCursor]=Items[BagItemNum];
        Items[BagItemNum].BagItemType=NONE;
        Items[BagItemNum].Num=0;
    }
}
void GameBag::EquipItem()
{
    switch(Items[BagCursor].BagItemType){
    case SmallRecoverDrug:case MidRecoverDrug:case BigRecoverDrug:
        if(RecoverItem==NONE){
            RecoverItem=Items[BagCursor].BagItemType;
            RecoverItemNum=Items[BagCursor].Num;
            BagItemNum--;
            Items[BagCursor]=Items[BagItemNum];
            Items[BagItemNum].BagItemType=NONE;
            Items[BagItemNum].Num=0;
        }else{
            int a=RecoverItem,b=RecoverItemNum;
            RecoverItem=Items[BagCursor].BagItemType;
            RecoverItemNum=Items[BagCursor].Num;
            Items[BagCursor].BagItemType=a;
            Items[BagCursor].Num=b;
        }
        break;
    }
}
void GameBag::UseRecoverItem()
{
    if(RecoverItemColdTimer==0){
        switch(RecoverItem){
        case SmallRecoverDrug:
            if(RecoverItemColdTimer==0){
                Root->GetHero()->IncreaseHP(60);
                RecoverItemNum--;
                RecoverItemColdTimer=3;
            }
            break;
        case MidRecoverDrug:
            if(RecoverItemColdTimer==0){
                Root->GetHero()->IncreaseHP(100);
                RecoverItemNum--;
                RecoverItemColdTimer=3;
            }
            break;
        case BigRecoverDrug:
            if(RecoverItemColdTimer==0){
                Root->GetHero()->IncreaseHP(150);
                RecoverItemNum--;
                RecoverItemColdTimer=3;
            }
            break;
        }
        if(RecoverItemNum==0){
            RecoverItem=NONE;
        }
    }
}
void GameBag::RecoverItemTimerRun(){
    if(RecoverItemColdTimer!=0)
        RecoverItemColdTimer--;
}
