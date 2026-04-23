#include "Filme.cc"
#include "Cinema.cc"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    // Filmes
    ifstream arquivoFilmes("documentos/filmesCrop.txt");
    if (!arquivoFilmes.is_open()) {
        cout << "Erro ao abrir filmes!" << endl;
        return 1;
    }
    string linha;
    vector<Filme> listaFilmes;
    getline(arquivoFilmes, linha); // pula cabeçalho
    while (getline(arquivoFilmes, linha)) {
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
        vector<string> genero;
        stringstream ssGenero(sGenero);
        string g;
        while (getline(ssGenero, g, ',')) genero.push_back(g);
        int ano = 0, tempo = 0;
        try { ano = stoi(sAno); } catch (const invalid_argument& e) { ano = 0; }
        try { tempo = stoi(sTempo); } catch (const invalid_argument& e) { tempo = 0; }
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
    arquivoFilmes.close();

    // Cinemas
    ifstream arquivoCinemas("documentos/cinemas.txt");
    if (!arquivoCinemas.is_open()) {
        cout << "Erro ao abrir cinemas!" << endl;
        return 1;
    }
    vector<Cinema> listaCinemas;
    while (getline(arquivoCinemas, linha)) {
        stringstream ss(linha);
        string sID, nome_cinema, sCoordenadaX, sCoordenadaY, sPreco, sFilme;
        getline(ss, sID, ',');
        getline(ss, nome_cinema, ',');
        getline(ss, sCoordenadaX, ',');
        getline(ss, sCoordenadaY, ',');
        getline(ss, sPreco, ',');
        vector<string> filmesEmExibicao;
        while (getline(ss, sFilme, ',')) {
            sFilme.erase(0, sFilme.find_first_not_of(" "));
            sFilme.erase(sFilme.find_last_not_of(" \r") + 1);
            if (!sFilme.empty()) filmesEmExibicao.push_back(sFilme);
        }
        Cinema c;
        c.setID(sID);
        c.setNomeCinema(nome_cinema);
        try { c.setCoordenadaX(stoi(sCoordenadaX)); } catch (const invalid_argument& e) { c.setCoordenadaX(0); }
        try { c.setCoordenadaY(stoi(sCoordenadaY)); } catch (const invalid_argument& e) { c.setCoordenadaY(0); }
        try { c.setPrecoIngresso(stod(sPreco)); } catch (const invalid_argument& e) { c.setPrecoIngresso(0); }
        c.setFilmesEmExibicao(filmesEmExibicao);
        listaCinemas.push_back(c);
    }
    arquivoCinemas.close();

    cout << "Filmes lidos: " << listaFilmes.size() << endl;
    cout << "Cinemas lidos: " << listaCinemas.size() << endl;

    return 0;
}
