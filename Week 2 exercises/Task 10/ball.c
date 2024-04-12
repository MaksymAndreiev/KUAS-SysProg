#include "window.h"

#define SIZE 4 // half the width/height of the ball

int main(int argc, char **argv) {
    size(400, 300);
    title("ball");
    // initial position
    int x = 0;
    int y = height / 2;
    // initial velocity
    int dx = 3;
    int dy = 3;
    // animation loop
    for (;;) {
        // draw the ball
        clear();
        fillRectangle(x - SIZE, y - SIZE, x + SIZE, y + SIZE);
        // update the display and wait a short time
        delay(10);
        // move the ball according to its velocity
        x += dx;
        // reverse X component of velocity if the ball
        // hits the right or left window edge
        if (x >= width || x <= 0) dx = -dx;
        // move the ball according to its velocity
        y += dy;
        // reverse Y component of velocity if the ball
        // hits the top or bottom window edge
        if (y >= height || y <= 0) dy = -dy;
    }
    return 0;
}