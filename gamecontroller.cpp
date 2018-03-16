#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <vector>
#include"common.h"

GameController::GameController(QObject *parent, QWidget *MainWidget):
    QObject(parent),
    MyWidget(MainWidget),
    MyMap(new GameMap(*this)),
    MyDialog(new ConDialog(MainWidget))
{
    LoadPic();
    MyPic = new QPixmap(1000,620);
    MyPainter = new QPainter(MyPic);
    MyDialog->setFixedSize(450,600);
    timer.start( 40 );

    connect(&timer, SIGNAL(timeout()),
            this, SLOT(KeyAction()));
    connect(&timer, SIGNAL(timeout()),
            this, SLOT(advanced()));
    connect(&timer, SIGNAL(timeout()),
            this, SLOT(DrawPic()));
    connect(&timer, SIGNAL(timeout()),
            MyWidget,SLOT(update()));
    MainWidget->installEventFilter(this);

    MapItem::GetFundData(this,MyMap);
    PicButton::GetFundData(this);
    MyHero=new Hero;
    MyBag=new GameBag(this);
    MyNPC=new NPC;
    MySpeekDialog = new ConversationDialog(this);

    StartButton=new PicButton(GotoGame,0);
    StartButton->setPos(405,400);


    LoadButton=new PicButton(GotoLoad,0);
    LoadButton->setPos(405,400);


    InformButton=new PicButton(GotoInform,0);
    InformButton->setPos(405,400);


    ExitButton=new PicButton(GameExit,0);
    ExitButton->setPos(405,470);


    BackMenuButton=new PicButton(BackToMenu,0);
    BackMenuButton->setPos(900,20);

    GameMenuButton=new PicButton(GotoGameMenu,0);
    GameMenuButton->setPos(900,20);
    //QString ch="欢迎你玩这个游戏！！！！！！！！！";
    //ShowMessage(0,ch);

    toGame();
}

GameController::~GameController()
{
    MapItem::GetFundData(NULL,NULL);
    PicButton::GetFundData(NULL);
}

int GameController::GetHeroX()
{
    return MyHero->GetMyX();
}
int GameController::GetHeroY()
{
    return MyHero->GetMyY();
}
Hero*GameController::GetHero()
{
    return MyHero;
}

GameBag*GameController::Bag()
{
    return MyBag;
}

void GameController::AddMapItem(int ItemType)
{

}

void GameController::handleKeyPressed(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W:
        //MyHero->HeroWalk(UP);
        break;
    case Qt::Key_S:

        break;
    case Qt::Key_A:

        break;
    case Qt::Key_D:

        break;
    case Qt::Key_U:case Qt::Key_Space:
        switch(PageCur){
        case PageMainMenu:break;
        case PageLoadMenu:break;
        case PageSaveMenu:break;
        case PageGame:
            switch(ControllModeCur){
            case Player:
                MyHero->HeroTalk();
                break;
            case InConversation:
                if(TouchingNPC!=NULL){
                    TouchingNPC->advance(MySpeekDialog->GetValue());
                    TouchingNPC->GetTouch(TalkVisit,MyHero);
                }else{
                    ControllModeCur = Player;
                }
                break;
            }
            break;
        case PageGameMenu:break;
        }
        break;
    }
}

void GameController::KeyAction(){
    if(PageCur==PageGame&&ControllModeCur==Player){
        if(GetKeyState('W')<0){
            MyHero->HeroWalk(UP);
        }else if(GetKeyState('S')<0){
            MyHero->HeroWalk(DOWN);
        }else if(GetKeyState('A')<0){
            MyHero->HeroWalk(LEFT);
        }else if(GetKeyState('D')<0){
            MyHero->HeroWalk(RIGHT);
        }
    }
}

void GameController::ShowMessage(int PicNum,QString&msg)
{
    MyDialog->SetMessage(PicNum,msg);
    MyDialog->show();
}
void GameController::GetCoversation(QString&msg,int ItemType,NPC*theNPC)
{
    if(msg=="#"){
        ControllModeCur = Player;
        TouchingNPC = NULL;
    }else{
        if(ControllModeCur!=InConversation){
            ControllModeCur=InConversation;
            TouchingNPC = theNPC;
        }
    }
    MySpeekDialog->GetConversation(msg,ItemType);
}
void GameController::SetControllerTask(int TaskType, int TaskNum)
{
    MyTaskCur=TaskType;
    MyTaskData=TaskNum;
    MyTaskTimer=0;
}

void GameController::Show(QPainter*painter,int w,int h){
    if(w>=2000&&h>=1240){
        painter->drawPixmap(w/2-1000,h/2-620,MyPic->scaled(2000,1240));
    }else if(w>=1500&&h>=930){
        painter->drawPixmap(w/2-750,h/2-465,MyPic->scaled(1500,930));
    }else if(w>=1000&&h>=620){
        painter->drawPixmap(w/2-500,h/2-310,*MyPic);
    }else if(w>=750&&h>=465){
        painter->drawPixmap(w/2-360,h/2-232,MyPic->scaled(750,465));
    }else{    
        painter->drawPixmap(w/2-240,h/2-155,MyPic->scaled(500,310));
    }
}
void GameController::DrawPic(){
    switch(PageCur){
    case PageMainMenu:break;
    case PageLoadMenu:break;
    case PageSaveMenu:break;
    case PageGame:
        if(ControllModeCur==Player||ControllModeCur==InConversation){
            MyMap->paint(MyPainter,0);
            /*Enemy,MapItem*/
            MyNPC->paint(MyPainter);
        }
        MyHero->paint(MyPainter);
        MyMap->paint(MyPainter,1);
        /*BOSS,Magic*/
        MyPainter->drawPixmap(0,0,1000,620,*GameMenuPic);
        switch(ControllModeCur){
        case InConversation:MySpeekDialog->paint(MyPainter);break;
        case InBag:case InSell:break;
        case InShop:break;
        }
        /*Bottons*/
        GameMenuButton->paint(MyPainter);
        break;
    case PageGameMenu:break;
    }
}

void GameController::advanced(){
    MyHero->Action();
}


void GameController::Load(int num){

}
void GameController::SaveAll(int num){

}
void GameController::toGame()
{
    PageCur = PageGame;
    ControllModeCur=Player;
}
void GameController::MapChange(){

}
void GameController::KillAllEnemy(){

}
void GameController::DeleteAllMagic()
{

}
void GameController::GameOver(){

}
bool GameController::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    } else{
        return QObject::eventFilter(object, event);
   }
   if(event->type() == QEvent::KeyPress){

   }
}
