#include "putbox.h"
#include "sculptor.h"

putbox::putbox(int _x0, int _x1, int _y0, int _y1, int _z0, int _z1, float _r, float _g, float _b, float _a)
    : x0(_x0), x1(_x1), y0(_y0), y1(_y1), z0(_z0), z1(_z1), r(_r), g(_g), b(_b), a(_a) {}

void putbox::draw(sculptor &t) {
    t.setcolor(r, g, b, a);
    t.putbox(x0, x1, y0, y1, z0, z1);
}
