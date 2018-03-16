#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QLinkedList>
#include <QLabel>

class QGraphicsScene;
class QKeyEvent;
class MapItem;
class GameMap;
class Hero;
class NPC;
class GameBag;
class Enemy;
class PicButton;
class ConDialog;
class ConversationDialog;
class MoviePlayer;
//class Snake;
//class Food;
//class Wall;

class GameController : public QObject
{
    Q_OBJECT

public:
    GameController(QObject *parent = 0, QWidget*MainWidget = 0);
    ~GameController();
    int GetHeroX();
    int GetHeroY();
    Hero*GetHero();
    GameBag* Bag();
    void AddMapItem(int ItemType);
    void ShowMessage(int PicNum,QString&msg);
    void GetCoversation(QString&msg,int ItemType,NPC*theNPC);
    void SetControllerTask(int TaskType,int TaskNum);
    void Show(QPainter*painter,int w,int h);
public slots:
    void advanced();            //更新物件
    void DrawPic();             //重绘
    void KeyAction();
protected:
     bool eventFilter(QObject *object, QEvent *event);
private:
     void Load(int num);                //读取游戏
     void SaveAll(int num);             //保存游戏
     void toGame();                     //进入游戏
     void MapChange();                  //地图改变
     void KillAllEnemy();               //杀死所有怪物
     void DeleteAllMagic();             //删除所有特技
     void GameOver();                   //游戏结束
    void handleKeyPressed(QKeyEvent *event);            //控制器相应按键
    QPainter*MyPainter;                                 //画笔
    QPixmap*MyPic;                                      //布
    int PageCur;                                        //游戏当前所处的页面
    int ControllModeCur;                                //控制器的当前操作模式
    QWidget*MyWidget;
    QTimer timer;                                       //控制器的计时器

    bool EventKey[100];                                 //全局事件开关
    int EventTimer;                                     //控制器事件计时器
    int MyTaskCur;                                      //控制器当前任务
    int MyTaskData;                                       //控制器当前任务的值
    int MyTaskTimer;                                      //控制器任务计时器

    ConDialog*MyDialog;                                 //提示框
    ConversationDialog*MySpeekDialog;                   //对话框
    GameMap *MyMap;                                     //地图
    Hero *MyHero;                                       //主角
    NPC *MyNPC;                                         //控制器的隐形NPC
    NPC *TouchingNPC;                                   //正在处理的NPC
    GameBag*MyBag;                                      //主角背包
    QLinkedList<MapItem *>MyItems;                      //地图物品
    QLinkedList<Enemy *>MyEnemies;                      //地图怪物
    Enemy*Boss;                                         //当前BOSS

    //QLinkedList<Magic *>MyMagic;                      //地图上的动画特效
    MoviePlayer*MyMoviePlayer;                          //地图全局动画播放器

    PicButton*ButtonOptions[4];
    PicButton*StartButton;                              //开始游戏按钮
    PicButton*LoadButton;                               //读取进度按钮
    PicButton*InformButton;                             //游戏介绍按钮
    PicButton*ExitButton;                               //退出游戏按钮
    PicButton*GameMenuButton;                           //(游戏中)菜单按钮
    PicButton*BackMenuButton;                           //返回主菜单按钮
    PicButton*BackGameButton;                           //返回游戏按钮
};
enum ControllTaskType{

};
enum Pages{
    PageMainMenu=1,
    PageLoadMenu,
    PageSaveMenu,
    PageGame,
    PageGameMenu,
};
enum ControllMode{
    Menu=1,
    LoadSeclect,
    SaveSeclect,
    Player,
    InBag,
    InSell,
    InShop,
    InConversation,
};
#endif // GAMECONTROLLER_H
