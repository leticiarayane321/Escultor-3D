#include "sculptor.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

// Construtor e Destrutor (Gestão de Memória Dinâmica)

Sculptor::Sculptor(int _nx, int _ny, int _nz) {
    nx = _nx;
    ny = _ny;
    nz = _nz;

    // 1. Aloca a primeira dimensão (nx)
    v = new Voxel**[nx];

    // 2. Aloca a segunda (ny) e terceira (nz) dimensões e inicializa
    for (int i = 0; i < nx; i++) {
        v[i] = new Voxel*[ny];
        for (int j = 0; j < ny; j++) {
            v[i][j] = new Voxel[nz];
            for (int k = 0; k < nz; k++) {
                v[i][j][k].show = false; // Todos os voxels começam apagados
            }
        }
    }
}

Sculptor::~Sculptor() {
    // Desaloca na ordem inversa da alocação
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            delete[] v[i][j]; // Libera a 3ª dimensão
        }
        delete[] v[i]; // Libera a 2ª dimensão
    }
    delete[] v; // Libera a 1ª dimensão
}


// Métodos de Controle (Cor) e Voxel Individual

void Sculptor::setColor(float r, float g, float b, float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a; // Define a cor e transparência atuais
}

void Sculptor::putVoxel(int x, int y, int z) {
    // Verifica limites
    if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
        v[x][y][z].show = true; // Ativa o voxel
        v[x][y][z].r = r;
        v[x][y][z].g = g;
        v[x][y][z].b = b;
        v[x][y][z].a = a; // Aplica a cor atual
    }
}

void Sculptor::cutVoxel(int x, int y, int z) {
    // Verifica limites
    if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
        v[x][y][z].show = false; // Desativa o voxel
    }
}

//  Métodos de Formas Primitivas (Box)

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {
    // Garante que os limites são válidos (ex: x0 <= x1)
    int start_x = (x0 < x1) ? x0 : x1;
    int end_x   = (x0 < x1) ? x1 : x0;

    int start_y = (y0 < y1) ? y0 : y1;
    int end_y   = (y0 < y1) ? y1 : y0;

    int start_z = (z0 < z1) ? z0 : z1;
    int end_z   = (z0 < z1) ? z1 : z0;

    // Itera sobre o bloco (box)
    for (int i = start_x; i <= end_x; i++) {
        for (int j = start_y; j <= end_y; j++) {
            for (int k = start_z; k <= end_z; k++) {
                putVoxel(i, j, k);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
    // Garante que os limites são válidos (ex: x0 <= x1)
    int start_x = (x0 < x1) ? x0 : x1;
    int end_x   = (x0 < x1) ? x1 : x0;

    int start_y = (y0 < y1) ? y0 : y1;
    int end_y   = (y0 < y1) ? y1 : y0;

    int start_z = (z0 < z1) ? z0 : z1;
    int end_z   = (z0 < z1) ? z1 : z0;

    // Itera sobre o bloco (box)
    for (int i = start_x; i <= end_x; i++) {
        for (int j = start_y; j <= end_y; j++) {
            for (int k = start_z; k <= end_z; k++) {
                cutVoxel(i, j, k);
            }
        }
    }
}


//  Métodos de Formas Geométricas (Esfera e Elipsóide)

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius) {
    // Otimiza o loop para iterar apenas sobre o cubo que contém a esfera
    for (int i = xcenter - radius; i <= xcenter + radius; i++) {
        for (int j = ycenter - radius; j <= ycenter + radius; j++) {
            for (int k = zcenter - radius; k <= zcenter + radius; k++) {
                // Equação da Esfera: (x - xc)^2 + (y - yc)^2 + (z - zc)^2 <= r^2
                double dist = static_cast<double>(i - xcenter) * (i - xcenter) / (radius * radius) +
                              static_cast<double>(j - ycenter) * (j - ycenter) / (radius * radius) +
                              static_cast<double>(k - zcenter) * (k - zcenter) / (radius * radius);

                if (dist <= 1.0) {
                    putVoxel(i, j, k);
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius) {
    // Otimiza o loop para iterar apenas sobre o cubo que contém a esfera
    for (int i = xcenter - radius; i <= xcenter + radius; i++) {
        for (int j = ycenter - radius; j <= ycenter + radius; j++) {
            for (int k = zcenter - radius; k <= zcenter + radius; k++) {
                // Equação da Esfera
                double dist = static_cast<double>(i - xcenter) * (i - xcenter) / (radius * radius) +
                              static_cast<double>(j - ycenter) * (j - ycenter) / (radius * radius) +
                              static_cast<double>(k - zcenter) * (k - zcenter) / (radius * radius);

                if (dist <= 1.0) {
                    cutVoxel(i, j, k);
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    // Otimiza o loop para iterar apenas sobre o cubo que contém o elipsóide
    for (int i = xcenter - rx; i <= xcenter + rx; i++) {
        for (int j = ycenter - ry; j <= ycenter + ry; j++) {
            for (int k = zcenter - rz; k <= zcenter + rz; k++) {
                // Equação do Elipsóide: (x-xc)^2/rx^2 + (y-yc)^2/ry^2 + (z-zc)^2/rz^2 <= 1
                double dist = static_cast<double>(i - xcenter) * (i - xcenter) / (rx * rx) +
                              static_cast<double>(j - ycenter) * (j - ycenter) / (ry * ry) +
                              static_cast<double>(k - zcenter) * (k - zcenter) / (rz * rz);

                if (dist <= 1.0) {
                    putVoxel(i, j, k);
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    // Otimiza o loop para iterar apenas sobre o cubo que contém o elipsóide
    for (int i = xcenter - rx; i <= xcenter + rx; i++) {
        for (int j = ycenter - ry; j <= ycenter + ry; j++) {
            for (int k = zcenter - rz; k <= zcenter + rz; k++) {
                // Equação do Elipsóide
                double dist = static_cast<double>(i - xcenter) * (i - xcenter) / (rx * rx) +
                              static_cast<double>(j - ycenter) * (j - ycenter) / (ry * ry) +
                              static_cast<double>(k - zcenter) * (k - zcenter) / (rz * rz);

                if (dist <= 1.0) {
                    cutVoxel(i, j, k);
                }
            }
        }
    }
}

// Método de Gravação (writeOFF)

void Sculptor::writeOFF(const char* filename) {
    std::ofstream fout;
    fout.open(filename);

    if (!fout.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo " << filename << std::endl;
        return;
    }

    //Pré-cálculo: Conta Nvoxels
    int Nvoxels = 0;
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].show) {
                    Nvoxels++;
                }
            }
        }
    }

    //Cabeçalho OFF: NVertices, NFaces, NArestas
    fout << "OFF" << std::endl;
    fout << 8 * Nvoxels << " " << 6 * Nvoxels << " " << 0 << std::endl;

    //Vértices
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].show) {
                    // Centro do cubo (x,y,z) está no centro do voxel (i, j, k)
                    float x = i;
                    float y = j;
                    float z = k;

                    // As 8 coordenadas do cubo de lado 1, centrado em (x,y,z)
                    // Os vértices são escritos na ordem P0, P1, P2, P3, P4, P5, P6, P7

                    // Coordenadas:
                    // P0 (x-0.5, y+0.5, z-0.5)
                    fout << x - 0.5 << " " << y + 0.5 << " " << z - 0.5 << std::endl;
                    // P1 (x-0.5, y-0.5, z-0.5)
                    fout << x - 0.5 << " " << y - 0.5 << " " << z - 0.5 << std::endl;
                    // P2 (x+0.5, y-0.5, z-0.5)
                    fout << x + 0.5 << " " << y - 0.5 << " " << z - 0.5 << std::endl;
                    // P3 (x+0.5, y+0.5, z-0.5)
                    fout << x + 0.5 << " " << y + 0.5 << " " << z - 0.5 << std::endl;
                    // P4 (x-0.5, y+0.5, z+0.5)
                    fout << x - 0.5 << " " << y + 0.5 << " " << z + 0.5 << std::endl;
                    // P5 (x-0.5, y-0.5, z+0.5)
                    fout << x - 0.5 << " " << y - 0.5 << " " << z + 0.5 << std::endl;
                    // P6 (x+0.5, y-0.5, z+0.5)
                    fout << x + 0.5 << " " << y - 0.5 << " " << z + 0.5 << std::endl;
                    // P7 (x+0.5, y+0.5, z+0.5)
                    fout << x + 0.5 << " " << y + 0.5 << " " << z + 0.5 << std::endl;
                }
            }
        }
    }

    //Faces
    int k_offset = 0; // Índice inicial do vértice para o cubo atual
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].show) {
                    Voxel current_v = v[i][j][k];

                    // Os 4 valores RGBA da cor
                    float r = current_v.r, g = current_v.g, b = current_v.b, a = current_v.a;

                    // As 6 faces do cubo (4 vértices cada), usando os índices relativos ao k_offset

                    // Face 1: Traseira (P0 P3 P2 P1)
                    fout << 4 << " " << k_offset + 0 << " " << k_offset + 3 << " " << k_offset + 2 << " " << k_offset + 1 << " "
                         << r << " " << g << " " << b << " " << a << std::endl;
                    // Face 2: Frontal (P4 P7 P6 P5)
                    fout << 4 << " " << k_offset + 4 << " " << k_offset + 7 << " " << k_offset + 6 << " " << k_offset + 5 << " "
                         << r << " " << g << " " << b << " " << a << std::endl;
                    // Face 3: Cima (P0 P4 P7 P3)
                    fout << 4 << " " << k_offset + 0 << " " << k_offset + 4 << " " << k_offset + 7 << " " << k_offset + 3 << " "
                         << r << " " << g << " " << b << " " << a << std::endl;
                    // Face 4: Baixo (P1 P2 P6 P5)
                    fout << 4 << " " << k_offset + 1 << " " << k_offset + 2 << " " << k_offset + 6 << " " << k_offset + 5 << " "
                         << r << " " << g << " " << b << " " << a << std::endl;
                    // Face 5: Direita (P3 P7 P6 P2)
                    fout << 4 << " " << k_offset + 3 << " " << k_offset + 7 << " " << k_offset + 6 << " " << k_offset + 2 << " "
                         << r << " " << g << " " << b << " " << a << std::endl;
                    // Face 6: Esquerda (P0 P1 P5 P4)
                    fout << 4 << " " << k_offset + 0 << " " << k_offset + 1 << " " << k_offset + 5 << " " << k_offset + 4 << " "
                         << r << " " << g << " " << b << " " << a << std::endl;

                    k_offset += 8; // Avança 8 posições para os próximos 8 vértices
                }
            }
        }
    }

    fout.close();
}
