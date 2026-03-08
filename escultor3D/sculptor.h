#ifndef SCULPTOR_H
#define SCULPTOR_H

// 1. Definição da estrutura Voxel
struct voxel {
    float r, g, b; // Cor (RGB)
    float a;       // Transparência (Alpha)
    bool show;     // Status de inclusao
};

// 2. Declaração da Classe Sculptor
class sculptor {
private:
    voxel ***v; // Matriz 3D de Voxels
    int nx, ny, nz; // Dimensões
    float r, g, b, a; // Cores de desenho atuais
public:
    // Construtor e Destrutor
    sculptor(int nx, int ny, int nz);
    ~sculptor();

    // Mudei setColor para setcolor (minúsculo)
    void setcolor(float r, float g, float b, float a);

    // --- 1. Voxel ---
    void putvoxel(int x, int y, int z);
    void cutvoxel(int x, int y, int z);

    // --- 2. Box ---
    void putbox(int x0, int x1, int y0, int y1, int z0, int z1);
    void cutbox(int x0, int x1, int y0, int y1, int z0, int z1);

    // --- 3. Sphere ---
    void putsphere(int xcenter, int ycenter, int zcenter, int radius);
    void cutsphere(int xcenter, int ycenter, int zcenter, int radius);

    // --- 4. Ellipsoid ---
    void putellipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    void cutellipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

    // --- writeOFF ---
    void writeoff(const char* filename);
};

#endif // SCULPTOR_H
