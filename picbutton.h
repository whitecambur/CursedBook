#ifndef PICBUTTON_H
#define PICBUTTON_H
#include <QRectF>
class GameController;
class PicButton
{
public:
    PicButton(int num,int value);
    static void GetFundData(GameController * controller);
    void paint(QPainter *painter);
    void setPos(int x,int y);
private:
    int DrawX,DrawY,w,h;
    int ButtonType;
    int MyValue;
    int Status;
    static GameController*Root;
};
enum UiButtonType{
    GotoGame=1,
    GotoLoad,
    GotoSave,
    GotoInform,
    GotoGameMenu,
    BackToMenu,
    BackToGame,
    GameExit
};
#endif // PICBUTTON_H
