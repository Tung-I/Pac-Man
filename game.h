#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "gamemap.h"
#include "button.h"

class Game;
extern Game *game;

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    //constructor
    Game(QWidget *parent = nullptr);

    //display
    void addToScene(QGraphicsItem *item);
    void removeFromScene(QGraphicsItem *item);
    void displayMenu();
    void createOverWindow();
    void displayOverWindow();
    void hideOverWindow();
    void displayPointCounter();

    //event
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    //change and get
    void changeCurrentScore(int score);
    int getCurrentScore();
    int pointPerDot;
    bool getPowerFlag(){return powerFlag;}
    GameMap *getMap();
    bool getGhost1Flag();
    bool getGhost4Flag();

    //timer
    void startPowerTimer(int time, int freq);
    void stopTimers();
    void delay(int msec);


signals:

public slots:
    void play();
    void start();
    void reset();
    void gameTimeoutFunc(); //call every 100 ms
    void powerTimeoutFunc(); //show the difference after eating pellet

    void pacMove();
    void ghost1Move();
    void ghost2Move();
    void ghost3Move();
    void ghost4Move();

    void ghost1Enable();
    void ghost2Enable();
    void ghost3Enable();
    void ghost4Enable();

    void changeToEasy();
    void changeToNormal();
    void changeToHard();



private:
    //scenes & background
    QGraphicsScene *gameScene;
    GameMap *map;
    QList <QGraphicsItem*> menuItemList;
    QGraphicsRectItem *overWindow;
    QGraphicsRectItem *overWindow_b;


    //buttons
    Button *overResetButton;
    Button *overQuitButton;
    Button *startButton;
    Button *resetButton;
    Button *quitButton;

    Button *easyButton;
    Button *normalButton;
    Button *hardButton;

    Button *ghost1EnableButton;
    Button *ghost2EnableButton;
    Button *ghost3EnableButton;
    Button *ghost4EnableButton;


    //timers
    QTimer *gameTimer;
    QTimer *powerTimer;
    QTimer *pacTimer;
    QTimer *ghost1Timer;
    QTimer *ghost2Timer;
    QTimer *ghost3Timer;
    QTimer *ghost4Timer;
    int gameTimerPeriod;

    //flags
    bool start_flag; //if the game start
    bool powerFlag; //if in power period
    bool ghost1Flag; //if ghost was enabled
    bool ghost2Flag;
    bool ghost3Flag;
    bool ghost4Flag;

    //texts
    QGraphicsTextItem *upText;
    QGraphicsTextItem *highScoreText;
    QGraphicsTextItem *currentPoint;
    QGraphicsTextItem *highScore;
    QGraphicsTextItem *overText;

    //ghost icon
    QGraphicsPixmapItem *g1;
    QGraphicsPixmapItem *g2;
    QGraphicsPixmapItem *g3;
    QGraphicsPixmapItem *g4;

    //ghost speed
    int ghost1Speed;
    int ghost2Speed;
    int ghost3Speed;
    int ghost4Speed;

    //score
    int currentPointNum;
    int highScoreNum;

    //counting left time
    int powerLeftTime;
    int ghost1LeftTime;
    int ghost2LeftTime;
    int ghost3LeftTime;
    int ghost4LeftTime;
};

#endif // GAME_H
