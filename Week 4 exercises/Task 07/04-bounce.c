#include "window.h"
#include "PointXY.c"

#define DRAWING 0 // 1 enable drawing, 0 disable drawing

int main(int argc, char **argv) {
    size(400, 300);
    title("bounce");

    // initial position
    struct Point *p = newPointXY(width / 2.0, height / 2);

    // initial velocity
    float dx = 3.0, dy = 4.0;

    unsigned long start = millisecondClock();

    // animation loop
    for (int i = 0; i < 33000000; ++i) {
        // draw the ball
        if (DRAWING) {
            clear();
            fillRectangle(Point_getX(p) - 2, Point_getY(p) - 2,
                          Point_getX(p) + 2, Point_getY(p) + 2);
            // update display and wait a short time
            delay(10);
        }

        // move the ball to its next position according to its velocity
        Point_setX(p, Point_getX(p) + dx);
        // reverse X component of velocity if the ball hits the right or left window edge
        if (Point_getX(p) >= width || Point_getX(p) <= 0) dx = -dx;
        Point_setY(p, Point_getY(p) + dy);
        // reverse Y component of velocity if the ball hits the right or left window edge
        if (Point_getY(p) >= height || Point_getY(p) <= 0) dy = -dy;
    }
    unsigned long finish = millisecondClock();
    printf("%lu\n", finish - start);
    return 0;
}
