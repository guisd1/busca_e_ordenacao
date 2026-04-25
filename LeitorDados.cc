#include "Filme.h"
#include "Cinema.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

class LeitorDados {
private:
    vector<Filme> listaFilmes;
    vector<Cinema> listaCinemas;
    unordered_map<string, int> indiceFilmes;

public:
    void lerDados() {
        auto inicio_cronometro = chrono::high_resolution_clock::now();

        // --- FILMES ---
        ifstream arquivoFilmes("documentos/filmesCrop.txt");
        if (!arquivoFilmes.is_open()) { cout << "Erro ao abrir filmes!" << endl; return; }

        string linha;
        listaFilmes.reserve(600000);
        getline(arquivoFilmes, linha); // pula cabeçalho

        while (getline(arquivoFilmes, linha)) {
            if (linha.empty()) continue;

            size_t cursor = 0, divisor;
            auto extrairF = [&](char delim) -> string {
                if (cursor == string::npos) return "";
                divisor = linha.find(delim, cursor);
                string campo = linha.substr(cursor, divisor - cursor);
                cursor = (divisor == string::npos) ? string::npos : divisor + 1;
                return campo;
            };

            string sID    = extrairF('\t');
            string tipo   = extrairF('\t');
            string tPri   = extrairF('\t');
            string tOri   = extrairF('\t');
            string sAdult = extrairF('\t');
            string sAno   = extrairF('\t');
            string sEndY = extrairF('\t');
            string sTempo = extrairF('\t');
            string sGen   = extrairF('\t');

            vector<string> generos;
            size_t g_pos = 0, g_div;
            while ((g_div = sGen.find(',', g_pos)) != string::npos) {
                generos.push_back(sGen.substr(g_pos, g_div - g_pos));
                g_pos = g_div + 1;
            }
            if (!sGen.empty()) generos.push_back(sGen.substr(g_pos));

            int ano = 0, tempo = 0;
            try { if (!sAno.empty()   && sAno   != "\\N") ano   = stoi(sAno);   } catch (...) {}
            try { if (!sTempo.empty() && sTempo != "\\N") tempo = stoi(sTempo); } catch (...) {}

            Filme f;
            f.setID(std::move(sID));
            f.setTipoTitulo(std::move(tipo));
            f.setTituloPrimario(std::move(tPri));
            f.setTituloOriginal(std::move(tOri));
            f.setEhAdulto(sAdult == "1");
            f.setAnoLancamento(ano);
            f.setTempoFilme(tempo);
            f.setGenero(std::move(generos));
            listaFilmes.push_back(std::move(f));
        }
        arquivoFilmes.close();

        // Constrói índice hash
        for (int i = 0; i < (int)listaFilmes.size(); i++)
            indiceFilmes[listaFilmes[i].getID()] = i;

        // IDs ordenados para busca binária (fallback de IDs inexistentes)
        vector<string> idsOrdenados;
        idsOrdenados.reserve(listaFilmes.size());
        for (const Filme& f : listaFilmes)
            idsOrdenados.push_back(f.getID());
        sort(idsOrdenados.begin(), idsOrdenados.end());

        // --- CINEMAS ---
        ifstream arquivoCinemas("documentos/cinemas.txt");
        if (!arquivoCinemas.is_open()) { cout << "Erro ao abrir cinemas!" << endl; return; }

        getline(arquivoCinemas, linha); // pula cabeçalho

        while (getline(arquivoCinemas, linha)) {
            if (linha.empty()) continue;

            size_t cursor = 0, divisor;
            auto extrairC = [&](char delim) -> string {
                if (cursor == string::npos) return "";
                divisor = linha.find(delim, cursor);
                string campo = linha.substr(cursor, divisor - cursor);
                cursor = (divisor == string::npos) ? string::npos : divisor + 1;
                return campo;
            };

            string cID    = extrairC(',');
            string cNome  = extrairC(',');
            string cX     = extrairC(',');
            string cY     = extrairC(',');
            string cPreco = extrairC(',');

            vector<string> filmes;
            while (cursor != string::npos) {
                string idFilme = extrairC(',');
                size_t p = idFilme.find_first_not_of(" ");
                if (p != string::npos) {
                    size_t u = idFilme.find_last_not_of(" \r");
                    idFilme = idFilme.substr(p, u - p + 1);
                    if (!idFilme.empty()) filmes.push_back(std::move(idFilme));
                }
            }

            // Resolve IDs inexistentes já no carregamento
            vector<string> idsResolvidos;
            for (const string& idFilme : filmes) {
                if (indiceFilmes.count(idFilme)) {
                    idsResolvidos.push_back(idFilme); // existe, usa direto
                } else {
                    // busca binária: ID maior mais próximo
                    auto it = upper_bound(idsOrdenados.begin(), idsOrdenados.end(), idFilme);
                    if (it != idsOrdenados.end())
                        idsResolvidos.push_back(*it);
                }
            }

            Cinema c;
            c.setID(std::move(cID));
            c.setNomeCinema(std::move(cNome));
            try { c.setCoordenadaX(stoi(cX));     } catch (...) { c.setCoordenadaX(0); }
            try { c.setCoordenadaY(stoi(cY));     } catch (...) { c.setCoordenadaY(0); }
            try { c.setPrecoIngresso(stod(cPreco)); } catch (...) { c.setPrecoIngresso(0.0); }
            c.setFilmesEmExibicao(std::move(idsResolvidos));

            listaCinemas.push_back(std::move(c));
        }
        arquivoCinemas.close();

        auto fim_cronometro = chrono::high_resolution_clock::now();
        chrono::duration<double> duracao = fim_cronometro - inicio_cronometro;
        cout << "Filmes lidos:  " << listaFilmes.size() << endl;
        cout << "Cinemas lidos: " << listaCinemas.size() << endl;
        cout << "Tempo de carregamento: " << duracao.count() * 1000 << " ms" << endl;
    }

    const vector<Filme>&               getFilmes() const { return listaFilmes; }
    const vector<Cinema>&              getCinemas() const { return listaCinemas; }
    const unordered_map<string, int>&  getIndice() const { return indiceFilmes; }
};