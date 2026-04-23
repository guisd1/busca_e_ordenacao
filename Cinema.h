#ifndef CINEMA_H
#define CINEMA_H
#include <string>
#include <vector>
using namespace std;

class Cinema {
private:
    string ID, nome_cinema;
    int coordenada_x, coordenada_y;
    double preco_ingresso;
    vector<string> filmes_em_exibicao;

public:
    Cinema();
    Cinema(const string& ID, const string& nome_cinema, int coordenada_x, int coordenada_y, double preco_ingresso, const vector<string>& filmes_em_exibicao);

    // Getters
    const string& getID() const;
    const string& getNomeCinema() const;
    int getCoordenadaX() const;
    int getCoordenadaY() const;
    double getPrecoIngresso() const;
    const vector<string>& getFilmesEmExibicao() const;

    // Setters
    void setID(const string& id);
    void setNomeCinema(const string& nome_cinema);
    void setCoordenadaX(int x);
    void setCoordenadaY(int y);
    void setPrecoIngresso(double preco);
    void setFilmesEmExibicao(const vector<string>& filmes);
};

#endif // CINEMA_H