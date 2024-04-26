#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Point { float x, y; };

float Point_getX(struct Point *p) { return p->x; }
float Point_getY(struct Point *p) { return p->y; }

struct Point *Point_setXY(struct Point *p, float x, float y)
{
    p->x = x;
    p->y = y;
    return p;
}

struct Point *newPointXY(float x, float y)
{
    struct Point *p = calloc(1, sizeof(*p));
    return Point_setXY(p, x, y);
}

void Point_setX(struct Point *p, float x) { Point_setXY(p, x             , Point_getY(p)); }
void Point_setY(struct Point *p, float y) { Point_setXY(p, Point_getX(p) , y            ); }

void Point_printXY(struct Point *p)
{
    printf("(%f, %f)\n", Point_getX(p), Point_getY(p));
}

#ifdef UNIT_TEST

int main(int argc, char **argv)
{
    struct Point *p = newPointXY(3, 4);

    Point_printXY(p);  Point_printRT(p);
    Point_setX(p,  5);
    Point_setY(p, 12);
    Point_printXY(p);  Point_printRT(p);

    // When the above works, uncomment the following one line at a time and
    // implement whatever is necessary to make the program compile and run.

    // Point_setRT(p, 1, 45);
    // Point_printXY(p);  Point_printRT(p);
    // Point_setR(p, 2);  Point_setT(p, 225);
    // Point_printXY(p);  Point_printRT(p);

    return 0;
}

#endif // UNIT_TEST
