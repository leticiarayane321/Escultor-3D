#include "sculptor.h"
#include <iostream>

int main() {
    // Dimensoes do espaco
    Sculptor s(50, 50, 80);

    // Corpo do Foguete (Azul)
    s.setColor(0.0, 0.0, 1.0, 1.0);
    s.putBox(20, 30, 20, 30, 10, 60);

    // Porta (Corte)
    s.cutBox(23, 27, 20, 22, 15, 25);

    // Bico (Vermelho)
    s.setColor(1.0, 0.0, 0.0, 1.0);
    s.putSphere(25, 25, 60, 7);

    // Janela (Corte redondo)
    s.cutSphere(25, 25, 50, 4);

    // Pes / Aletas (Verde)
    s.setColor(0.0, 1.0, 0.0, 1.0);
    s.putEllipsoid(15, 25, 10, 3, 3, 8); // Esquerda
    s.putEllipsoid(35, 25, 10, 3, 3, 8); // Direita
    s.putEllipsoid(25, 15, 10, 3, 3, 8); // Frente
    s.putEllipsoid(25, 35, 10, 3, 3, 8); // Tras

    // Motor (Corte na base)
    s.cutEllipsoid(25, 25, 10, 4, 4, 2);

    // Fogo (Amarelo - Voxels individuais)
    s.setColor(1.0, 1.0, 0.0, 1.0);
    for(int k = 0; k < 8; k++) {
        s.putVoxel(25, 25, k);
        s.putVoxel(24, 25, k);
        s.putVoxel(26, 25, k);
        s.putVoxel(25, 24, k);
        s.putVoxel(25, 26, k);
    }

    // Detalhe no bico (Desgaste - cutVoxel)
    s.cutVoxel(25, 25, 66);
    s.cutVoxel(25, 25, 67);

    // Salvar arquivo
    s.writeOFF("foguete.off");

    std::cout << "Arquivo foguete.off criado!" << std::endl;

    return 0;
}
