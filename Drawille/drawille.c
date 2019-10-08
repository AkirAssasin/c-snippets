#include <stdio.h> /* printf */

/* printf("\xE2\x98\xA0"); unicode */
/* key discovery: braille in unicode is arranged based on the binary form of 
 * last two hexadecimal digits...?
*/

// 0 3
// 1 4
// 2 5
// 6 7

void getBraille (int* _bools, char* _string) {

    // first six bools

    char delta = 0;
    char scale = 1;

    for (int i = 0; i < 6; ++i) {

        scale = (char)(i ? (scale << 1) : 1);
        if (_bools[i]) delta += scale;

    }

    _string[2] = delta - 128;

    // last two bools

    if (_bools[6] == _bools[7]) {
        _string[1] = _bools[6] ? '\xA3' : '\xA0';
    } else {
        _string[1] = _bools[6] ? '\xA0' : '\xA2';
    }

}

int dx[8] = { 0, 0, 0, 1, 1, 1, 0, 1 };
int dy[8] = { 0, 1, 2, 0, 1, 2, 3, 3 };

#define BRAILLE_WIDTH_FACTOR 2
#define BRAILLE_HEIGHT_FACTOR 4

void printBraille (int _width, int _height, int _array[_width][_height]) {

    // declare arrays (temp implementation)

    int bools[8];
    char braille[4] = {'\xE2',0,0,0};

    // get braille dimensions

    int brailleWidth = _width / BRAILLE_WIDTH_FACTOR;
    if (_width % BRAILLE_WIDTH_FACTOR) brailleWidth++;

    int brailleHeight = _height / BRAILLE_HEIGHT_FACTOR;
    if (_height % BRAILLE_HEIGHT_FACTOR) brailleHeight++;

    // iterate through braille dimensions

    for (int y = 0; y < brailleHeight; ++y) {
        for (int x = 0; x < brailleWidth; ++x) {

            // fill in bools array

            for (int i = 0; i < 8; ++i) {

                int tx = x * BRAILLE_WIDTH_FACTOR + dx[i];
                int ty = y * BRAILLE_HEIGHT_FACTOR + dy[i];

                if (tx >= _width || ty >= _height) {
                    bools[i] = 0;
                    continue;
                }

                bools[i] = _array[tx][ty];

            }

            // print braille

            getBraille(bools,braille);
            printf("%s",braille);

        }

        printf("\n");

    }

}

int main (void) {

    int height = 50;
    int width = 50;

    float sqradius = 25.0f * 25.0f;

    int array[width][height];

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            float dx = x - width / 2.0f;
            float dy = y - height / 2.0f;

            array[x][y] = (dx * dx) + (dy * dy) <= sqradius;
        }
    }
    
    printBraille(width,height,array);

    return 0;

}
