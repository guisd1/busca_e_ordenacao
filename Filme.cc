#include "Filmes.h"
#include<iostream>
#include<vector>

using namespace std;

Filmes::Filmes() {} // Construtor vazio
Filmes::Filmes(int ID, int ano_lancamento, int tempo_filme, const string &tipo_titulo, const string &titulo_primario, const string &titulo_original, const vector<string> &genero, bool eh_adulto) {
    this->ID = ID;
    this->ano_lancamento = ano_lancamento;
    this->tempo_filme = tempo_filme;
    this->tipo_titulo = tipo_titulo;
    this->titulo_primario = titulo_primario;
    this->titulo_original = titulo_original;
    this->genero = genero;
    this->eh_adulto = eh_adulto;
} // Construtor com parâmetros


// Getters
int Filmes::getID() const {
    return this->ID;
}

int Filmes::getAnoLancamento() const {
    return this->ano_lancamento;
}

int Filmes::getTempoFilme() const {
    return this->tempo_filme;
}

string Filmes::getTipoTitulo() const {
    return this->tipo_titulo;
}

string Filmes::getTituloPrimario() const {
    return this->titulo_primario;
}

string Filmes::getTituloOriginal() const {
    return this->titulo_original;
}

vector<string> Filmes::getGenero() const {
    return this->genero;
}

bool Filmes::isEhAdulto() const {
    return this->eh_adulto;
}

// Setters
void Filmes::setID(int ID) {
    this->ID = ID;
}

void Filmes::setAnoLancamento(int ano_lancamento) {
    this->ano_lancamento = ano_lancamento;
}

void Filmes::setTempoFilme(int tempo_filme) {
    this->tempo_filme = tempo_filme;
}

void Filmes::setTipoTitulo(const string &tipo_titulo) {
    this->tipo_titulo = tipo_titulo;
}

void Filmes::setTituloPrimario(const string &titulo_primario) {
    this->titulo_primario = titulo_primario;
}

void Filmes::setTituloOriginal(const string &titulo_original) {
    this->titulo_original = titulo_original;
}

void Filmes::setGenero(const vector<string> &genero) {
    this->genero = genero;
}

void Filmes::setEhAdulto(bool eh_adulto) {
    this->eh_adulto = eh_adulto;
}