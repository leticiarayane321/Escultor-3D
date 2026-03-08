#ifndef PUTVOXEL_H
#define PUTVOXEL_H
#include "figurageometrica.h"
#include "sculptor.h"

class putvoxel : public figurageometrica {
    int x, y, z;
    float r, g, b, a;
public:
    putvoxel(int x, int y, int z, float r, float g, float b, float a);
    ~putvoxel();
    void draw(sculptor &t) override;
};
#endif
