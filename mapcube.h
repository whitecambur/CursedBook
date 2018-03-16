#ifndef MAPCUBE_H
#define MAPCUBE_H

class MapCube;
class MapItem;
class GameController;
class QPainter;
class GameMap
{
public:
    GameMap(GameController&Controller);
    int GetTouch(int X,int Y,int TouchType,MapItem*Toucher,int HurtData = 0,int addons = 0,int addonsData = 0);
    void MoveItem(MapItem*item,int preX,int preY,int nowX,int nowY);
    void AddItem(MapItem*item,int X,int Y);
    void RemoveItem(int X,int Y);
    void LoadMap(int MapNum);
    void ChangeMap(int Toward);
    void paint(QPainter*painter,int flag);
    ~GameMap();
private:
    MapCube**map;
    GameController & root;
    int MapNum;                         //当前地图编号
    int UpMapNum;                       //上方地图编号
    int DownMapNum;                     //下方地图编号
    int LeftMapNum;                     //左方地图编号
    int RightMapNum;                    //右方地图编号
};
class MapCube
{
public:
    MapCube();
    ~MapCube();
    void GetValue(bool isWalk,bool isLook);
    int GetTouch(int TouchType,MapItem*Toucher,int HurtData = 0,int addons = 0,int addonsData = 0);
    void AddItem(MapItem*item);
    void RemoveItem();
    void ChangeToLookable();
    bool Look();
private:
    bool isWalkable;
    bool isLookable;
    MapItem*MyItem;
};

#endif // MAPCUBE_H
