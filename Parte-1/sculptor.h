#ifndef SCULPTOR_H
#define SCULPTOR_H

struct Voxel {
    float r, g, b; // Cores
    float a;       // Transparência
    bool show;     // Incluído ou não
};

class Sculptor {
private:
  Voxel ***v; // 3D matrix
  int nx,ny,nz; // Dimensions
  float r,g,b,a; // Current drawing color

public:
    // Construtor e Destrutor [cite: 137, 138]
    Sculptor(int _nx, int _ny, int _nz);
    ~Sculptor();

    // Métodos de Controle e Desenho
    void setColor(float r, float g, float b, float a);
    void putVoxel(int x, int y, int z);
    void cutVoxel(int x, int y, int z);
    void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
    void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
    void putSphere(int xcenter, int ycenter, int zcenter, int radius);
    void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
    void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

    // Método de Gravação
    void writeOFF(const char* filename); // Grava a escultura no formato OFF [cite: 147, 151]
};

#endif // SCULPTOR_H
