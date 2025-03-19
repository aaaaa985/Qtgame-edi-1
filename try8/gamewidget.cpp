#include "gamewidget.h"
#include <QPainter>

GameWidget::GameWidget(QWidget *parent)
    : QWidget{parent}
{


    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&GameWidget::updateGame);
    if(timer!=nullptr){
        timer->start(16);
    }


    //初始化一些目标
    for(int i=0;i<5;++i){
        Target target;
        while(isOverlapping(target.getRect(),targets,obstacles,character,healingPoints)){
            target.position.setX(rand()%600+100);
            target.position.setY(rand()%240+20);
        }
        targets.append(target);
    }

    //初始化一些障碍
    for(int i=0;i<6;i++){
        Obstacle obstacle;
        while(isOverlapping(obstacle.getRect(),targets,obstacles,character,healingPoints)){
            obstacle.position.setX(rand()%600+100);
            obstacle.position.setY(rand()%200+20);
        }
        obstacles.append(obstacle);
    }

    //初始化回血点
    for(int i=0;i<3;i++){
        HealingPoint healingPoint;
        while (isOverlapping(healingPoint.getRect(),targets,obstacles,character,healingPoints)){
            healingPoint.position.setX(rand()%600+100);
            healingPoint.position.setY(rand()%240+20);
        }
        healingPoints.append(healingPoint);
    }

    gameOver=false;

    //确保GameWidget可以获得焦点
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}


GameWidget::~GameWidget(){
    delete timer;
}

void GameWidget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);


    //绘制人物
    painter.setBrush(Qt::blue);
    painter.drawRect(character.position.x(),character.position.y(),25,50);
    //绘制目标
    painter.setBrush(Qt::yellow);
    for(const auto &target:targets){
        painter.drawRect(target.position.x(),target.position.y(),20,20);
    }

    //绘制障碍
    painter.setBrush(Qt::red);
    for(const auto &obstacle:obstacles){
        painter.drawRect(obstacle.position.x(),obstacle.position.y(),obstacle.width,obstacle.height);
    }

    //绘制回血点
    painter.setBrush(Qt::green);
    for(const auto &healingPoint:healingPoints){
        painter.drawRect(healingPoint.position.x(),healingPoint.position.y(),healingPoint.width,healingPoint.height);
    }



    //绘制游戏结束信息
    if(gameOver){
        painter.setFont(QFont("Impact",100));
        painter.setPen(QColor(0,0,0,128));//半透明黑色
        painter.drawText(rect().translated(5,5),Qt::AlignCenter,character.health<=0?"Lose":"Win!");
        painter.setPen(Qt::red);
        if(character.health<=0){
            painter.drawText(rect(),Qt::AlignCenter,"Lose");
        }
        else{
            painter.drawText(rect(),Qt::AlignCenter,"Win!");
        }
    }
}

void GameWidget::keyPressEvent(QKeyEvent *event){
    QPointF newPosition=character.position;
    switch(event->key()){
    case Qt::Key_Left:
        newPosition.rx()-=character.speed;
        if(newPosition.x()<0){
            newPosition.setX(0);
        }
        break;
    case Qt::Key_Right:
        newPosition.rx()+=character.speed;
        if(newPosition.x()+25>width()){
            newPosition.setX(width()-25);
        }
        break;
    case Qt::Key_Up:
        newPosition.ry()-=character.speed;
        if(newPosition.y()<0){
            newPosition.setY(0);
        }
        break;
    case Qt::Key_Down:
        newPosition.ry()+=character.speed;
        if(newPosition.y()+50>height()){
            newPosition.setY(height()-50);
        }
        break;
    case Qt::Key_Space:
        character.isAttacking=true;
        handleAttack();
        break;
    }

    Character tempCharacter=character;
    tempCharacter.position=newPosition;
    QRectF newRect=tempCharacter.getRect();

    bool collision=false;
    for(const auto &obstacle:obstacles){
        Character tempCharacter=character;
        tempCharacter.position=newPosition;
        if(isCollisionWithObstacle(tempCharacter,obstacle)){
            collision =true;
            if(character.health>0){
                character.health--;
            }
            break;
        }
    }

    for(auto it=healingPoints.begin();it!=healingPoints.end();){
        if(isCollisionWithHealingPoint(tempCharacter,*it)){
            if(character.health<10){
                character.health++;
            }
            it=healingPoints.erase(it);
        }
        else{
            ++it;
        }
    }
    if(!collision){
        character.position=newPosition;
    }

    if(character.health<=0){
        gameOver=true;
    }

    update();
}


bool GameWidget::isOverlapping(const QRectF& rect,const QList<Target>& targets,const QList<Obstacle>& obstacles,const Character& character,const QList<HealingPoint>& healingPoints){
    if(rect.intersects(character.getRect())){
        return true;
    }
    for(const auto& target:targets){
        if(rect.intersects(target.getRect())){
            return true;
        }
    }
    for(const auto& obstacle:obstacles){
        if(rect.intersects(obstacle.getRect())){
            return true;
        }
    }
    for(const auto& healingPoint:healingPoints){
        if(rect.intersects(healingPoint.getRect())){
            return true;
        }
    }
    return false;
}

void GameWidget::updateGame(){
    if(gameOver)
        return;

    for(auto& obstacle:obstacles){
        obstacle.move();

        //处理障碍碰到边界的情况
        if(obstacle.position.x()<0||obstacle.position.x()+obstacle.width>width()||obstacle.position.y()<0||obstacle.position.y()+obstacle.height>height()){
            obstacle.changeDirection();
        }
    }

    if(targets.empty()){
        gameOver=true;
    }

    if(character.health<=0){
        gameOver=true;
    }

    update();
}

bool GameWidget::isCollision(const Character &character,const Target &target){
    QRectF charRect(character.position.x(),character.position.y(),25,50);
    QRectF targetRect(target.position.x(),target.position.y(),20,20);
    return charRect.intersects(targetRect);
}

bool GameWidget::isCollisionWithObstacle(const Character &character,const Obstacle &obstacle){
    QRectF charRect(character.position.x(),character.position.y(),25,50);
    QRectF obstacleRect(obstacle.position.x(),obstacle.position.y(),60,60);
    return charRect.intersects(obstacleRect);
}

bool GameWidget::isCollisionWithHealingPoint(const Character &character,const HealingPoint &healingPoint){
    QRectF charRect(character.position.x(),character.position.y(),25,50);
    QRectF healingPointRect(healingPoint.position.x(),healingPoint.position.y(),healingPoint.width,healingPoint.height);
    return charRect.intersects(healingPointRect);
}

void GameWidget::handleAttack(){
    QRectF attackRect=character.getAttackRect();
    for(auto it=targets.begin();it!=targets.end();){
        if(attackRect.intersects(it->getRect())){
            it->health-=100;
            if(it->health<=0){
                it=targets.erase(it);
            }
            else{
                ++it;
            }
        }
        else{
            ++it;
        }
    }
    character.isAttacking=false;
}









