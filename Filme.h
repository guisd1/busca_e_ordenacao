#ifndef FILME_H
#define FILME_H
#include <string>
#include <vector>
using namespace std;

class Filme {
private:
    int ano_lancamento, tempo_filme;
    string ID, tipo_titulo, titulo_primario, titulo_original;
    vector<string> genero;
    bool eh_adulto;

public:
    Filme();
    Filme(const string& ID, int ano_lancamento, int tempo_filme,
          const string& tipo_titulo, const string& titulo_primario,
          const string& titulo_original, const vector<string>& genero, bool eh_adulto);

    // Getters — por referência const, sem cópia
    const string&         getID()             const;
    int                   getAnoLancamento()  const;
    int                   getTempoFilme()     const;
    const string&         getTipoTitulo()     const;
    const string&         getTituloPrimario() const;
    const string&         getTituloOriginal() const;
    const vector<string>& getGenero()         const;
    bool                  isEhAdulto()        const;

    // Setters — recebem por valor para permitir move
    void setID(string id);
    void setAnoLancamento(int ano);
    void setTempoFilme(int tempo);
    void setTipoTitulo(string tipo);
    void setTituloPrimario(string titulo);
    void setTituloOriginal(string titulo);
    void setGenero(vector<string> genero);
    void setEhAdulto(bool adulto);
};

#endif