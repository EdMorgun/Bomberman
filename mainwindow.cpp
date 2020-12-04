#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QPainter"
#include "QTimer"
#include "QKeyEvent"
#include "QMessageBox"

#include "QDebug"

int SIZE;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SIZE = 48;

    game = Game::getInstance();
    this->setGeometry(30,30, SIZE*15, SIZE*13);

    oneFrame = new QTimer();
    connect(oneFrame, SIGNAL(timeout()), this, SLOT(frame()));
    oneFrame->start(32);
}

MainWindow::~MainWindow()
{
    delete oneFrame;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    this->setGeometry(30, 30, this->height()*16/13, this->height());
    this->setGeometry(30, 30, this->width(), this->width()*13/16);
    SIZE = this->height()/13;
    QPainter painter(this);
    game->paintGame(&painter);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
     game->reactionForPressKeys(e);
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
     game->reactionForReleaseKeys(e);
}

void MainWindow::frame()
{
    game->frame();
    update();
    if(game->getEnd())
    {
       QMessageBox::StandardButton reply;
       switch(game->getResultGame())
       {
       case 1 :
           reply = QMessageBox::question(this, "Congratulations!",
                    "You really passed this level and didn't crash him!\nTY for PLAY my game!!!\n Play again?",
                    QMessageBox::Yes|QMessageBox::No);
           if(reply == QMessageBox::Yes)
           {
               game->newGame();
           }
           else qApp->quit();
           break;
       case 2 :
           reply = QMessageBox::question(this, "Game Over!",
                    "You were killed by enemy\nPlay again?",
                    QMessageBox::Yes|QMessageBox::No);
           if(reply == QMessageBox::Yes)
           {
               game->newGame();
           }
           else qApp->quit();
           break;
       }
    }
}
