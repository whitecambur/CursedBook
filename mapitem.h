#ifndef HERO_H
#define HERO_H

#include <QGraphicsItem>
#include <QRectF>

class GameController;
class GameMap;

class MapItem
{
public:
    MapItem();
    static void GetFundData(GameController * controller,GameMap * map);
    virtual void paint(QPainter *painter) = 0;
    virtual int GetTouch(int TouchType,MapItem*Toucher,int HurtData = 0,int addons = 0,int addonsData = 0) = 0;
    virtual void Action() = 0;
    int GetItemType();
    int GetValue();
    void SetPaintValue(int MapNum);
protected:
    int DrawX,DrawY;
    static GameController * Root;
    static GameMap * MyMap;
    int MyTimer;
    int MyType;
    int MapX;
    int MapY;
    int value;
    int MyToward;

    bool PaintValue;
    int MapCur;
};


#endif // HERO_H
