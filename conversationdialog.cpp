#include "common.h"

ConversationDialog::ConversationDialog(GameController*Controller)
{
    Root=Controller;
    Sentence="#";
    Options[2]=Options[1]=Options[0]="";
    SpeekerNum=0;
    OptionNum=0;
    OPtionCur=0;
}
void ConversationDialog::GetConversation(QString&ch,int ItemType){
    SpeekerNum=ItemType;
    if(ch[0]=='?'){
        for(int i=0;i<3;i++){
            Options[i]=ch.section('?',i+1,i+1);
            if(!Options[i].isEmpty()){
                OptionNum++;
            }
        }
        OPtionCur=1;
        Sentence="#";
    }else{
        Sentence=ch;
        OPtionCur=0;
        OptionNum=0;
        Options[2]=Options[1]=Options[0]="";
    }
}
void ConversationDialog::OptionMove(int Toward){
    if(OPtionCur!=0){
        switch(Toward){
        case UP:
            if(OPtionCur==1){
                OPtionCur=OptionNum;
            }else{
                OPtionCur--;
            }
        case DOWN:
            if(OPtionCur==OptionNum){
                OPtionCur=1;
            }else{
                OPtionCur++;
            }
        }
    }
}

int ConversationDialog::GetValue(){
    return OPtionCur;
}

void ConversationDialog::paint(QPainter*painter){
    if(OptionNum==0){
        if(Sentence!="#"){
            painter->fillRect(250,500,600,120,Qt::yellow);
            painter->drawText(320,520,Sentence);
        }
    }
}
