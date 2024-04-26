#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEGREES * (180.0 / M_PI)
#define RADIANS * (M_PI / 180.0)

struct Point { float r, t; };

float Point_getR(struct Point *p) { return p->r; }
float Point_getT(struct Point *p) { return p->t DEGREES; }

struct Point *Point_setRT(struct Point *p, float r, float t)
{
    p->r = r;
    p->t = t RADIANS;
    return p;
}

void Point_setR(struct Point *p, float r) { Point_setRT(p, r             , Point_getT(p)); }
void Point_setT(struct Point *p, float t) { Point_setRT(p, Point_getR(p) , t            ); }

struct Point *newPointRT(float r, float t)
{
    struct Point *p = calloc(1, sizeof(*p));
    return Point_setRT(p, r, t);
}

void Point_printRT(struct Point *p)
{
    printf("(%f, %f)\n", Point_getR(p), Point_getT(p));
}

#ifdef UNIT_TEST

int main(int argc, char **argv)
{
    struct Point *p = newPointXY(3, 4);

    Point_printXY(p);  Point_printRT(p);
    Point_setX(p,  5);
    Point_setY(p, 12);
    Point_printXY(p);  Point_printRT(p);

    Point_setRT(p, 1, 45);
    Point_printXY(p);  Point_printRT(p);
    Point_setR(p, 2);  Point_setT(p, 225);
    Point_printXY(p);  Point_printRT(p);

    return 0;
}

#endif // UNIT_TEST
