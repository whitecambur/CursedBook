#ifndef MOVEPLAYER_H
#define MOVEPLAYER_H

class QPainter;
class GameController;
class MoviePlayer
{
public:
    MoviePlayer();
    void SetMovieTask(int MovieTaskType);       //收取一个动画任务

    void Paint(QPainter*painter);
private:
    int MyMovieTask;                              //当前正在执行的动画任务
    int MyTimer;                                //内部计时器
};
enum MoveTask{

};

#endif // MOVEPLAYER_H
