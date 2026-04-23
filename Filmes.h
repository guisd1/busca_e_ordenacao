#ifndef FILMES_H
#define FILMES_H

#include<iostream>
#include<vector>

using namespace std;

class filmes {
    private: 
        int ID, ano_lancamento, tempo_filme;
        string tipo_titulo, titulo_primario, titulo_original;
        vector<string> genero;
        bool eh_adulto;

    public:
        filmes();

        filmes(int ID, int ano_lancamento, int tempo_filme, const string &tipo_titulo, const string &titulo_primario, const string &titulo_original, const vector<string> &genero, bool eh_adulto);

        int getID() const;

        int getAnoLancamento() const;

        int getTempoFilme() const;

        string getTipoTitulo() const;

        string getTituloPrimario() const;

        string getTituloOriginal() const;

        vector<string> getGenero() const;

        bool isEhAdulto() const;

        void setID(int ID);

        void setAnoLancamento(int ano_lancamento);

        void setTempoFilme(int tempo_filme);

        void setTipoTitulo(const string &tipo_titulo);

        void setTituloPrimario(const string &titulo_primario);

        void setTituloOriginal(const string &titulo_original);

        void setGenero(const vector<string> &genero);

        void setEhAdulto(bool eh_adulto);
};

#endif // FILMES_H