#ifndef GAME_H
#define GAME_H
#include "resources.h"
#include <vector>
#include <QObject>
#include <QPixmap>
#include <map>
#include "mybox.h"

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
    enum class Lines {row1, row2, row3, col1, col2, col3, diag1, diag2};
    std::map<Lines, bool> m_lines;

public:
    Game();
    ~Game();
    static gameboard::PlayerType getPlayerTurn();
    static void changePlayerTurn();
    void addBox(MyBox* box);
    MyBox *getBox(QPointF pos);
    static QPixmap* xImage;
    static QPixmap* oImage;

signals:
    void updateParentPlayerDisplay(QPixmap *img);
    void endRound(gameboard::PlayerType winner);
public slots:
    void handlePlayerSelectionMade();

};

#endif // GAME_H
