#include "cutvoxel.h"
#include "sculptor.h"

// O ERRO ESTÁ AQUI: Tem que ser cutvoxel::cutvoxel (tudo minúsculo)
cutvoxel::cutvoxel(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

cutvoxel::~cutvoxel() {
}

void cutvoxel::draw(sculptor &t) {
    t.cutvoxel(x, y, z);
}
