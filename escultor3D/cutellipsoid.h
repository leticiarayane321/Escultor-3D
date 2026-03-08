#ifndef CUTELLIPSOID_H
#define CUTELLIPSOID_H

#include "figurageometrica.h"

class cutellipsoid : public figurageometrica {
    // Variáveis que estavam faltando:
    int xcenter, ycenter, zcenter, rx, ry, rz;
public:
    cutellipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    virtual ~cutellipsoid(); // Declaração do destrutor
    void draw(sculptor &t) override;
};

#endif // CUTELLIPSOID_H
