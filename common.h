#ifndef COMMON_H
#define COMMON_H

#define MapMaxX 12          //(单页)地图最大X值
#define MapMaxY 10          //(单页)地图最大Y值
#define TimeUnit 10         //时间单位
#define NONE 0
#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <windows.h>
#include <QGraphicsSceneMouseEvent>
#include "resource.h"
#include "mapcube.h"
#include "mapitem.h"
#include "gamecontroller.h"
#include "condialog.h"
#include "conversationdialog.h"
#include "moveplayer.h"
#include "gamehero.h"
#include "npc.h"
#include "equipment.h"
#include "enemy.h"
#include "enemybat.h"
#include "gamebag.h"
#include "picbutton.h"
enum Towards
{
    UP=1,
    DOWN,
    LEFT,
    RIGHT,
};

enum MapItemType            //地图物品类型
{
    Type_Hero=1,              //英雄
    Type_EnemyBat,          //怪物-蝙蝠
    /*...*/
};

enum TouchType              //交互常量
{
    WalkVisit = 1,          //行走访问
    AtkVisit,               //攻击访问
    HeroAtkVisit,           //主角的攻击访问
    EnemyAtkVisit,          //怪物的的攻击访问
    TalkVisit,              //交谈类访问

    WatchVisit,             //(怪物的)视线访问
};

//For HurtData
#define PreDamage(Physic,Magic) Magic*10000+Physic
#define GetPhysic(a) a%10000
#define GetMagic(a) a/10000
#define FinaDamage(PhyA,MagA,PhyD,MagD) (PhyA>PhyD?PhyA-PhyD:0)+(MagA>MagD?MagA-MagD:0)

enum AtkAddons              //攻击附加效果
{
    Poison = 1,             //中毒
    Knockback,              //击退
    Stun,                   //昏迷
    RealDamage,             //固定伤害
    PenetrateEnemy,         //穿透怪物(分裂)
    PenetrateDamage,        //穿透伤害
    BloodSuck,              //吸血
    Recover,                //回复
    DesTroy,                //(对部分地图物品)毁坏
    Death,                  //(对部分怪物)秒杀
    Contrapose,             //克制(某种类型的怪物)
    StrikeBack,             //反击
};
#define PoisonedTime 3*TimeUnit
#define StunTime 2*TimeUnit
#endif // COMMON_H
