#include"common.h"
GameMap::GameMap(GameController&Controller):
    root(Controller)
{
    map = new MapCube*[10];
    for(int i=0;i<10;i++)
    {
        map[i] = new MapCube[12];
    }
}
GameMap::~GameMap(){
    if(map){
        for(int i=0;i<10;i++)
        {
            if(map[i]){
                delete map[i];
                map[i]=NULL;
            }
        }
        delete map;
        map=NULL;
    }
}
void GameMap::AddItem(MapItem*item,int X,int Y){
    this->map[Y][X].AddItem(item);
    if(item->GetItemType()==Type_Hero){
        this->map[Y][X].ChangeToLookable();
    }
}
void GameMap::RemoveItem(int X,int Y)
{
    this->map[Y][X].RemoveItem();
}
void GameMap::MoveItem(MapItem *item,int preX,int preY,int nowX,int nowY)
{
    this->map[preY][preX].RemoveItem();
    this->map[nowY][nowX].AddItem(item);
}
int GameMap::GetTouch(int X,int Y,int TouchType,MapItem*Toucher,int HurtData,int addons,int addonsData){
    if(X==-1||X==MapMaxX||Y==-1||Y==MapMaxY){
        return 1;
    }
    return this->map[Y][X].GetTouch(TouchType,Toucher,HurtData,addons,addonsData);
}
void GameMap::LoadMap(int MapNum)
{

}
void GameMap::ChangeMap(int Toward)
{

}
void GameMap::paint(QPainter*painter,int flag){
    if(flag==0){
        painter->fillRect(250,50,600,500,Qt::green);
    }else{
    //    for(int i=0;i<10;i++){
    //        for(int j=0;j<12;j++){
    //            if(map[i][j].Look()==false){
    //                painter->fillRect(250+j*50,50+i*50,50,50,Qt::black);
    //            }
    //        }
    //    }
    }
}

MapCube::MapCube()
{
    isWalkable = true;
    isLookable = true;
    this->MyItem=NULL;
}
void MapCube::GetValue(bool isWalk,bool isLook)
{
    isWalkable = isWalk;
    isLookable = isLook;
}
MapCube::~MapCube()
{
    this->MyItem=NULL;
}
void MapCube::AddItem(MapItem*item)
{
    this->MyItem=item;
}
void MapCube::RemoveItem()
{
    this->MyItem=NULL;
}
int MapCube::GetTouch(int TouchType,MapItem*Toucher,int HurtData,int addons,int addonsData)
{
    switch(TouchType)
    {
    case WalkVisit:
        if(this->MyItem==NULL)return this->isWalkable;
        else return 0;
        break;
    default:
        if(this->MyItem==NULL)return this->isWalkable;
        else return this->MyItem->GetTouch(TouchType,Toucher,HurtData,addons,addonsData);
        break;
    }
}
void MapCube::ChangeToLookable()
{
    this->isLookable=true;
}
bool MapCube::Look(){
    return isLookable;
}
