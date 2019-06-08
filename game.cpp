#include "game.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QTime>
#include <QCoreApplication>


Game::Game(QWidget *parent) : QGraphicsView(parent), gameTimerPeriod(100),
    ghost1Speed(200), ghost2Speed(200), ghost3Speed(200), ghost4Speed(500)
{
    //create Scene
    gameScene = new QGraphicsScene();
    gameScene->setSceneRect(0, 0, 1400, 900);

    //create the view
    setFixedSize(1400,900);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(gameScene);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(10, 10, 10, 255));
    setBackgroundBrush(brush);
    createOverWindow();

    //initialize data members
    powerFlag = false;
    start_flag = false;
    ghost1Flag = false;
    ghost2Flag = false;
    ghost3Flag = false;
    ghost4Flag = false;
    pointPerDot = 100;
    powerLeftTime = -1;
    ghost1LeftTime = -1;
    ghost2LeftTime = -1;
    ghost3LeftTime = -1;
    ghost4LeftTime = -1;

    //create & connect timers
    gameTimer = new QTimer(this);
    powerTimer = new QTimer(this);
    pacTimer = new QTimer(this);
    ghost1Timer = new QTimer(this);
    ghost2Timer = new QTimer(this);
    ghost3Timer = new QTimer(this);
    ghost4Timer = new QTimer(this);
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(gameTimeoutFunc()));
    connect(powerTimer,SIGNAL(timeout()),this,SLOT(powerTimeoutFunc()));
    connect(pacTimer,SIGNAL(timeout()),this,SLOT(pacMove()));
    connect(ghost1Timer,SIGNAL(timeout()),this,SLOT(ghost1Move()));
    connect(ghost2Timer,SIGNAL(timeout()),this,SLOT(ghost2Move()));
    connect(ghost3Timer,SIGNAL(timeout()),this,SLOT(ghost3Move()));
    connect(ghost4Timer,SIGNAL(timeout()),this,SLOT(ghost4Move()));
}

void Game::displayMenu(){
    //menu background
    QGraphicsRectItem *back = new QGraphicsRectItem();
    back->setRect(0, 0, 1400, 900);
    back->setPos(0, 0);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(20, 20, 20, 255));
    back->setBrush(brush);
    back->setZValue(4);
    addToScene(back);
    menuItemList.append(back);

    //create text
    QGraphicsTextItem* text = new QGraphicsTextItem("Super PacMan");
    QFont font = text->font();
    font.setPointSize(50);
    font.setBold(true);
    text->setFont(font);
    text->setPos(700-text->boundingRect().width()/2, 180);
    text->setZValue(5);
    text->setDefaultTextColor(QColor(41, 255, 41, 255));
    addToScene(text);
    menuItemList.append(text);

    //create button
    Button *playButton = new Button("Play");
    playButton->setPos(700-playButton->rect().width()/2, 650);
    playButton->setZValue(5);
    connect(playButton, SIGNAL(clicked()) , this, SLOT(play()));
    addToScene(playButton);
    menuItemList.append(playButton);
    Button *closeButton = new Button("Quit");
    closeButton->setPos(700-closeButton->rect().width()/2, 700);
    closeButton->setZValue(5);
    connect(closeButton, SIGNAL(clicked()) , this, SLOT(close()));
    addToScene(closeButton);
    menuItemList.append(closeButton);

    //menu icons
    QGraphicsPixmapItem *p1 = new QGraphicsPixmapItem();
    p1->setPixmap(QPixmap(":/new/prefix1/imgs/pacman_right.png"));
    p1->setPos(585,320);
    p1->setScale(0.16);
    p1->setZValue(5);
    addToScene(p1);
    menuItemList.append(p1);
    QGraphicsPixmapItem *p2 = new QGraphicsPixmapItem();
    p2->setPixmap(QPixmap(":/new/prefix1/imgs/mouse.png"));
    p2->setPos(400,360);
    p2->setScale(0.2);
    p2->setZValue(5);
    addToScene(p2);
    menuItemList.append(p2);
    QGraphicsPixmapItem *p3 = new QGraphicsPixmapItem();
    p3->setPixmap(QPixmap(":/new/prefix1/imgs/angel.png"));
    p3->setPos(215,360);
    p3->setScale(0.2);
    p3->setZValue(5);
    addToScene(p3);
    menuItemList.append(p3);
    QGraphicsPixmapItem *p4 = new QGraphicsPixmapItem();
    p4->setPixmap(QPixmap(":/new/prefix1/imgs/bomber.png"));
    p4->setPos(850,360);
    p4->setScale(0.2);
    p4->setZValue(5);
    addToScene(p4);
    menuItemList.append(p4);
    QGraphicsPixmapItem *p5 = new QGraphicsPixmapItem();
    p5->setPixmap(QPixmap(":/new/prefix1/imgs/penguin.png"));
    p5->setPos(1035,360);
    p5->setScale(0.2);
    p5->setZValue(5);
    addToScene(p5);
    menuItemList.append(p5);
}


void Game::createOverWindow(){
    QBrush brush;
    overWindow = new QGraphicsRectItem();
    overWindow->setRect(0, 0, 450, 400);
    overWindow->setPos(700 - 225, 250);
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0, 0, 0, 255));
    overWindow->setBrush(brush);
    overWindow->setZValue(10);

    overWindow_b = new QGraphicsRectItem();
    overWindow_b->setRect(0, 0, 470, 420);
    overWindow_b->setPos(700 - 235, 240);
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(143, 143, 143, 255));
    overWindow_b->setBrush(brush);
    overWindow_b->setZValue(9);

    overText = new QGraphicsTextItem("Game Over");
    QFont font = overText->font();
    font.setPointSize(24);
    font.setBold(true);
    overText->setFont(font);
    overText->setPos(700-overText->boundingRect().width()/2, 320);
    overText->setZValue(11);
    overText->setDefaultTextColor(QColor(41, 255, 41, 255));

    overResetButton = new Button("Play Again");
    overResetButton->setPos(700-overResetButton->rect().width()/2, 475);
    overResetButton->setZValue(11);
    connect(overResetButton, SIGNAL(clicked()) , this, SLOT(reset()));

    overQuitButton = new Button("Quit");
    overQuitButton->setPos(700-overQuitButton->rect().width()/2, 550);
    overQuitButton->setZValue(11);
    connect(overQuitButton, SIGNAL(clicked()) , this, SLOT(close()));

    addToScene(overWindow);
    addToScene(overWindow_b);
    addToScene(overResetButton);
    addToScene(overQuitButton);
    addToScene(overText);
    hideOverWindow();
}

void Game::play(){
    //clear menu items
    int n = menuItemList.size();
    for(int i =0; i < n; i++){
        removeFromScene(menuItemList[i]);
    }
    //create map
    map = new GameMap();
    map->ghost1->setVisible(false);
    map->ghost2->setVisible(false);
    map->ghost3->setVisible(false);
    map->ghost4->setVisible(false);
    //show point counter
    displayPointCounter();
    //create game button
    startButton = new Button("Start");
    startButton->setPos(1125, 170);
    startButton->setZValue(2);
    connect(startButton, SIGNAL(clicked()) , this, SLOT(start()));
    addToScene(startButton);

    resetButton = new Button("reset");
    resetButton->setPos(1125, 250);
    resetButton->setZValue(2);
    connect(resetButton, SIGNAL(clicked()) , this, SLOT(reset()));
    addToScene(resetButton);

    easyButton = new Button("easy mode");
    easyButton->setPos(1125, 380);
    easyButton->setZValue(2);
    connect(easyButton, SIGNAL(clicked()) , this, SLOT(changeToEasy()));
    addToScene(easyButton);

    normalButton = new Button("normal mode");
    normalButton->setPos(1125, 450);
    normalButton->setZValue(2);
    connect(normalButton, SIGNAL(clicked()) , this, SLOT(changeToNormal()));
    addToScene(normalButton);

    hardButton = new Button("hard mode");
    hardButton->setPos(1125, 520);
    hardButton->setZValue(2);
    connect(hardButton, SIGNAL(clicked()) , this, SLOT(changeToHard()));
    addToScene(hardButton);

    quitButton = new Button("Quit");
    quitButton->setPos(1125, 700);
    quitButton->setZValue(2);
    connect(quitButton, SIGNAL(clicked()) , this, SLOT(close()));
    addToScene(quitButton);

    ghost1EnableButton = new Button("enable");
    ghost1EnableButton->setPos(130, 150);
    ghost1EnableButton->setZValue(2);
    connect(ghost1EnableButton, SIGNAL(clicked()) , this, SLOT(ghost1Enable()));
    addToScene(ghost1EnableButton);

    ghost2EnableButton = new Button("enable");
    ghost2EnableButton->setPos(130, 325);
    ghost2EnableButton->setZValue(2);
    connect(ghost2EnableButton, SIGNAL(clicked()) , this, SLOT(ghost2Enable()));
    addToScene(ghost2EnableButton);

    ghost3EnableButton = new Button("enable");
    ghost3EnableButton->setPos(130, 500);
    ghost3EnableButton->setZValue(2);
    connect(ghost3EnableButton, SIGNAL(clicked()) , this, SLOT(ghost3Enable()));
    addToScene(ghost3EnableButton);

    ghost4EnableButton = new Button("enable");
    ghost4EnableButton->setPos(130, 675);
    ghost4EnableButton->setZValue(2);
    connect(ghost4EnableButton, SIGNAL(clicked()) , this, SLOT(ghost4Enable()));
    addToScene(ghost4EnableButton);

    //add icons
    g1 = new QGraphicsPixmapItem();
    g1->setPixmap(QPixmap(":/new/prefix1/imgs/angel.png"));
    g1->setPos(25, 150);
    g1->setScale(0.12);
    g1->setZValue(2);
    addToScene(g1);
    g2 = new QGraphicsPixmapItem();
    g2->setPixmap(QPixmap(":/new/prefix1/imgs/mouse.png"));
    g2->setPos(25, 325);
    g2->setScale(0.12);
    g2->setZValue(2);
    addToScene(g2);
    g3 = new QGraphicsPixmapItem();
    g3->setPixmap(QPixmap(":/new/prefix1/imgs/penguin.png"));
    g3->setPos(25, 500);
    g3->setScale(0.12);
    g3->setZValue(2);
    addToScene(g3);
    g4 = new QGraphicsPixmapItem();
    g4->setPixmap(QPixmap(":/new/prefix1/imgs/bomber.png"));
    g4->setPos(25, 670);
    g4->setScale(0.12);
    g4->setZValue(2);
    addToScene(g4);
}

void Game::start(){
    if(start_flag==false){
        start_flag = true;
        //start timers
        gameTimer->start(gameTimerPeriod);
        pacTimer->start(100);
        if(ghost1Flag)ghost1Timer->start(ghost1Speed);
        if(ghost2Flag)ghost2Timer->start(ghost2Speed);
        if(ghost3Flag)ghost3Timer->start(ghost3Speed);
        if(ghost4Flag)ghost4Timer->start(ghost4Speed);
    }

}

void Game::delay(int msec){
    QTime deadline= QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < deadline ){QCoreApplication::processEvents();}
}

void Game::reset(){
    if(start_flag==false){
        hideOverWindow();
    }
    start_flag = false;
    stopTimers();
    map->reset();
    changeCurrentScore(0);

    ghost1Flag = true;
    map->ghost1->setVisible(true);
    ghost2Flag = true;
    map->ghost2->setVisible(true);
    ghost3Flag = true;
    map->ghost3->setVisible(true);
    ghost4Flag = true;
    map->ghost4->setVisible(true);
}

void Game::gameTimeoutFunc(){
    //stop power pellet time
    if(powerFlag && powerLeftTime<=0){
        powerFlag = false;
        map->pacman->setScale(0.02);
        powerTimer->stop();
    }
    //eat ghosts
    if(powerFlag && map->pacman->currentBox==map->ghost1->currentBox){
        changeCurrentScore(getCurrentScore()+500);
        ghost1Timer->stop();
        map->resetGhost1();
        map->ghost1->setVisible(false);
        ghost1LeftTime = 50;
    }
    if(powerFlag && map->pacman->currentBox==map->ghost2->currentBox){
        changeCurrentScore(getCurrentScore()+500);
        ghost2Timer->stop();
        map->resetGhost2();
        map->ghost2->setVisible(false);
        ghost2LeftTime = 50;
    }
    if(powerFlag && map->pacman->currentBox==map->ghost3->currentBox){
        changeCurrentScore(getCurrentScore()+500);
        ghost3Timer->stop();
        map->resetGhost3();
        map->ghost3->setVisible(false);
        ghost3LeftTime = 50;
    }
    if(powerFlag && map->pacman->currentBox==map->ghost4->currentBox){
        changeCurrentScore(getCurrentScore()+500);
        ghost4Timer->stop();
        map->resetGhost4();
        map->ghost4->setVisible(false);
        ghost4LeftTime = 50;
    }
    //ghosts recover
    if(ghost1LeftTime>0){ghost1LeftTime-=1;}
    else if(ghost1LeftTime==0){
        ghost1LeftTime-=1;
        map->ghost1->setVisible(true);
        ghost1Timer->start(ghost1Speed);
    }
    if(ghost2LeftTime>0){ghost2LeftTime-=1;}
    else if(ghost2LeftTime==0){
        ghost2LeftTime-=1;
        map->ghost2->setVisible(true);
        ghost2Timer->start(ghost2Speed);
    }
    if(ghost3LeftTime>0){ghost3LeftTime-=1;}
    else if(ghost3LeftTime==0){
        ghost3LeftTime-=1;
        map->ghost3->setVisible(true);
        ghost3Timer->start(ghost3Speed);
    }
    if(ghost4LeftTime>0){ghost4LeftTime-=1;}
    else if(ghost4LeftTime==0){
        ghost4LeftTime-=1;
        map->ghost4->setVisible(true);
        ghost4Timer->start(ghost4Speed);
    }
    //game over situation
    if(map->getDotLeft()==0 && start_flag==true){
        map->reduceDotLeft();
        start_flag = false;
        stopTimers();
        displayOverWindow();
    }
    else if(map->pacman->currentBox==map->ghost1->currentBox && start_flag==true){
        start_flag = false;
        stopTimers();
        displayOverWindow();
    }
    else if(map->pacman->currentBox==map->ghost2->currentBox && start_flag==true){
        start_flag = false;
        stopTimers();
        displayOverWindow();
    }
    else if(map->pacman->currentBox==map->ghost3->currentBox && start_flag==true){
        start_flag = false;
        stopTimers();
        displayOverWindow();
    }
    else if(map->pacman->currentBox==map->ghost4->currentBox && start_flag==true){
        start_flag = false;
        stopTimers();
        displayOverWindow();
    }
}

void Game::stopTimers(){
    map->pacman->setScale(0.02);
    gameTimer->stop();
    powerTimer->stop();
    pacTimer->stop();
    ghost1Timer->stop();
    ghost2Timer->stop();
    ghost3Timer->stop();
    ghost4Timer->stop();
}

void Game::startPowerTimer(int time, int freq){
    powerLeftTime = time;
    powerFlag = true;
    powerTimer->start(freq);
}

void Game::powerTimeoutFunc(){
    if(powerLeftTime%3==0)map->pacman->setScale(0.03);
    else if(powerLeftTime%3==1)map->pacman->setScale(0.025);
    else map->pacman->setScale(0.02);
    powerLeftTime--;
}

void Game::pacMove(){map->pacman->move();}
void Game::ghost1Move(){map->ghost1->move();}
void Game::ghost2Move(){map->ghost2->move();}
void Game::ghost3Move(){map->ghost3->move();}
void Game::ghost4Move(){map->ghost4->move();}

void Game::ghost1Enable(){
    if(start_flag)return;
    ghost1Flag = !ghost1Flag;
    if(ghost1Flag==false){map->ghost1->setVisible(false);}
    else{map->ghost1->setVisible(true);}
}
void Game::ghost2Enable(){
    if(start_flag)return;
    ghost2Flag = !ghost2Flag;
    if(ghost2Flag==false){map->ghost2->setVisible(false);}
    else{map->ghost2->setVisible(true);}
}
void Game::ghost3Enable(){
    if(start_flag)return;
    ghost3Flag = !ghost3Flag;
    if(ghost3Flag==false){map->ghost3->setVisible(false);}
    else{map->ghost3->setVisible(true);}
}
void Game::ghost4Enable(){
    if(start_flag)return;
    ghost4Flag = !ghost4Flag;
    if(ghost4Flag==false){map->ghost4->setVisible(false);}
    else{map->ghost4->setVisible(true);}
}


void Game::changeCurrentScore(int score){
    currentPointNum = score;
    currentPoint->setPlainText(QString::number(currentPointNum));
    if(score>highScoreNum){
        highScoreNum = score;
        highScore->setPlainText(QString::number(highScoreNum));
    }
}
int Game::getCurrentScore(){return currentPointNum;}

void Game::displayPointCounter(){
    upText = new QGraphicsTextItem("1UP");
    upText->setPos(50, 20);
    upText->setDefaultTextColor(Qt::white);
    QFont font = upText->font();
    font.setPixelSize(30);
    upText->setFont(font);
    addToScene(upText);

    highScoreText = new QGraphicsTextItem("HIGH SCORE");
    highScoreText->setPos(1075, 20);
    highScoreText->setDefaultTextColor(Qt::white);
    font = highScoreText->font();
    font.setPixelSize(30);
    highScoreText->setFont(font);
    addToScene(highScoreText);

    currentPointNum = 0;
    highScoreNum = 0;

    highScore = new QGraphicsTextItem(QString::number(highScoreNum));
    highScore->setPos(1300, 20);
    highScore->setDefaultTextColor(Qt::white);
    font = highScore->font();
    font.setPixelSize(30);
    highScore->setFont(font);
    addToScene(highScore);

    currentPoint = new QGraphicsTextItem(QString::number(currentPointNum));
    currentPoint->setPos(175, 20);
    currentPoint->setDefaultTextColor(Qt::white);
    font = currentPoint->font();
    font.setPixelSize(30);
    currentPoint->setFont(font);
    addToScene(currentPoint);
}

void Game::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Up:
        map->pacman->changeDir(1);
        break;
    case Qt::Key_Down:
        map->pacman->changeDir(2);
        break;
    case Qt::Key_Left:
        map->pacman->changeDir(3);
        break;
    case Qt::Key_Right:
        map->pacman->changeDir(4);
        break;
    default: break;
    }
}
void Game::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()==false)map->pacman->changeDir(0);
}

void Game::displayOverWindow(){
    overWindow->setVisible(true);
    overWindow_b->setVisible(true);
    overResetButton->setVisible(true);
    overQuitButton->setVisible(true);
    overText->setVisible(true);
}
void Game::hideOverWindow(){
    overWindow->setVisible(false);
    overWindow_b->setVisible(false);
    overResetButton->setVisible(false);
    overQuitButton->setVisible(false);
    overText->setVisible(false);
}

void Game::addToScene(QGraphicsItem *item){gameScene->addItem(item);}
void Game::removeFromScene(QGraphicsItem *item){gameScene->removeItem(item);}

GameMap* Game::getMap(){return map;}
bool Game::getGhost1Flag(){return ghost1Flag;}
bool Game::getGhost4Flag(){return ghost4Flag;}

void Game::changeToEasy(){
    ghost1Speed = 500;
    ghost2Speed = 500;
    ghost3Speed = 500;
    ghost4Speed = 500;
}
void Game::changeToNormal(){
    ghost1Speed = 200;
    ghost2Speed = 200;
    ghost3Speed = 200;
    ghost4Speed = 500;
}
void Game::changeToHard(){
    ghost1Speed = 150;
    ghost2Speed = 150;
    ghost3Speed = 150;
    ghost4Speed = 200;
}
