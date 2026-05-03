#include "LeitorDados.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
using namespace std;

// ── Merge sort ────────────────────────────────────────────────────────────────

static void mergePares(vector<pair<string,int>>& v, int esq, int meio, int dir) {
    vector<pair<string,int>> tmp(v.begin() + esq, v.begin() + meio + 1);
    int i = 0, j = meio + 1, k = esq;
    while (i < (int)tmp.size() && j <= dir) {
        if (tmp[i].first <= v[j].first) v[k++] = tmp[i++];
        else                             v[k++] = v[j++];
    }
    while (i < (int)tmp.size()) v[k++] = tmp[i++];
}

static void mergeSort(vector<pair<string,int>>& v, int esq, int dir) {
    if (esq >= dir) return;
    int meio = esq + (dir - esq) / 2;
    mergeSort(v, esq, meio);
    mergeSort(v, meio + 1, dir);
    mergePares(v, esq, meio, dir);
}

// ── Buscas binárias (usadas internamente no carregamento) ─────────────────────

static int buscarID(const vector<pair<string,int>>& idx, const string& id) {
    int esq = 0, dir = (int)idx.size() - 1;
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        if      (idx[meio].first == id) return idx[meio].second;
        else if (idx[meio].first  < id) esq = meio + 1;
        else                            dir = meio - 1;
    }
    return -1;
}

static const string* upperBoundID(const vector<pair<string,int>>& idx, const string& id) {
    int esq = 0, dir = (int)idx.size();
    while (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        if (idx[meio].first <= id) esq = meio + 1;
        else                       dir = meio;
    }
    return (esq < (int)idx.size()) ? &idx[esq].first : nullptr;
}

// ── LeitorDados ───────────────────────────────────────────────────────────────

void LeitorDados::lerDados() {
    auto inicio = chrono::high_resolution_clock::now();

    // --- FILMES ---
    ifstream arquivoFilmes("documentos/filmesCrop.txt");
    if (!arquivoFilmes.is_open()) { cout << "Erro ao abrir filmes!\n"; return; }

    string linha;
    listaFilmes.reserve(600000);
    indiceFilmes.reserve(600000);
    getline(arquivoFilmes, linha); // cabeçalho

    while (getline(arquivoFilmes, linha)) {
        if (linha.empty()) continue;

        size_t cursor = 0, divisor;
        auto extrair = [&](char delim) -> string {
            if (cursor == string::npos) return "";
            divisor = linha.find(delim, cursor);
            string campo = linha.substr(cursor, divisor - cursor);
            cursor = (divisor == string::npos) ? string::npos : divisor + 1;
            return campo;
        };

        string sID    = extrair('\t');
        string tipo   = extrair('\t');
        string tPri   = extrair('\t');
        string tOri   = extrair('\t');
        string sAdult = extrair('\t');
        string sAno   = extrair('\t');
                        extrair('\t'); // endYear ignorado
        string sTempo = extrair('\t');
        string sGen   = extrair('\t');

        vector<string> generos;
        size_t g_pos = 0, g_div;
        while ((g_div = sGen.find(',', g_pos)) != string::npos) {
            generos.push_back(sGen.substr(g_pos, g_div - g_pos));
            g_pos = g_div + 1;
        }
        if (!sGen.empty()) generos.push_back(sGen.substr(g_pos));

        int ano = 0, tempo = 0;
        try { if (sAno   != "\\N" && !sAno.empty())   ano   = stoi(sAno);   } catch (...) {}
        try { if (sTempo != "\\N" && !sTempo.empty())  tempo = stoi(sTempo); } catch (...) {}

        indiceFilmes.emplace_back(sID, (int)listaFilmes.size());

        Filme f;
        f.setID(sID);
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

    mergeSort(indiceFilmes, 0, (int)indiceFilmes.size() - 1);

    // --- CINEMAS ---
    ifstream arquivoCinemas("documentos/cinemas.txt");
    if (!arquivoCinemas.is_open()) { cout << "Erro ao abrir cinemas!\n"; return; }

    getline(arquivoCinemas, linha); // cabeçalho

    while (getline(arquivoCinemas, linha)) {
        if (linha.empty()) continue;

        size_t cursor = 0, divisor;
        auto extrair = [&](char delim) -> string {
            if (cursor == string::npos) return "";
            divisor = linha.find(delim, cursor);
            string campo = linha.substr(cursor, divisor - cursor);
            cursor = (divisor == string::npos) ? string::npos : divisor + 1;
            return campo;
        };

        string cID    = extrair(',');
        string cNome  = extrair(',');
        string cX     = extrair(',');
        string cY     = extrair(',');
        string cPreco = extrair(',');

        vector<string> idsResolvidos;
        while (cursor != string::npos) {
            string idFilme = extrair(',');
            size_t p = idFilme.find_first_not_of(" ");
            if (p == string::npos) continue;
            size_t u = idFilme.find_last_not_of(" \r");
            idFilme = idFilme.substr(p, u - p + 1);
            if (idFilme.empty()) continue;

            if (buscarID(indiceFilmes, idFilme) != -1) {
                idsResolvidos.push_back(idFilme);
            } else {
                const string* prox = upperBoundID(indiceFilmes, idFilme);
                if (prox) idsResolvidos.push_back(*prox);
            }
        }

        Cinema c;
        c.setID(std::move(cID));
        c.setNomeCinema(std::move(cNome));
        try { c.setCoordenadaX(stoi(cX));       } catch (...) { c.setCoordenadaX(0); }
        try { c.setCoordenadaY(stoi(cY));       } catch (...) { c.setCoordenadaY(0); }
        try { c.setPrecoIngresso(stod(cPreco)); } catch (...) { c.setPrecoIngresso(0.0); }
        c.setFilmesEmExibicao(std::move(idsResolvidos));
        listaCinemas.push_back(std::move(c));
    }
    arquivoCinemas.close();

    auto fim = chrono::high_resolution_clock::now();
    chrono::duration<double> dur = fim - inicio;
    cout << "Filmes lidos:  " << listaFilmes.size() << "\n";
    cout << "Cinemas lidos: " << listaCinemas.size() << "\n";
    cout << "Tempo de carregamento: " << dur.count() * 1000 << " ms\n";
}

const vector<Filme>&            LeitorDados::getFilmes()  const { return listaFilmes; }
const vector<Cinema>&           LeitorDados::getCinemas() const { return listaCinemas; }
const vector<pair<string,int>>& LeitorDados::getIndice()  const { return indiceFilmes; }