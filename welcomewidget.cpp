#include "welcomewiget.h"
#include <QVBoxLayout>

WelcomeWidget::WelcomeWidget(QWidget *parent):QWidget(parent){
    startGameButton=new QPushButton("进入游戏",this);
    if(startGameButton){
        qDebug()<<"Button pointer is valid";
    }
    else{
        qDebug()<<"Button pointer isinvalid";
    }


    QSizePolicy sizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    startGameButton->setSizePolicy(sizePolicy);

    QVBoxLayout *verticalLayout=new QVBoxLayout(this);

    QSpacerItem *verticalSpacerTop=new QSpacerItem(20,730,QSizePolicy::Minimum,QSizePolicy::Expanding);
    verticalLayout->addItem(verticalSpacerTop);

    QHBoxLayout *horizontalLayout=new QHBoxLayout();

    QSpacerItem *horizontalSpacerLeft=new QSpacerItem(200,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
    horizontalLayout->addItem(horizontalSpacerLeft);

    horizontalLayout->addWidget(startGameButton);

   QSpacerItem *horizontalSpacerRight=new QSpacerItem(200,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
    horizontalLayout->addItem(horizontalSpacerRight);

    verticalLayout->addLayout(horizontalLayout);

    QSpacerItem *verticalSpacerBottom=new QSpacerItem(20,30,QSizePolicy::Minimum,QSizePolicy::Expanding);
    verticalLayout->addItem(verticalSpacerBottom);

    QFont buttonFont("Arial",30);
    buttonFont.setBold(true);
    startGameButton->setFont(buttonFont);
    startGameButton->update();

    startGameButton->setStyleSheet(
        "QPushButton{"
        "   width:200px;"
        "   height:40px;"
        "   background-color:#4CAF50;"
        "   color:white;"
        "   border:2px solid #0000FF;"
        "   border-radius:10px;"
        "   padding:5px;"
        "   margin:5px;"
        "   font-weight:bold;"
        "}"
        "QPushButton:hover{"
        "   background-color:#45a049;"
        "}"
        "QPushButton:pressed{"
        "   background-color:#3e8e41;"
        "}"
    );

    backgroundImage=QPixmap(":/images/background'.png");


    setFixedSize(600,800);

    connect(startGameButton,&QPushButton::clicked,this,&WelcomeWidget::onStartGameButtonClicked);
}

WelcomeWidget::~WelcomeWidget(){

}

void WelcomeWidget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(rect(),backgroundImage.scaled(size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
}

void WelcomeWidget::onStartGameButtonClicked(){
    emit startGameClicked();
}







