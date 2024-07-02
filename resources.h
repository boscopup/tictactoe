#ifndef RESOURCES_H
#define RESOURCES_H

#include <QPixmap>

namespace gameboard {
    static const int box_width = 100;
    static const int line_width = 10;
    static const int board_width = 3*box_width + 2*line_width;
    static const int box1_start = 0;
    static const int box2_start = box1_start + box_width + line_width;
    static const int box3_start = box2_start + box_width + line_width;
    static const int box1_end = box1_start + box_width;
    static const int box2_end = box2_start + box_width;
    static const int box3_end = box2_start + box_width;
    enum PlayerType {x, o};
}
#endif // RESOURCES_H
