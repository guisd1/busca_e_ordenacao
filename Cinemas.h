#ifndef CINEMAS_H
#define CINEMAS_H

#include <string>
#include <vector>

using namespace std;

class Cinema {
private:
    int ID;
    string nome_cinema, coordenada_x, coordenada_y, preco_ingresso;
    vector<int> filmes_em_exibicao; // IDs dos filmes em exibição

public:
    Cinema();
    Cinema(int ID, const string &nome, const string &coordenada_x, const string &coordenada_y, const string &preco_ingresso, const vector<int> &filmes_em_exibicao);

    // Getters
    int getID() const;
    const string& getNomeCinema() const;
    const string& getCoordenadaX() const;
    const string& getCoordenadaY() const;
    const string& getPrecoIngresso() const;
    const vector<int>& getFilmesEmExibicao() const;

    // Setters
    void setID(int id);
    void setNomeCinema(const string& nome);
    void setCoordenadaX(const string& x);
    void setCoordenadaY(const string& y);
    void setPrecoIngresso(const string& preco);
    void setFilmesEmExibicao(const vector<int>& filmes);
};

#endif // CINEMAS_H