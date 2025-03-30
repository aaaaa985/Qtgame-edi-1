#include "gamewidget.h"
#include "welcomewiget.h"

#include <QApplication>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{

    //初始化随机数种子
    srand(time(NULL));

    QApplication a(argc, argv);

    WelcomeWidget welcomeWidget;
    GameWidget gameWidget;

    QObject::connect(&welcomeWidget,&WelcomeWidget::startGameClicked,[&](){
        welcomeWidget.hide();
        gameWidget.show();
    });

    welcomeWidget.show();

    return a.exec();
}






