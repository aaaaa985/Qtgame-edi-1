#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameWidget=new GameWidget(this);
    setCentralWidget(gameWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
