#include "Filme.h"
#include<iostream>
#include<vector>

using namespace std;

Filme::Filme() {} // Construtor vazio
Filme::Filme(int ID, int ano_lancamento, int tempo_filme, const string &tipo_titulo, const string &titulo_primario, const string &titulo_original, const vector<string> &genero, bool eh_adulto) {
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
int Filme::getID() const {
    return this->ID;
}

int Filme::getAnoLancamento() const {
    return this->ano_lancamento;
}

int Filme::getTempoFilme() const {
    return this->tempo_filme;
}

string Filme::getTipoTitulo() const {
    return this->tipo_titulo;
}

string Filme::getTituloPrimario() const {
    return this->titulo_primario;
}

string Filme::getTituloOriginal() const {
    return this->titulo_original;
}

vector<string> Filme::getGenero() const {
    return this->genero;
}

bool Filme::isEhAdulto() const {
    return this->eh_adulto;
}

// Setters
void Filme::setID(int ID) {
    this->ID = ID;
}

void Filme::setAnoLancamento(int ano_lancamento) {
    this->ano_lancamento = ano_lancamento;
}

void Filme::setTempoFilme(int tempo_filme) {
    this->tempo_filme = tempo_filme;
}

void Filme::setTipoTitulo(const string &tipo_titulo) {
    this->tipo_titulo = tipo_titulo;
}

void Filme::setTituloPrimario(const string &titulo_primario) {
    this->titulo_primario = titulo_primario;
}

void Filme::setTituloOriginal(const string &titulo_original) {
    this->titulo_original = titulo_original;
}

void Filme::setGenero(const vector<string> &genero) {
    this->genero = genero;
}

void Filme::setEhAdulto(bool eh_adulto) {
    this->eh_adulto = eh_adulto;
}