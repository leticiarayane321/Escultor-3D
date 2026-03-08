#ifndef FIGURAGEOMETRICA_H
#define FIGURAGEOMETRICA_H

// FORWARD DECLARATION:
// Avisa que a classe "sculptor" existe (tudo minúsculo)
class sculptor;

class figurageometrica {
public:
    virtual ~figurageometrica(){}
    // Note o 'sculptor' minúsculo aqui
    virtual void draw(sculptor &t) = 0;
};

#endif // FIGURAGEOMETRICA_H
