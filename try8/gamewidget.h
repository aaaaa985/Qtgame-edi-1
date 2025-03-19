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
        position.setY(320);
        speed=10;
        isAttacking=false;
        attackRange=20;
        health=10;
        image=QPixmap(":/images/character.png");
        if (image.isNull()) {
            qDebug() << "Failed to load character image!";
        }
        else{
            image=image.scaled(25,50,Qt::KeepAspectRatio);
        }
    }
    QPointF position;
    int speed;
    bool isAttacking;
    int attackRange;
    int health;
    QPixmap image;

    QRectF getRect() const{
        return QRectF(position.x(),position.y(),25,50);
    }

    QRectF getAttackRect() const {
        return QRectF(position.x()-attackRange,position.y()-attackRange,25+2*attackRange,50+2*attackRange);
    }
};

class Target{
public:
    Target(){
        position.setX(rand()%600+100);
        position.setY(rand()%240+20);
        health=100;
        image=QPixmap(":/images/target.png");
        if (image.isNull()) {
            qDebug() << "Failed to load target image!";
        }
        else{
            image=image.scaled(20,20,Qt::KeepAspectRatio);
        }
    }
    QPointF position;
    int health;
    QPixmap image;

    QRectF getRect() const{
        return QRectF(position.x(),position.y(),20,20);
    }
};

class Obstacle{
public:
    Obstacle(){
        position.setX(rand()%600+100);
        position.setY(rand()%200+20);
        width=60;
        height=60;
        speed=2;
        direction=rand()%4;//随机初始方向，0：上，1：右，2：下，3：左；
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
    }

    void changeDirection(){
        direction=rand()%4;
    }
};

class HealingPoint{
public:
    HealingPoint(){
        position.setX(rand()%600+100);
        position.setY(rand()%240+20);
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
    QPointF position;
    int width;
    int height;
    QPixmap image;

    QRectF getRect() const{
        return QRectF(position.x(),position.y(),width,height);
    }
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
    bool gameOver;
    QPixmap backgroundImage;

    bool isCollision(const Character &character,const Target &target);
    bool isCollisionWithObstacle(const Character &character,const Obstacle &obstacle);
    bool isCollisionWithHealingPoint(const Character &character,const HealingPoint &healingPoint);
    void handleAttack();
    bool isOverlapping(const QRectF& rect,const QList<Target>& targets,const QList<Obstacle>& obstacles,const Character& character,const QList<HealingPoint>& healingPoints);
};




#endif // GAMEWIDGET_H








