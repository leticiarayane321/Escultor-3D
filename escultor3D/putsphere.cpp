#include "putsphere.h"
#include "sculptor.h"

// Implementação do construtor: os nomes dos argumentos devem CORRESPONDER à declaração no .h
putsphere::putsphere(int _xc, int _yc, int _zc, int _raio, float _red, float _green, float _blue, float _alpha)
    // Inicialização dos atributos da classe com os valores passados:
    : xcenter(_xc), ycenter(_yc), zcenter(_zc), radius(_raio),
    r(_red), g(_green), b(_blue), a(_alpha)
{
    // O corpo do construtor pode ficar vazio, pois a inicialização já foi feita acima.
}

// Implementação do método draw
void putsphere::draw(sculptor &t) {
    // Define a cor do objeto Sculptor (t)
    t.setcolor(r, g, b, a);
    // Chama a função putSphere real do Sculptor
    t.putsphere(xcenter, ycenter, zcenter, radius);
}
