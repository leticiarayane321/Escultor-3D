#include "sculptor.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

sculptor::sculptor(int _nx, int _ny, int _nz) {
    nx = _nx; ny = _ny; nz = _nz;
    r = g = b = 0.0; a = 1.0;
    if (nx <= 0 || ny <= 0 || nz <= 0) { v = nullptr; return; }
    v = new voxel**[nx];
    for (int i = 0; i < nx; i++) {
        v[i] = new voxel*[ny];
        for (int j = 0; j < ny; j++) {
            v[i][j] = new voxel[nz];
            for (int k = 0; k < nz; k++) {
                v[i][j][k].show = false;
            }
        }
    }
}

sculptor::~sculptor() {
    if (!v) return;
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) delete[] v[i][j];
        delete[] v[i];
    }
    delete[] v;
}

void sculptor::setcolor(float _r, float _g, float _b, float _a) {
    r = _r; g = _g; b = _b; a = _a;
}

void sculptor::putvoxel(int x, int y, int z) {
    if (x>=0 && x<nx && y>=0 && y<ny && z>=0 && z<nz) {
        v[x][y][z].show = true;
        v[x][y][z].r = r; v[x][y][z].g = g; v[x][y][z].b = b; v[x][y][z].a = a;
    }
}

void sculptor::cutvoxel(int x, int y, int z) {
    if (x>=0 && x<nx && y>=0 && y<ny && z>=0 && z<nz) v[x][y][z].show = false;
}

void sculptor::putbox(int x0, int x1, int y0, int y1, int z0, int z1) {
    for(int i=min(x0,x1); i<=max(x0,x1); i++)
        for(int j=min(y0,y1); j<=max(y0,y1); j++)
            for(int k=min(z0,z1); k<=max(z0,z1); k++) putvoxel(i,j,k);
}

void sculptor::cutbox(int x0, int x1, int y0, int y1, int z0, int z1) {
    for(int i=min(x0,x1); i<=max(x0,x1); i++)
        for(int j=min(y0,y1); j<=max(y0,y1); j++)
            for(int k=min(z0,z1); k<=max(z0,z1); k++) cutvoxel(i,j,k);
}

void sculptor::putsphere(int xc, int yc, int zc, int radius) {
    double r2 = radius*radius;
    for(int i=0; i<nx; i++)
        for(int j=0; j<ny; j++)
            for(int k=0; k<nz; k++)
                if (pow(i-xc,2)+pow(j-yc,2)+pow(k-zc,2) <= r2) putvoxel(i,j,k);
}

void sculptor::cutsphere(int xc, int yc, int zc, int radius) {
    double r2 = radius*radius;
    for(int i=0; i<nx; i++)
        for(int j=0; j<ny; j++)
            for(int k=0; k<nz; k++)
                if (pow(i-xc,2)+pow(j-yc,2)+pow(k-zc,2) <= r2) cutvoxel(i,j,k);
}

void sculptor::putellipsoid(int xc, int yc, int zc, int rx, int ry, int rz) {
    if(!rx||!ry||!rz) return;
    for(int i=0; i<nx; i++)
        for(int j=0; j<ny; j++)
            for(int k=0; k<nz; k++)
                if (pow(i-xc,2)/pow(rx,2) + pow(j-yc,2)/pow(ry,2) + pow(k-zc,2)/pow(rz,2) <= 1) putvoxel(i,j,k);
}

void sculptor::cutellipsoid(int xc, int yc, int zc, int rx, int ry, int rz) {
    if(!rx||!ry||!rz) return;
    for(int i=0; i<nx; i++)
        for(int j=0; j<ny; j++)
            for(int k=0; k<nz; k++)
                if (pow(i-xc,2)/pow(rx,2) + pow(j-yc,2)/pow(ry,2) + pow(k-zc,2)/pow(rz,2) <= 1) cutvoxel(i,j,k);
}

void sculptor::writeoff(const char* filename) {
    ofstream f(filename);
    if (!f.is_open()) return;
    int total = 0;
    for(int i=0; i<nx; i++) for(int j=0; j<ny; j++) for(int k=0; k<nz; k++) if(v[i][j][k].show) total++;
    f << "OFF\n" << total*8 << " " << total*6 << " 0\n";
    f << fixed << setprecision(1);
    for(int i=0; i<nx; i++) for(int j=0; j<ny; j++) for(int k=0; k<nz; k++) {
                if(v[i][j][k].show) {
                    f << i-0.5 << " " << j+0.5 << " " << k-0.5 << endl;
                    f << i-0.5 << " " << j-0.5 << " " << k-0.5 << endl;
                    f << i+0.5 << " " << j-0.5 << " " << k-0.5 << endl;
                    f << i+0.5 << " " << j+0.5 << " " << k-0.5 << endl;
                    f << i-0.5 << " " << j+0.5 << " " << k+0.5 << endl;
                    f << i-0.5 << " " << j-0.5 << " " << k+0.5 << endl;
                    f << i+0.5 << " " << j-0.5 << " " << k+0.5 << endl;
                    f << i+0.5 << " " << j+0.5 << " " << k+0.5 << endl;
                }
            }
    int c=0;
    for(int i=0; i<nx; i++) for(int j=0; j<ny; j++) for(int k=0; k<nz; k++) {
                if(v[i][j][k].show) {
                    int p=c*8; float r=v[i][j][k].r, g=v[i][j][k].g, b=v[i][j][k].b, a=v[i][j][k].a;
                    f<<"4 "<<p+0<<" "<<p+3<<" "<<p+2<<" "<<p+1<<" "<<r<<" "<<g<<" "<<b<<" "<<a<<endl;
                    f<<"4 "<<p+4<<" "<<p+5<<" "<<p+6<<" "<<p+7<<" "<<r<<" "<<g<<" "<<b<<" "<<a<<endl;
                    f<<"4 "<<p+0<<" "<<p+1<<" "<<p+5<<" "<<p+4<<" "<<r<<" "<<g<<" "<<b<<" "<<a<<endl;
                    f<<"4 "<<p+0<<" "<<p+4<<" "<<p+7<<" "<<p+3<<" "<<r<<" "<<g<<" "<<b<<" "<<a<<endl;
                    f<<"4 "<<p+3<<" "<<p+7<<" "<<p+6<<" "<<p+2<<" "<<r<<" "<<g<<" "<<b<<" "<<a<<endl;
                    f<<"4 "<<p+1<<" "<<p+2<<" "<<p+6<<" "<<p+5<<" "<<r<<" "<<g<<" "<<b<<" "<<a<<endl;
                    c++;
                }
            }
    f.close();
}
