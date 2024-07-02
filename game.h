#ifndef GAME_H
#define GAME_H
#include "resources.h"
#include <vector>
#include <QObject>
#include <QPixmap>

class MyBox; // Game holds a vector of MyBox pointers, and MyBox holds a Game pointer

class Game : public QObject
{
    Q_OBJECT
private:
    std::vector<MyBox *> m_boxes;
    static gameboard::PlayerType m_playerTurn;
    static void loadImages();
    gameboard::PlayerType m_winner;
    bool isWinner();

public:
    Game();
    static gameboard::PlayerType getPlayerTurn();
    static void changePlayerTurn();
    void addBox(MyBox* box);
    MyBox *getBox(QPointF pos);
    static QPixmap* xImage;
    static QPixmap* oImage;

signals:
    void updateParentPlayerDisplay(QPixmap *img);
public slots:
    void handlePlayerSelectionMade();

};

#endif // GAME_H
