#include "Cinema.h"
#include <iostream>
#include <vector>
using namespace std;

Cinema::Cinema() {}

Cinema::Cinema(const string& ID, const string& nome_cinema, int coordenada_x, int coordenada_y, double preco_ingresso, const vector<string>& filmes_em_exibicao) {
    this->ID = ID;
    this->nome_cinema = nome_cinema;
    this->coordenada_x = coordenada_x;
    this->coordenada_y = coordenada_y;
    this->preco_ingresso = preco_ingresso;
    this->filmes_em_exibicao = filmes_em_exibicao;
}

// Getters
const string& Cinema::getID() const { 
    return ID; 
}
const string& Cinema::getNomeCinema() const { 
    return nome_cinema; 
}
int Cinema::getCoordenadaX() const { 
    return coordenada_x; 
}
int Cinema::getCoordenadaY() const { 
    return coordenada_y; 
}
double Cinema::getPrecoIngresso() const { 
    return preco_ingresso; 
}
const vector<string>& Cinema::getFilmesEmExibicao() const { 
    return filmes_em_exibicao; 
}

// Setters
void Cinema::setID(const string& id) { 
    this->ID = id; 
}
void Cinema::setNomeCinema(const string& nome_cinema) { 
    this->nome_cinema = nome_cinema; 
}
void Cinema::setCoordenadaX(int x) { 
    this->coordenada_x = x; 
}
void Cinema::setCoordenadaY(int y) { 
    this->coordenada_y = y; 
}
void Cinema::setPrecoIngresso(double preco) { 
    this->preco_ingresso = preco; 
}
void Cinema::setFilmesEmExibicao(const vector<string>& filmes) { 
    this->filmes_em_exibicao = filmes; 
}