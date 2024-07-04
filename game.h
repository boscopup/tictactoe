#ifndef GAME_H
#define GAME_H
#include "resources.h"
#include <vector>
#include <QObject>
#include <QPixmap>
#include <map>
#include "box.h"
#include "overlay.h"

class Box; // Game holds a vector of Box pointers, and Box holds a Game pointer

class Game : public QObject
{
    Q_OBJECT
private:
    std::vector<Box *> m_boxes;
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
    void addBox(Box* box);
    Box *getBox(QPointF pos);
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
