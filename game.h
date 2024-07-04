#ifndef GAME_H
#define GAME_H
#include "resources.h"
#include <vector>
#include <QObject>
#include <QPixmap>
#include <map>
#include "mybox.h"
#include "overlay.h"

class MyBox; // Game holds a vector of MyBox pointers, and MyBox holds a Game pointer

class Game : public QObject
{
    Q_OBJECT
private:
    std::vector<MyBox *> m_boxes;
    static gameboard::PlayerType m_playerTurn;
    gameboard::PlayerType m_startingPlayer;
    Overlay *m_overlay;
    static void loadImages();
    gameboard::PlayerType m_winner;
    bool isWinner();
    void initializeMembers();

public:
    Game(Overlay *overlay = nullptr);
    ~Game();
    void resetBoard(bool resetGame = false);
    static gameboard::PlayerType getPlayerTurn();
    static void changePlayerTurn();
    void changeStartingPlayer();
    void addBox(MyBox* box);
    MyBox *getBox(QPointF pos);
    static QPixmap* xImage;
    static QPixmap* oImage;
    static QPixmap* xoImage;

signals:
    void updateParentPlayerDisplay(QPixmap *img);
    void endRound(gameboard::PlayerType winner);
public slots:
    void handlePlayerSelectionMade();

};

#endif // GAME_H
