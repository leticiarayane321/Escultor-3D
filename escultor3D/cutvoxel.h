#ifndef CUTVOXEL_H
#define CUTVOXEL_H
#include "figurageometrica.h"
#include "sculptor.h"

// Classe com nome minúsculo
class cutvoxel : public figurageometrica {
    int x, y, z;
public:
    cutvoxel(int x, int y, int z);
    ~cutvoxel();
    void draw(sculptor &t) override;
};
#endif
