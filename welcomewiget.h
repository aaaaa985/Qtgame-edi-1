#ifndef WELCOMEWIGET_H
#define WELCOMEWIGET_H

#endif // WELCOMEWIGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QSpacerItem>
#include <QPaintEvent>
#include <QPainter>

class WelcomeWidget:public QWidget{
    Q_OBJECT
public:
    explicit WelcomeWidget(QWidget *parent=nullptr);
    ~WelcomeWidget();

signals:
    void startGameClicked();

private slots:
    void onStartGameButtonClicked();

protected:
    void paintEvent(QPaintEvent *event)override;

private:
    QPushButton *startGameButton;
    QPixmap backgroundImage;
};






