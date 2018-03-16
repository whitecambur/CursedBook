#ifndef GAMEBAG_H
#define GAMEBAG_H

#include <QRectF>
class GameController;
struct GameBagItem
{
    int BagItemType;
    int Num;
};
enum BagItemType            //背包物品类型
{
    SmallRecoverDrug=1,     //小药
    MidRecoverDrug,         //中药
    BigRecoverDrug,         //大药
    RedSoulChip,            //红灵魂碎片
    BlueSoulChip,           //蓝灵魂碎片
    YellowSoulChip,         //黄灵魂碎片
    KeyA,                   //钥匙A
    KeyB,                   //钥匙B
    KeyC,                   //钥匙C
    HandBomb,               //投掷型手雷
};

class GameBag
{
public:
    GameBag(GameController*Controller);
    void paint(QPainter *painter);
    void IncreaseSoulChip(int data);
    void IncreaseSkeletonCoin(int data);
    bool isEnoughSoulChip(int data);
    bool isEnoughSkeletonCoin(int data);
    void CursorMove(int Toward);
    bool GetItem(int ItemType);                           //获得物品
    bool isOwnItem(int ItemType,int Num,bool isConsume);  //是否拥有物品，数量，是否会消耗
    void UseItem();                     //使用道具
    void UseRecoverItem();              //使用恢复道具
    void RecoverItemTimerRun();         //回复道具冷却
    void EquipItem();                   //装备道具
private:
    GameController*Root;
    int SoulChip;                       //灵魂碎片
    int SkeletonCoin;                   //骷髅币
    int HeroEquipment[5];               //主角装备栏(存装备编号)
    int RecoverItem;                    //回复道具栏(存恢复道具编号)
    int RecoverItemNum;                 //回复道具的数量
    int RecoverItemColdTimer;           //回复道具冷却时间
    struct GameBagItem Items[20];       //背包内物品
    int BagItemNum;                     //背包内物品数量
    int BagCursor;                      //背包界面光标
};

#endif // GAMEBAG_H
