#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QList>
#include <QPoint>
#include <QPixmap>

class Character{
public:
    Character(){
        position.setX(60);
        position.setY(520);
        normalSpeed=6;
        speed=normalSpeed;
        isAttacking=false;
        attackRange=20;
        health=15;
        image=QPixmap(":/images/character.png");
        if (image.isNull()) {
            qDebug() << "Failed to load character image!";
        }
        else{
            image=image.scaled(25,50,Qt::KeepAspectRatio);
        }
        isHit=false;
        hitDuration=10;//受击效果持续10帧
        hitFramesLeft=0;
        isHealing=false;
        healDuration=20;//回血效果持续10帧
        healFramesLeft=0;
        plusIcon=QPixmap(":/images/plus_icon.png");
        if(plusIcon.isNull()){
            qDebug()<<"Failed to load plus icon image!";
        }
        else{
            plusIcon=plusIcon.scaled(15,15,Qt::KeepAspectRatio);
        }
        canUseBoost=true;
        boostCooldown=0;
    }
    QPointF position;
    int normalSpeed;
    int speed;
    bool isAttacking;
    int attackRange;
    int health;
    QPixmap image;
    bool isHit;
    int hitDuration;
    int hitFramesLeft;
    bool isHealing;
    int healDuration;
    int healFramesLeft;
    QPixmap plusIcon;
    bool canUseBoost;
    int boostCooldown;

    QRectF getRect() const{
        return QRectF(position.x(),position.y(),image.width(),image.height());
    }

    QRectF getAttackRect() const {
        return QRectF(position.x()-attackRange,position.y()-attackRange,image.width()+2*attackRange,image.height()+2*attackRange);
    }

    void startHitEffect(){
        isHit=true;
        hitFramesLeft=hitDuration;
        qDebug()<<"Hit effect started!";
    }


    void startHealEffect(){
        isHealing=true;
        healFramesLeft=healDuration;
        qDebug()<<"Hit effect started!";
    }


    void updateEffects(){
        if(isHit){
            if(hitFramesLeft>0){
                hitFramesLeft--;
            }
            else{
                isHit=false;
                qDebug()<<"Hit effect started!";
            }
        }
        if(isHealing){
            if(healFramesLeft>0){
                healFramesLeft--;

            }
            else{
                isHealing=false;
                qDebug()<<"Hit effect started!";
            }
        }
        if(!canUseBoost&&boostCooldown>0){
            boostCooldown--;
            if(boostCooldown==0){
                canUseBoost=true;
            }
        }
    }

    void setBoostSpeed(){
        qDebug()<<"Can use boost: "<<canUseBoost;
        if(canUseBoost){
            speed=15;
            canUseBoost=false;
            boostCooldown=20*60;//20秒大概1250帧
        }
    }

    void resetSpeed(){
        speed=normalSpeed;
        qDebug()<<"Reset speed to: "<<speed;
    }
};

class Target{
public:
    Target(){
        position.setX(rand()%800+100);
        position.setY(rand()%440+20);
        health=2;
        image=QPixmap(":/images/target.png");
        if (image.isNull()) {
            qDebug() << "Failed to load target image!";
        }
        else{
            image=image.scaled(20,20,Qt::KeepAspectRatio);
        }
        speed=3;
        direction=rand()%4;
        moveCount=0;
        changeDirectionInterval=400;
        isHit=false;
        hitDuration=10;//受击效果持续10帧
        hitFramesLeft=0;

    }
    QPointF position;
    int health;
    QPixmap image;
    int speed;
    int direction;
    int moveCount;
    int changeDirectionInterval;
    bool isHit;
    int hitDuration;
    int hitFramesLeft;

    QRectF getRect() const{
        return QRectF(position.x(),position.y(),image.width(),image.height());
    }


    void startHitEffect(){
        isHit=true;
        hitFramesLeft=hitDuration;
        qDebug()<<"Hit effect started!";
    }

    void updateEffects(){
        if(isHit){
            if(hitFramesLeft>0){
                hitFramesLeft--;
            }
            else{
                isHit=false;
                qDebug()<<"Hit effect started!";
            }
        }
    }

    void move(){
        switch(direction){
        case 0:
            position.ry()-=speed;
            break;
        case 1:
            position.rx()+=speed;
            break;
        case 2:
            position.ry()+=speed;
            break;
        case 3:
            position.rx()-=speed;
            break;
        }
        moveCount++;
        if(moveCount>=changeDirectionInterval){
            changeDirection();
            moveCount=0;
        }
    }

    void changeDirection(){
        direction=rand()%4;
    }
};

class Obstacle{
public:
    Obstacle(){
        position.setX(rand()%800+100);
        position.setY(rand()%440+20);
        width=60;
        height=60;
        speed=2;
        direction=rand()%4;//随机初始方向，0：上，1：右，2：下，3：左；
        moveCount=0;
        changeDirectionInterval=200;
        image=QPixmap(":/images/obstacle.png");
        if (image.isNull()) {
            qDebug() << "Failed to load obstacle image!";
        }
        else{
            image=image.scaled(60,60,Qt::KeepAspectRatio);
        }
    }
    QPointF position;
    int width;
    int height;
    int speed;
    int direction;
    int moveCount;
    int changeDirectionInterval;
    QPixmap image;

    QRectF getRect() const{
        return QRectF(position.x(),position.y(),width,height);
    }

    void move(){
        switch (direction){
        case 0:
            position.ry()-=speed;
            break;
        case 1:
            position.rx()+=speed;
            break;
        case 2:
            position.ry()+=speed;
            break;
        case 3:
            position.rx()-=speed;
            break;
        }
        moveCount++;
        if(moveCount>=changeDirectionInterval){
            changeDirection();
            moveCount=0;
        }
    }

    void changeDirection(){
        direction=rand()%4;
    }
};

class HealingPoint{
public:
    HealingPoint(){
        position.setX(rand()%800+100);
        position.setY(rand()%440+20);
        width=20;
        height=20;
        image=QPixmap(":/images/healing_point.png");
        if (image.isNull()) {
            qDebug() << "Failed to load healing_point image!";
        }
        else{
            image=image.scaled(20,20,Qt::KeepAspectRatio);
        }
    }
    int width;
    int height;
    QPointF position;
    QPixmap image;

    QRectF getRect() const{
        return QRectF(position.x(),position.y(),width,height);
    }
};

class Portal{
public:
    Portal(){
        position.setX(rand()%800+100);
        position.setY(rand()%440+20);
        image=QPixmap(":/images/portal.png");
        if(image.isNull()){
            qDebug()<<"Failed to load portal image!";
        }
        else{
            image=image.scaled(15,55,Qt::KeepAspectRatio);
        }
        pairedPortal=nullptr;
    }
    QPointF position;
    QPixmap image;
    Portal* pairedPortal=nullptr;

    QRectF getRect() const{
        return QRectF(position.x(),position.y(),image.width(),image.height());

    }
    Portal(const Portal&)=delete;
    Portal& operator=(const Portal&)=delete;
};

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
    ~GameWidget();
protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void updateGame();
private:
    QTimer *timer;
    Character character;
    QList<Target> targets;
    QList<Obstacle> obstacles;
    QList<HealingPoint> healingPoints;
    QList<Portal*>portals;
    bool gameOver;
    QPixmap backgroundImage;

    bool isCollision(const Character &character,const Target &target);
    bool isCollisionWithObstacle(const Character &character,const Obstacle &obstacle);
    bool isCollisionWithHealingPoint(const Character &character,const HealingPoint &healingPoint);
    bool isCollisionWithPortal(const Character &character,const Portal &portal);
    void handleAttack();
    bool isOverlapping(const QRectF& rect,const QList<Target>& targets,const QList<Obstacle>& obstacles,const Character& character,const QList<HealingPoint>& healingPoints,const QList<Portal*>& portals);
};




#endif // GAMEWIDGET_H








