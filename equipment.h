#ifndef EQUIPMENT_H
#define EQUIPMENT_H

class GameMap;

struct Weapon
{
    int WeaponNum;                      //武器编号（用于判断武器是什么）
    int WeaponType;                     //武器类别
    int AtkData;                        //攻击力
    int AtkRange;                       //攻击范围
    int AtkSpeed;                       //攻击时间
    int DamageType;                     //伤害类型
    int WeaponAddons;                   //附加的特殊效果
    int WeaponAddonsData;               //附加的特殊效果的数值(如果有的话)
};

struct Armor{
    int ArmorNum;                       //防具编号
    int PhyDefData;                     //防御
    int MagDefData;                     //魔防
    int ArmorAddons;                    //防具特殊效果
    int ArmorAddonsData;                //防具特殊效果数值(如果有的话)
};
enum WeaponType{
    Fist = 1,               //拳
    Sword,                  //刀剑
    Spear,                  //矛(长枪)
    Bow,                    //弓(枪)
    Wand,                   //法杖
};
enum EquipAddons            //装备附加效果
{
    AddHP = 1,              //提高血量
    AddPhyAtk,              //提高物理攻击
    AddMagAtk,              //提高魔法攻击
    RealDamageable,         //固定伤害
    AddPhyDef,              //提高物防
    AddMagDef,              //提高魔防
    Poisonable,             //中毒
    Knockbackable,          //击退
    Stunable,               //昏迷
    PenetrateWallable,      //穿墙
    PenetrateEnemyable,     //穿透怪物(分裂)
    BloodSuckable,          //吸血
    DesTroyable,            //(对部分地图物品)毁坏
    Deathable,              //(对部分怪物)秒杀
    Contraposeable,         //克制(某种类型的怪物)
    Defend,                 //完全抵挡攻击
    Resistence,             //对某怪物具有抗性
    Lighting,               //照明
    SoulCurse,              //灵魂诅咒
    PhyStrikeBack,          //物理反击
    MagStrikeBack,          //魔法反击
    Virtual,                //虚无
};
#endif // EQUIPMENT_H
