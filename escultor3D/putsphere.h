#ifndef PUTSPHERE_H
#define PUTSPHERE_H

#include "figurageometrica.h"
#include "sculptor.h"

class putsphere : public figurageometrica {
private:
    int xcenter, ycenter, zcenter, radius;
    float r, g, b, a;

public:
    // Construtor: Nomes de parâmetros ÚNICOS e CLAROS
    putsphere(int _xc, int _yc, int _zc, int _raio,
              float _red, float _green, float _blue, float _alpha);

    // Implementação obrigatória do método virtual draw
    void draw(sculptor &t);
};

#endif // PUTSPHERE_H
