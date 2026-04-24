#include "Filme.h"
#include "Cinema.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>

using namespace std;

class LerListas {
    public:
        void lerListas() {
            // Implementação para ler as listas de filmes e cinemas
            auto inicio_cronometro = chrono::high_resolution_clock::now();

            ifstream arquivoFilmes("documentos/filmesCrop.txt");
            if (!arquivoFilmes.is_open()) {
                cout << "Erro ao abrir filmes!" << endl;
                return;
            }

            string linha;
            vector<Filme> listaFilmes;
            listaFilmes.reserve(600000);

            getline(arquivoFilmes, linha); // Pula cabeçalho dos filmes

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

                string sID = extrairF('\t');
                string tipo = extrairF('\t');
                string tPri = extrairF('\t');
                string tOri = extrairF('\t');
                string sAdulto = extrairF('\t');
                string sAno = extrairF('\t');
                string sTempo = extrairF('\t');
                string sGen = extrairF('\t');

                vector<string> generos;
                size_t g_pos = 0, g_div;
                while ((g_div = sGen.find(',', g_pos)) != string::npos) {
                    generos.push_back(sGen.substr(g_pos, g_div - g_pos));
                    g_pos = g_div + 1;
                }
                if(!sGen.empty()) generos.push_back(sGen.substr(g_pos));

                int ano = 0, tempo = 0;
                try { if (!sAno.empty() && sAno != "\\N") ano = stoi(sAno); } catch (...) { ano = 0; }
                try { if (!sTempo.empty() && sTempo != "\\N") tempo = stoi(sTempo); } catch (...) { tempo = 0; }

                Filme f;
                f.setID(std::move(sID));
                f.setTipoTitulo(std::move(tipo));
                f.setTituloPrimario(std::move(tPri));
                f.setTituloOriginal(std::move(tOri));
                f.setEhAdulto(sAdulto == "1");
                f.setAnoLancamento(ano);
                f.setTempoFilme(tempo);
                f.setGenero(std::move(generos));
                listaFilmes.push_back(std::move(f));
            }
            arquivoFilmes.close();

            // --- BLOCO DE CINEMAS (CSV) ---
            ifstream arquivoCinemas("documentos/cinemas.txt");
            if (!arquivoCinemas.is_open()) {
                cout << "Erro ao abrir cinemas!" << endl;
                return;
            }

            vector<Cinema> listaCinemas;
            
            // CORREÇÃO: Pula a primeira linha (cabeçalho) do arquivo de cinemas
            if (getline(arquivoCinemas, linha)) {
                // Apenas lê a linha e não faz nada, deixando o cursor na segunda linha
            }

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

                // Extrai campos fixos (separados por vírgula)
                string cID = extrairC(',');
                string cNome = extrairC(',');
                string cX = extrairC(',');
                string cY = extrairC(',');
                string cPreco = extrairC(',');

                // Extrai o restante da linha como filmes em exibição
                vector<string> filmes;
                while (cursor != string::npos) {
                    string idFilme = extrairC(',');
                    // Limpa espaços e \r do ID do filme
                    size_t p = idFilme.find_first_not_of(" ");
                    if (p != string::npos) {
                        size_t u = idFilme.find_last_not_of(" \r");
                        idFilme = idFilme.substr(p, (u - p + 1));
                        if (!idFilme.empty()) filmes.push_back(std::move(idFilme));
                    }
                }

                Cinema c;
                c.setID(std::move(cID));
                c.setNomeCinema(std::move(cNome));
                try { c.setCoordenadaX(stoi(cX)); } catch (...) { c.setCoordenadaX(0); }
                try { c.setCoordenadaY(stoi(cY)); } catch (...) { c.setCoordenadaY(0); }
                try { c.setPrecoIngresso(stod(cPreco)); } catch (...) { c.setPrecoIngresso(0.0); }
                c.setFilmesEmExibicao(std::move(filmes));
                
                listaCinemas.push_back(std::move(c));
            }
            arquivoCinemas.close();

            // --- RESULTADOS ---
            auto fim_cronometro = chrono::high_resolution_clock::now();
            chrono::duration<double> duracao = fim_cronometro - inicio_cronometro;

            cout << "Filmes lidos: " << listaFilmes.size() << endl;
            cout << "Cinemas lidos: " << listaCinemas.size() << endl;
            cout << "Tempo total: " << duracao.count() * 1000 << " ms" << endl;
            }
};