#include "putvoxel.h"
#include "sculptor.h"

// ATENÇÃO AQUI: tem que ser putvoxel::putvoxel (minúsculo)
putvoxel::putvoxel(int x, int y, int z, float r, float g, float b, float a) {
    this->x = x; this->y = y; this->z = z;
    this->r = r; this->g = g; this->b = b; this->a = a;
}

putvoxel::~putvoxel() {
}

void putvoxel::draw(sculptor &t) {
    t.setcolor(r, g, b, a);
    t.putvoxel(x, y, z);
}
