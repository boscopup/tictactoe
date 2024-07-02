#ifndef GAME_H
#define GAME_H
#include "resources.h"
#include <vector>
#include <QObject>
#include "mybox.h"
#include <QPixmap>

class Game : public QObject
{
    Q_OBJECT
private:
    std::vector<MyBox *> m_boxes;
    static gameboard::PlayerType m_playerTurn;
    static void loadImages();
public:
    Game();
    static gameboard::PlayerType getPlayerTurn();
    static void changePlayerTurn();
    void addBox(MyBox* box);
    MyBox *getBox(QPointF pos);
    static QPixmap* xImage;
    static QPixmap* oImage;
public slots:
    static void handlePlayerSelectionMade();

};

#endif // GAME_H
