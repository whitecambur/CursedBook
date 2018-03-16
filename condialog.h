#ifndef CONDIALOG_H
#define CONDIALOG_H
#include <QDialog>

class ConDialog:public QDialog
{
public:
    ConDialog(QWidget*p);
    void SetMessage(int PicNum,QString&msg);
private:
    void paintEvent(QPaintEvent *event);
    int MyPicNum;
    QString MyMsg;
};

#endif // CONDIALOG_H
