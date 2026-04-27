#ifndef LEITORDADOS_H
#define LEITORDADOS_H
#include "Filme.h"
#include "Cinema.h"
#include <vector>
#include <string>
using namespace std;

class LeitorDados {
private:
    vector<Filme>            listaFilmes;
    vector<Cinema>           listaCinemas;
    vector<pair<string,int>> indiceFilmes;

public:
    void lerDados();

    const vector<Filme>&            getFilmes()  const;
    const vector<Cinema>&           getCinemas() const;
    const vector<pair<string,int>>& getIndice()  const;
};

#endif