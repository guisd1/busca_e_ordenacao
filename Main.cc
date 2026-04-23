#include "Filme.cc"
#include "Cinema.cc"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    ifstream arquivo("documentos/filmesCrop.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }
    string linha;
    vector<Filme> listaFilmes;

    getline(arquivo, linha); // pula cabeçalho se tiver

    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string sID, tipo_titulo, titulo_primario, titulo_original;
        string sAdulto, sAno, sTempo, sGenero;

        getline(ss, sID, '\t');
        getline(ss, tipo_titulo, '\t');
        getline(ss, titulo_primario, '\t');
        getline(ss, titulo_original, '\t');
        getline(ss, sAdulto, '\t');
        getline(ss, sAno, '\t');
        getline(ss, sTempo, '\t');
        getline(ss, sGenero, '\t');

        // separa múltiplos gêneros
        vector<string> genero;
        stringstream ssGenero(sGenero);
        string g;
        while (getline(ssGenero, g, ',')) {
            genero.push_back(g);
        }

        // trata \N como 0
        int ano = 0, tempo = 0;
        try { ano = (sAno == "\\N") ? 0 : stoi(sAno); } 
            catch (const invalid_argument& e) { ano = 0; }
        try { tempo = (sTempo == "\\N") ? 0 : stoi(sTempo); } 
            catch (const invalid_argument& e) { tempo=0; }

        Filme f;
        f.setID(sID);
        f.setTipoTitulo(tipo_titulo);
        f.setTituloPrimario(titulo_primario);
        f.setTituloOriginal(titulo_original);
        f.setEhAdulto(sAdulto == "1");
        f.setAnoLancamento(ano);
        f.setTempoFilme(tempo);
        f.setGenero(genero);

        listaFilmes.push_back(f);
    }

    arquivo.close();
    return 0;
}