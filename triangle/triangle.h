typedef struct point {
    
    float x;
    float y;

} point;

point lerpPoint (point _a, point _b, float _t) {

    point p;

    p.x = (1.0f - _t) * _a.x + _t * _b.x;
    p.y = (1.0f - _t) * _a.y + _t * _b.y;

    return p;

}

typedef struct tri {

    point a;
    point b;
    point c;

} tri;

tri defineTriangleAs (float _a1, float _a2, float _b1, float _b2, float _c1, float _c2) {

    tri result;
    
    result.a.x = _a1;
    result.a.y = _a2;

    result.b.x = _b1;
    result.b.y = _b2;

    result.c.x = _c1;
    result.c.y = _c2;
    
    return result;

}

tri splitTriangle (tri* _tri, int _side, float _t) {

    tri resultTri = *_tri;
    point r;

    if (_t < 0.0f) {
        _t = 0.0f;
    } else if (_t > 1.0f) {
        _t = 1.0f;
    }

    switch (_side) {

        case 0: /* split a and b */

            r = lerpPoint(resultTri.a,resultTri.b,_t);
            resultTri.b = r;
            (*_tri).a = r;

            break;

        case 1: /* split b and c */

            r = lerpPoint(resultTri.b,resultTri.c,_t);
            resultTri.c = r;
            (*_tri).b = r;

            break;

        default: /* split c and a */

            r = lerpPoint(resultTri.c,resultTri.a,_t);
            resultTri.a = r;
            (*_tri).c = r;

            break;

    }

    return resultTri;

}

int isPointInTriangle (tri _tri, float _x, float _y) {

    /* https://stackoverflow.com/a/9755252 */
    /* calculate vector (A -> P) */

    float apX = _x - _tri.a.x;
    float apY = _y - _tri.a.y;

    /* dot product of normal of (A -> B) with (A -> P) */

    int pointBehindAB = (_tri.b.x - _tri.a.x) * apY - (_tri.b.y - _tri.a.y) * apX > 0;

    /* dot product of normal of (A -> C) with (A -> P) */

    int pointBehindAC = (_tri.c.x - _tri.a.x) * apY - (_tri.c.y - _tri.a.y) * apX > 0;
    int pointInFrontOfBC;

    /* if both same sign, then point isn't within the cone of A to B and C */

    if(pointBehindAB == pointBehindAC) return 0;

    /* dot product of normal of (B -> C) with (B -> P) */

    pointInFrontOfBC = (_tri.c.x - _tri.b.x) * (_y - _tri.b.y)
     - (_tri.c.y - _tri.b.y) * (_x - _tri.b.x) > 0;

    return pointBehindAB == pointInFrontOfBC;

}
