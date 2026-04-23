#include "Cinema.h"
#include<iostream>
#include<vector>

using namespace std;

Cinema::Cinema() {} // Construtor vazio
Cinema::Cinema(int ID, const string &nome_cinema, const string &coordenada_x, const string &coordenada_y, const string &preco_ingresso, const vector<int> &filmes_em_exibicao) {
    this->ID = ID;
    this->nome_cinema = nome_cinema;
    this->coordenada_x = coordenada_x;
    this->coordenada_y = coordenada_y;
    this->preco_ingresso = preco_ingresso;
    this->filmes_em_exibicao = filmes_em_exibicao;

} // Construtor com parâmetros


// Getters
int Cinema::getID() const { return ID; }
const string& Cinema::getNomeCinema() const { 
    return nome_cinema; 
}
const string& Cinema::getCoordenadaX() const { 
    return coordenada_x; 
}
const string& Cinema::getCoordenadaY() const { 
    return coordenada_y; 
}
const string& Cinema::getPrecoIngresso() const { 
    return preco_ingresso; 
}
const vector<int>& Cinema::getFilmesEmExibicao() const { 
    return filmes_em_exibicao; 
}

// Setters
void Cinema::setNomeCinema(const string &nome_cinema) { 
    this->nome_cinema = nome_cinema; 
}
void Cinema::setCoordenadaX(const string &coordenada_x) { 
    this->coordenada_x = coordenada_x; 
}
void Cinema::setCoordenadaY(const string &coordenada_y) { 
    this->coordenada_y = coordenada_y; 
}
void Cinema::setPrecoIngresso(const string &preco_ingresso) { 
    this->preco_ingresso = preco_ingresso; 
}
void Cinema::setFilmesEmExibicao(const vector<int> &filmes_em_exibicao) { 
    this->filmes_em_exibicao = filmes_em_exibicao; 
}
