#include "Cinemas.h"
#include<iostream>
#include<vector>

using namespace std;

Cinemas::Cinemas() {} // Construtor vazio
Cinemas::Cinemas(int ID, const string &nome_cinema, const string &coordenada_x, const string &coordenada_y, const string &preco_ingresso, const vector<int> &filmes_em_exibicao) {
    this->ID = ID;
    this->nome_cinema = nome_cinema;
    this->coordenada_x = coordenada_x;
    this->coordenada_y = coordenada_y;
    this->preco_ingresso = preco_ingresso;
    this->filmes_em_exibicao = filmes_em_exibicao;

} // Construtor com parâmetros


// Getters
int Cinemas::getID() const { return ID; }
const string& Cinemas::getNomeCinema() const { 
    return nome_cinema; 
}
const string& Cinemas::getCoordenadaX() const { 
    return coordenada_x; 
}
const string& Cinemas::getCoordenadaY() const { 
    return coordenada_y; 
}
const string& Cinemas::getPrecoIngresso() const { 
    return preco_ingresso; 
}
const vector<int>& Cinemas::getFilmesEmExibicao() const { 
    return filmes_em_exibicao; 
}

// Setters
void Cinemas::setNomeCinema(const string &nome_cinema) { 
    this->nome_cinema = nome_cinema; 
}
void Cinemas::setCoordenadaX(const string &coordenada_x) { 
    this->coordenada_x = coordenada_x; 
}
void Cinemas::setCoordenadaY(const string &coordenada_y) { 
    this->coordenada_y = coordenada_y; 
}
void Cinemas::setPrecoIngresso(const string &preco_ingresso) { 
    this->preco_ingresso = preco_ingresso; 
}
void Cinemas::setFilmesEmExibicao(const vector<int> &filmes_em_exibicao) { 
    this->filmes_em_exibicao = filmes_em_exibicao; 
}
