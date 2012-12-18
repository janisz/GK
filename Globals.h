#ifndef GLOBALS_H
#define GLOBALS_H

namespace Globals {

enum ShapeType
{
    Line        = 0,
    Circle      = 1,
    AACircle    = 2,
    Rectangle   = 3,
    Polygon     = 4,
    StrongLine  = 5,
    StrongCircle= 6
};

enum FilterType
{
    Scale  = 0,
    Matrix = 1,
    Rotate = 2,
    Strech = 3
};

}

#endif // GLOBALS_H
