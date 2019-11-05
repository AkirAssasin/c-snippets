/*

If you're reading this:
this was meant to be an answer for Practice 3,
where you code a program that identifies the type of a triangle.
However, I decided to program a triangle display
for god knows what reason,
and after that was sort of complete
I just lost all motivation to do the actual practice.
So yeah lmao

*/

#include <stdio.h> /* printf */
#include <stdlib.h> /* rand */
#include <time.h> /* time */

#include "triangle.h" /* point, tri and relevant functions */
#include "randoma.h" /* shuffle */

#define CONSOLE_WIDTH 100
#define CONSOLE_HEIGHT 50
#define CONSOLE_MULT (CONSOLE_WIDTH * CONSOLE_HEIGHT) /* height times width */

#define FONT_ASPECT 2.0f /* height over width */

int triangleID[CONSOLE_MULT];

#define TRI_COUNT 16 /* must be at least 2; powers of 2 recommended */
tri triangles[TRI_COUNT];
int colorID[TRI_COUNT];

void fillTriangleArray (float _width, float _height) {

    int newTriangleID = 2;
    int lastSplitTarget = 1;
    int currentSplitTarget = 0;
    int splitSide = 2;
    int i;

    /* generate base triangles */

    triangles[0] = defineTriangleAs(0,0,0,_height,_width,_height);
    triangles[1] = defineTriangleAs(0,0,_width,0,_width,_height);

    /* split triangles randomly */

    srand((unsigned int)time(0));
    while (newTriangleID < TRI_COUNT) {

        triangles[newTriangleID++] = splitTriangle(
            &triangles[currentSplitTarget++],
            splitSide,
            0.25f + 0.5f * ((float)rand() / RAND_MAX)
        );

        splitSide = (splitSide + 1 + (rand() % 2)) % 3;

        if (currentSplitTarget > lastSplitTarget) {
            currentSplitTarget = 0;
            lastSplitTarget = newTriangleID - 1;
        }

    }

    /* give triangles random colors */

    for (i = 0; i < TRI_COUNT; i++) colorID[i] = 8 + i;
    shuffle(colorID,TRI_COUNT);

}

void getColorPair (int _id, int* _foreground, int* _background) {

    _id %= 32;

    if (_id <= 7) {
        *_foreground = 8;
        *_background = 100 + _id;
        return;
    }

    if (_id <= 15) {
        *_foreground = 30 + _id - 8;
        *_background = 100 + _id - 8;
        return;
    }

    if (_id <= 23) {
        *_foreground = 90 + _id - 16;
        *_background = 40 + _id - 16;
        return;
    }

    *_foreground = 8;
    *_background = 40 + _id - 24;

}

void computeTriangleID () {

    float fx, fy;
    int x, y, i, l, li, le, fc, bc;
    /* char color[7]; */

    /* find the triangle for all points */

    l = 0;

    for (y = 0; y < CONSOLE_HEIGHT; y++) {
        for (x = 0; x < CONSOLE_WIDTH; x++) {
        
            fx = 0.5f + (x / FONT_ASPECT);
            fy = 0.5f + (CONSOLE_HEIGHT - y);

            le = 0;

            for (i = 0; i < TRI_COUNT; i++) {

                li = (i + l) % TRI_COUNT;
                if (isPointInTriangle(triangles[li],fx,fy)) {

                    if (l != li) {
                        l = li;
                        getColorPair(colorID[l],&fc,&bc);
                    }

                    le = 1;
                    
                    triangleID[x + y * CONSOLE_WIDTH] = li;
                    break;

                }

            }

            if (le) {
                printf("\033[0;%d;%dm%c",bc,fc,65 + l);
            } else {
                printf("%%");
            }

        }

        printf("\033[0m\n");
    
    }

    printf("\n");

}

int main (void) {

    int run = 1;
    int scanfResult;

    printf("\033[8;%d;%dt",CONSOLE_HEIGHT + 2,CONSOLE_WIDTH);

    /* bruh I said must be at least 2 */
    
    if (TRI_COUNT < 2) return 1;

    while (run) {

        fillTriangleArray((CONSOLE_WIDTH + 1) / FONT_ASPECT, CONSOLE_HEIGHT + 1);    
        computeTriangleID();

        printf("Restart? ");
        scanfResult = scanf("%d",&run);
        if (!scanfResult) run = 0;

    }

    return 0;

}
