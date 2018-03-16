#ifndef ENEMYBAT_H
#define ENEMYBAT_H

class Enemy;
class EnemyBat : public Enemy
{
public:
    EnemyBat(int X,int Y);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void AIAction();
private:
    void EnemyConcreteAction();
    static int AttTime;
};

#endif // ENEMYBAT_H
