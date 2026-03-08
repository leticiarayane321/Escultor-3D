#include "cutellipsoid.h"
#include "sculptor.h"

cutellipsoid::cutellipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    this->xcenter = xcenter;
    this->ycenter = ycenter;
    this->zcenter = zcenter;
    this->rx = rx;
    this->ry = ry;
    this->rz = rz;
}

cutellipsoid::~cutellipsoid() {
}

void cutellipsoid::draw(sculptor &t) {
    t.cutellipsoid(xcenter, ycenter, zcenter, rx, ry, rz);
}
