#ifndef CONVERSATIONDIALOG_H
#define CONVERSATIONDIALOG_H

class QPainter;
class GameController;
class QString;
class ConversationDialog
{
public:
    ConversationDialog(GameController*Controller);
    void GetConversation(QString&ch,int ItemType);
    void OptionMove(int Toward);
    int GetValue();
    void paint(QPainter*painter);
private:
    GameController*Root;
    int SpeekerNum;                     //说话的是谁
    QString Sentence;                   //说话的内容
    int OptionNum;                      //当前选择项个数
    int OPtionCur;                      //当前正选中的项目
    QString Options[3];                 //选择项文字说明

};

#endif // CONVERSATIONDIALOG_H
