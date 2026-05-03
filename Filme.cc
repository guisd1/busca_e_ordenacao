#include "Filme.h"

Filme::Filme() : ano_lancamento(0), tempo_filme(0), eh_adulto(false) {}

Filme::Filme(const string& ID, int ano_lancamento, int tempo_filme,
             const string& tipo_titulo, const string& titulo_primario,
             const string& titulo_original, const vector<string>& genero, bool eh_adulto)
    : ID(ID), ano_lancamento(ano_lancamento), tempo_filme(tempo_filme),
      tipo_titulo(tipo_titulo), titulo_primario(titulo_primario),
      titulo_original(titulo_original), genero(genero), eh_adulto(eh_adulto) {}

const string&         Filme::getID()             const { return ID; }
int                   Filme::getAnoLancamento()  const { return ano_lancamento; }
int                   Filme::getTempoFilme()     const { return tempo_filme; }
const string&         Filme::getTipoTitulo()     const { return tipo_titulo; }
const string&         Filme::getTituloPrimario() const { return titulo_primario; }
const string&         Filme::getTituloOriginal() const { return titulo_original; }
const vector<string>& Filme::getGenero()         const { return genero; }
bool                  Filme::isEhAdulto()        const { return eh_adulto; }

void Filme::setID(string id)                  { ID = std::move(id); }
void Filme::setAnoLancamento(int ano)         { ano_lancamento = ano; }
void Filme::setTempoFilme(int tempo)          { tempo_filme = tempo; }
void Filme::setTipoTitulo(string tipo)        { tipo_titulo = std::move(tipo); }
void Filme::setTituloPrimario(string titulo)  { titulo_primario = std::move(titulo); }
void Filme::setTituloOriginal(string titulo)  { titulo_original = std::move(titulo); }
void Filme::setGenero(vector<string> g)       { genero = std::move(g); }
void Filme::setEhAdulto(bool adulto)          { eh_adulto = adulto; }