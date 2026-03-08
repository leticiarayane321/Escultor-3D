#ifndef CUTSPHERE_H
#define CUTSPHERE_H

#include "figurageometrica.h"
#include "sculptor.h"

class cutsphere : public figurageometrica {
private:
    // Atributos para armazenar o centro e o raio da esfera
    int xc, yc, zc, raio;

public:
    // Construtor: recebe a posição do centro e o raio
    cutsphere(int _xc, int _yc, int _zc, int _raio);

    // Implementação obrigatória da função virtual 'draw'
    // Esta função será chamada para remover a esfera da matriz
    void draw(sculptor &t);
};

#endif // CUTSPHERE_H
