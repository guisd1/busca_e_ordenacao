#ifndef BUSCADOR_H
#define BUSCADOR_H
#include "Filme.h"
#include "Cinema.h"
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Buscador {
private:
    const vector<Filme>& filmes;
    const vector<Cinema>& cinemas;
    const unordered_map<string, int>& indice;

    // Filtros de filme
    vector<Filme> filtrarPorTipo(const vector<Filme>& lista, const vector<string>& tipos, bool operadorE);
    vector<Filme> filtrarPorGenero(const vector<Filme>& lista, const vector<string>& generos, bool operadorE);
    vector<Filme> filtrarPorDuracao(const vector<Filme>& lista, int minMin, int maxMin);
    vector<Filme> filtrarPorAno(const vector<Filme>& lista, int anoMin, int anoMax);

    // Filtros de cinema
    vector<Cinema> filtrarPorDistancia(const vector<Cinema>& lista, int x, int y, double distMax);
    vector<Cinema> filtrarPorPreco(const vector<Cinema>& lista, double precoMax);
    vector<Cinema> filtrarCinemaPorTitulo(const vector<Cinema>& lista, const string& titulo);
    vector<Cinema> filtrarCinemaPorTipo(const vector<Cinema>& lista, const vector<string>& tipos, bool operadorE);
    vector<Cinema> filtrarCinemaPorGenero(const vector<Cinema>& lista, const vector<string>& generos, bool operadorE);
    vector<Cinema> filtrarCinemaPorDuracao(const vector<Cinema>& lista, int minMin, int maxMin);
    vector<Cinema> filtrarCinemaPorAno(const vector<Cinema>& lista, int anoMin, int anoMax);

    // Auxiliar: busca filme por ID usando o índice (com fallback para ID mais próximo)
    const Filme* buscarFilmePorID(const string& id) const;

public:
    Buscador(const vector<Filme>& f, const vector<Cinema>& c, const unordered_map<string, int>& idx);
    vector<Filme> buscarFilmes();
    vector<Cinema> buscarCinemas();
};

#endif