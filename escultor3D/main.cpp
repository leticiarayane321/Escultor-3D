#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

// Inclusões das Classes Principais (Tudo minúsculo conforme solicitado)
#include "sculptor.h"
#include "figurageometrica.h"

// Inclusões das 8 Classes Concretas
#include "putvoxel.h"
#include "cutvoxel.h"
#include "putbox.h"
#include "cutbox.h"
#include "putsphere.h"
#include "cutsphere.h"
#include "putellipsoid.h"
#include "cutellipsoid.h"

using namespace std;

int main() {
    // 1. DECLARAÇÃO DE VARIÁVEIS
    int dim_x = 0, dim_y = 0, dim_z = 0;
    // Variáveis usadas para ler parâmetros de todas as formas
    int x0, x1, y0, y1, z0, z1, raio, rx, ry, rz;
    float r, g, b, a;

    vector<figurageometrica*> lista_de_comandos;
    string comando_atual;
    string token;

    cout << "Iniciando. Tentando abrir comandos.txt" << endl;

    ifstream fluxo_entrada_comandos;
fluxo_entrada_comandos.open("comandos.txt");
    if (!fluxo_entrada_comandos.is_open()) {
        cerr << "Nao foi possivel abrir comandos.txt!" << endl;
        return 1;
    }

    cout << "Arquivo comandos.txt aberto." << endl;

    // LEITURA E PARSING
    while (getline(fluxo_entrada_comandos, comando_atual)) {
        stringstream ss(comando_atual);
        ss >> token;

        if (token == "dim") {
            ss >> dim_x >> dim_y >> dim_z;
        }
        else if (token == "putvoxel") {
            ss >> x0 >> y0 >> z0 >> r >> g >> b >> a;
            lista_de_comandos.push_back(new putvoxel(x0, y0, z0, r, g, b, a));
        }
        else if (token == "cutvoxel") {
            ss >> x0 >> y0 >> z0;
            lista_de_comandos.push_back(new cutvoxel(x0, y0, z0));
        }
        else if (token == "putbox") {
            ss >> x0 >> x1 >> y0 >> y1 >> z0 >> z1 >> r >> g >> b >> a;
            lista_de_comandos.push_back(new putbox(x0, x1, y0, y1, z0, z1, r, g, b, a));
        }
        else if (token == "cutbox") {
            ss >> x0 >> x1 >> y0 >> y1 >> z0 >> z1;
            lista_de_comandos.push_back(new cutbox(x0, x1, y0, y1, z0, z1));
        }
        else if (token == "putsphere") {
            ss >> x0 >> y0 >> z0 >> raio >> r >> g >> b >> a;
            lista_de_comandos.push_back(new putsphere(x0, y0, z0, raio, r, g, b, a));
        }
        else if (token == "cutsphere") {
            ss >> x0 >> y0 >> z0 >> raio;
            lista_de_comandos.push_back(new cutsphere(x0, y0, z0, raio));
        }
        else if (token == "putellipsoid") {
            ss >> x0 >> y0 >> z0 >> rx >> ry >> rz >> r >> g >> b >> a;
            lista_de_comandos.push_back(new putellipsoid(x0, y0, z0, rx, ry, rz, r, g, b, a));
        }
        else if (token == "cutellipsoid") {
            ss >> x0 >> y0 >> z0 >> rx >> ry >> rz;
            lista_de_comandos.push_back(new cutellipsoid(x0, y0, z0, rx, ry, rz));
        }
    }

    cout << " Leitura concluida. Verificando dimensoes." << endl;

    if (dim_x <= 0 || lista_de_comandos.empty()) {
        cerr << "ERRO: Dimensoes invalidas (dim_x<=0) ou comandos vazios. Finalizando." << endl;
        // Limpeza de memória
        for (figurageometrica* figura : lista_de_comandos) {
            delete figura;
        }
        return 1;
    }

    cout << "Dimensões lidas: " << dim_x << "x" << dim_y << "x" << dim_z << endl;
    cout << "Comandos no vetor: " << lista_de_comandos.size() << endl;

    // EXECUÇÃO (Cria o Sculptor e executa os comandos)
    sculptor* escultor_3d = new sculptor(dim_x, dim_y, dim_z);

    cout << "Iniciando loop de desenho (Polimorfismo). ---" << endl;

    // Itera sobre o vetor e chama o método virtual draw()
    for (figurageometrica* figura : lista_de_comandos) {
        figura->draw(*escultor_3d);
    }

    //Geração do Arquivo OFF
    cout << "Desenho finalizado. Tentando gerar OFF." << endl;

    // Deixei writeOFF pois geralmente métodos mantêm camelCase, mas verifique seu .h
    escultor_3d->writeoff("escultura_final_parte2.off");

    cout << " Arquivo OFF gerado com sucesso." << endl;

    // LIMPEZA DE MEMÓRIA (para não ter vazamento)
    delete escultor_3d;

    // Libera os objetos FiguraGeometrica do vetor (Polimorfismo)
    for (figurageometrica* figura : lista_de_comandos) {
        delete figura;
    }
    lista_de_comandos.clear();

    return 0;
}
