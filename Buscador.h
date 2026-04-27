#ifndef BUSCADOR_H
#define BUSCADOR_H
#include "Filme.h"
#include "Cinema.h"
#include <vector>
#include <string>
using namespace std;

class Buscador {
private:
    const vector<Filme>&            filmes;
    const vector<Cinema>&           cinemas;
    const vector<pair<string,int>>& indice; // índice ordenado por merge sort

    const Filme* buscarFilmePorID(const string& id) const;

    vector<Filme>  filtrarPorTipo    (const vector<Filme>&,  const vector<string>&, bool op);
    vector<Filme>  filtrarPorGenero  (const vector<Filme>&,  const vector<string>&, bool op);
    vector<Filme>  filtrarPorDuracao (const vector<Filme>&,  int mn, int mx);
    vector<Filme>  filtrarPorAno     (const vector<Filme>&,  int a1, int a2);

    vector<Cinema> filtrarPorDistancia      (const vector<Cinema>&, int x, int y, double dist);
    vector<Cinema> filtrarPorPreco          (const vector<Cinema>&, double pmax);
    vector<Cinema> filtrarCinemaPorTitulo   (const vector<Cinema>&, const string& titulo);
    vector<Cinema> filtrarCinemaPorTipo     (const vector<Cinema>&, const vector<string>&, bool op);
    vector<Cinema> filtrarCinemaPorGenero   (const vector<Cinema>&, const vector<string>&, bool op);
    vector<Cinema> filtrarCinemaPorDuracao  (const vector<Cinema>&, int mn, int mx);
    vector<Cinema> filtrarCinemaPorAno      (const vector<Cinema>&, int a1, int a2);

public:
    Buscador(const vector<Filme>& f, const vector<Cinema>& c,
             const vector<pair<string,int>>& idx);

    vector<Filme>  buscarFilmes();
    vector<Cinema> buscarCinemas();
};

#endif