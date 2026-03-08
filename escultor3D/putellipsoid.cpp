#include "putellipsoid.h"
#include "sculptor.h"

putellipsoid::putellipsoid(int _xc, int _yc, int _zc, int _rx, int _ry, int _rz, float _r, float _g, float _b, float _a)
    : xc(_xc), yc(_yc), zc(_zc), rx(_rx), ry(_ry), rz(_rz), r(_r), g(_g), b(_b), a(_a) {}

void putellipsoid::draw(sculptor &t) {
    t.setcolor(r, g, b, a);
    t.putellipsoid(xc, yc, zc, rx, ry, rz);
}
