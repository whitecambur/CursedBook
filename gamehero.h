#ifndef MAPHERO_H
#define MAPHERO_H

class MapItem;

struct Weapon;
struct Armor;
class Hero:public MapItem
{
public:
    Hero();
    //Hero(int X,int Y,int MaxHP,int HP);
    int GetTouch(int TouchType, MapItem *Toucher, int HurtData, int addons, int addonsData);
    void paint(QPainter *painter);
    void Action();
    void IncreaseHP(int data);          //主角增加HP
    void DecreaseHP(int data);          //主角减少HP
    int HeroWalk(int Toward);           //主角走路
    int HeroAttack(int Toward);         //主角攻击
    int HeroTalk();                     //主角交谈
    void Poisoned();                    //主角中毒
    void HPDownToZero();
    int GetMyX();                       //获取主角X坐标
    int GetMyY();                       //获取主角Y坐标
    void EquipEquipments(int EquipmentNum,int Part);
                                        //主角装备道具，参数分别为装备序号，装备位置
    int GetLightAbility();              //主角照明能力
private:
    int HP;                             //主角HP值
    int MaxHP;                          //主角最大HP值
    int Status;                         //主角的行动状态
    int isPoisoned;                     //主角是否中毒
    int PoisonedTimer;                  //主角中毒计时器
    Weapon*MyWeapon;                    //主角的武器
    int WeaponTimer;                    //武器附加效果计时器
    Armor*HeadArmor;                    //主角的头部防具
    int HeadArmorTimer;                 //头部防具附加效果计时器
    Armor*HandArmor;                    //主角的手部防具
    int HandArmorTimer;                 //手部防具附加效果计时器
    Armor*BodyArmor;                    //主角的身体防具
    int BodyArmorTimer;                 //身体防具附加效果计时器
    Armor*FeetArmor;                    //主角的脚部防御
    int FeetArmorTimer;                 //脚部防具附加效果计时器
    int PhyDef;                         //主角防御力
    int MagDef;                         //主角魔抗值
    int Proficiency[5];                 //主角对五种武器的熟练度
};

#endif
