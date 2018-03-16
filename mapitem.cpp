#include"common.h"
GameController * MapItem::Root=NULL;
GameMap * MapItem::MyMap=NULL;
MapItem::MapItem(){
    value = 1;
}
void MapItem::GetFundData(GameController * controller,GameMap * map)
{
    Root=controller;
    MyMap=map;
}
int MapItem::GetItemType()
{
    return this->MyType;
}
int MapItem::GetValue()
{
    return this->value;
}
void MapItem::SetPaintValue(int MapNum)
{
    if(MapCur==MapNum)
    {
        PaintValue=true;
        MyMap->AddItem(this,MapX,MapY);
    }else{
        PaintValue=false;
    }
}
