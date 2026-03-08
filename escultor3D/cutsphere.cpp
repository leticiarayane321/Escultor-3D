#include "cutsphere.h"
#include "sculptor.h"

// Implementação do Construtor
cutsphere::cutsphere(int _xc, int _yc, int _zc, int _raio)
    : xc(_xc), yc(_yc), zc(_zc), raio(_raio)
{}

// Implementação do Método Draw
void cutsphere::draw(sculptor &t) {
    // Chama o método da classe Sculptor para remover a esfera
    t.cutsphere(xc, yc, zc, raio);
}
