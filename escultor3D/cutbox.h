#ifndef CUTBOX_H
#define CUTBOX_H

#include "figurageometrica.h"


class cutbox : public figurageometrica {
    // Estas variáveis PRECISAM estar aqui para o .cpp reconhecer
    int x0, x1, y0, y1, z0, z1;
public:
    cutbox(int x0, int x1, int y0, int y1, int z0, int z1);
    virtual ~cutbox(); // O Destrutor precisa ser declarado aqui
    void draw(sculptor &t) override;
};

#endif // CUTBOX_H
