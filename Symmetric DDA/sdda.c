#include <math.h>

void swap_float (float *_a, float *_b) {
    float t = *_a;
    *_a = *_b;
    *_b = t;
}

void sdda (float _x1, float _y1, float _x2, float _y2) {
 
    float adx, ady, dx, dy, step;
    int i;

    dx = (float)(_x2 - _x1);
    adx = dx < 0 ? -dx : dx;

    dy = (float)(_y2 - _y1);
    ady = dy < 0 ? -dy : dy;
  
    step = adx < ady ? ady : adx;
    if (step < 1.0f) {

        // do something with (int)_x1 and (int) _y1
        return;

    }

    step = getSddaStep(step);
 
	dx /= step;
	dy /= step;
 
	i = 1;
	while (i <= step) {
		
        _x1 += dx;
        _y1 += dy;

        // do something with (int)_x1 and (int) _y1

		++i;
	}
 
}

float getSddaStep (float _step) {

    int p2 = 2;
    while (_step >= p2) {
        p2 = p2 << 1;
    }
    return p2;

}
