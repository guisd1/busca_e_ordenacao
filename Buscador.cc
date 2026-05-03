#include "Buscador.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <chrono>
using namespace std;

Buscador(const std::vector<Filme>& f, const std::vector<Cinema>& c, const std::unordered_map<std::string, int>& idx);
    : filmes(f), cinemas(c), indice(idx) {}

// ── AUXILIAR ────────────────────────────────────────────────────

const Filme* Buscador::buscarFilmePorID(const string& id) const {
    auto it = indice.find(id);
    if (it != indice.end())
        return &filmes[it->second];

    // Caso especial: ID não existe → busca o ID maior mais próximo
    // Os IDs são strings no formato "tt1234567", comparação lexicográfica funciona
    const Filme* melhor = nullptr;
    for (const Filme& f : filmes) {
        if (f.getID() > id) {
            if (melhor == nullptr || f.getID() < melhor->getID())
                melhor = &f;
        }
    }
    return melhor;
}

// ── FILTROS DE FILME ────────────────────────────────────────────

vector<Filme> Buscador::filtrarPorTipo(const vector<Filme>& lista, const vector<string>& tipos, bool operadorE) {
    vector<Filme> resultado;
    for (const Filme& f : lista) {
        bool match = operadorE;
        for (const string& tipo : tipos) {
            bool igual = (f.getTipoTitulo() == tipo);
            if (operadorE) match = match && igual;
            else           match = match || igual;
        }
        if (match) resultado.push_back(f);
    }
    return resultado;
}

vector<Filme> Buscador::filtrarPorGenero(const vector<Filme>& lista, const vector<string>& generos, bool operadorE) {
    vector<Filme> resultado;
    for (const Filme& f : lista) {
        const vector<string>& gf = f.getGenero();
        bool match = operadorE;
        for (const string& g : generos) {
            bool tem = false;
            for (const string& gFilme : gf)
                if (gFilme == g) { tem = true; break; }
            if (operadorE) match = match && tem;
            else           match = match || tem;
        }
        if (match) resultado.push_back(f);
    }
    return resultado;
}

vector<Filme> Buscador::filtrarPorDuracao(const vector<Filme>& lista, int minMin, int maxMin) {
    vector<Filme> resultado;
    for (const Filme& f : lista) {
        int t = f.getTempoFilme();
        if (t > 0 && t >= minMin && t <= maxMin)
            resultado.push_back(f);
    }
    return resultado;
}

vector<Filme> Buscador::filtrarPorAno(const vector<Filme>& lista, int anoMin, int anoMax) {
    vector<Filme> resultado;
    for (const Filme& f : lista) {
        int ano = f.getAnoLancamento();
        if (ano > 0 && ano >= anoMin && ano <= anoMax)
            resultado.push_back(f);
    }
    return resultado;
}

// ── FILTROS DE CINEMA ───────────────────────────────────────────

vector<Cinema> Buscador::filtrarPorPreco(const vector<Cinema>& lista, double precoMax) {
    vector<Cinema> resultado;
    for (const Cinema& c : lista)
        if (c.getPrecoIngresso() <= precoMax)
            resultado.push_back(c);
    return resultado;
}

vector<Cinema> Buscador::filtrarPorDistancia(const vector<Cinema>& lista, int x, int y, double distMax) {
    vector<Cinema> resultado;
    for (const Cinema& c : lista) {
        double dx = c.getCoordenadaX() - x;
        double dy = c.getCoordenadaY() - y;
        if (sqrt(dx*dx + dy*dy) <= distMax)
            resultado.push_back(c);
    }
    return resultado;
}

vector<Cinema> Buscador::filtrarCinemaPorTitulo(const vector<Cinema>& lista, const string& titulo) {
    vector<Cinema> resultado;
    for (const Cinema& c : lista) {
        for (const string& idFilme : c.getFilmesEmExibicao()) {
            const Filme* f = buscarFilmePorID(idFilme);
            if (f && (f->getTituloPrimario() == titulo || f->getTituloOriginal() == titulo)) {
                resultado.push_back(c);
                break;
            }
        }
    }
    return resultado;
}

vector<Cinema> Buscador::filtrarCinemaPorTipo(const vector<Cinema>& lista, const vector<string>& tipos, bool operadorE) {
    vector<Cinema> resultado;
    for (const Cinema& c : lista) {
        bool cinemaMatch = false;
        for (const string& idFilme : c.getFilmesEmExibicao()) {
            const Filme* f = buscarFilmePorID(idFilme);
            if (!f) continue;
            bool filmeMatch = operadorE;
            for (const string& tipo : tipos) {
                bool igual = (f->getTipoTitulo() == tipo);
                if (operadorE) filmeMatch = filmeMatch && igual;
                else           filmeMatch = filmeMatch || igual;
            }
            if (filmeMatch) { cinemaMatch = true; break; }
        }
        if (cinemaMatch) resultado.push_back(c);
    }
    return resultado;
}

vector<Cinema> Buscador::filtrarCinemaPorGenero(const vector<Cinema>& lista, const vector<string>& generos, bool operadorE) {
    vector<Cinema> resultado;
    for (const Cinema& c : lista) {
        bool cinemaMatch = false;
        for (const string& idFilme : c.getFilmesEmExibicao()) {
            const Filme* f = buscarFilmePorID(idFilme);
            if (!f) continue;
            const vector<string>& gf = f->getGenero();
            bool filmeMatch = operadorE;
            for (const string& g : generos) {
                bool tem = false;
                for (const string& gFilme : gf)
                    if (gFilme == g) { tem = true; break; }
                if (operadorE) filmeMatch = filmeMatch && tem;
                else           filmeMatch = filmeMatch || tem;
            }
            if (filmeMatch) { cinemaMatch = true; break; }
        }
        if (cinemaMatch) resultado.push_back(c);
    }
    return resultado;
}

vector<Cinema> Buscador::filtrarCinemaPorDuracao(const vector<Cinema>& lista, int minMin, int maxMin) {
    vector<Cinema> resultado;
    for (const Cinema& c : lista) {
        bool cinemaMatch = false;
        for (const string& idFilme : c.getFilmesEmExibicao()) {
            const Filme* f = buscarFilmePorID(idFilme);
            if (!f) continue;
            int t = f->getTempoFilme();
            if (t > 0 && t >= minMin && t <= maxMin) { cinemaMatch = true; break; }
        }
        if (cinemaMatch) resultado.push_back(c);
    }
    return resultado;
}

vector<Cinema> Buscador::filtrarCinemaPorAno(const vector<Cinema>& lista, int anoMin, int anoMax) {
    vector<Cinema> resultado;
    for (const Cinema& c : lista) {
        bool cinemaMatch = false;
        for (const string& idFilme : c.getFilmesEmExibicao()) {
            const Filme* f = buscarFilmePorID(idFilme);
            if (!f) continue;
            int ano = f->getAnoLancamento();
            if (ano > 0 && ano >= anoMin && ano <= anoMax) { cinemaMatch = true; break; }
        }
        if (cinemaMatch) resultado.push_back(c);
    }
    return resultado;
}

// ── MENUS ───────────────────────────────────────────────────────

vector<Filme> Buscador::buscarFilmes() {
    vector<Filme> resultado(filmes);
    int opcao;
    do {
        cout << "\n=== FILTROS DE FILME ===" << endl;
        cout << "1. Por tipo" << endl;
        cout << "2. Por genero" << endl;
        cout << "3. Por duracao" << endl;
        cout << "4. Por ano" << endl;
        cout << "5. Exibir resultados" << endl;
        cout << "0. Concluir" << endl;
        cout << "Opcao: ";
        cin >> opcao;

        if (opcao == 1) {
            int op, n; cout << "Operador (1=OU 2=E): "; cin >> op;
            cout << "Quantos tipos? "; cin >> n;
            vector<string> tipos(n);
            for (auto& t : tipos) { cout << "Tipo: "; cin >> t; }
            
            auto inicio = chrono::high_resolution_clock::now();
            resultado = filtrarPorTipo(resultado, tipos, op == 2);
            auto fim = chrono::high_resolution_clock::now();
            chrono::duration<double> dur = fim - inicio;
            cout << "Tempo de busca: " << dur.count()*1000<< " ms\n";

        } else if (opcao == 2) {
            int op, n; cout << "Operador (1=OU 2=E): "; cin >> op;
            cout << "Quantos generos? "; cin >> n;
            vector<string> gens(n);
            for (auto& g : gens) { cout << "Genero: "; cin >> g; }
            
            auto inicio = chrono::high_resolution_clock::now();
            resultado = filtrarPorGenero(resultado, gens, op == 2);
            auto fim = chrono::high_resolution_clock::now();
            chrono::duration<double> dur = fim - inicio;
            cout << "Tempo de busca: " << dur.count()*1000<< " ms\n";

        } else if (opcao == 3) {
            int mn, mx;
            cout << "Duracao minima (min): "; cin >> mn;
            cout << "Duracao maxima (min): "; cin >> mx;
            
            auto inicio = chrono::high_resolution_clock::now();
            resultado = filtrarPorDuracao(resultado, mn, mx);
            auto fim = chrono::high_resolution_clock::now();
            chrono::duration<double> dur = fim - inicio;
            cout << "Tempo de busca: " << dur.count()*1000<< " ms\n";

        } else if (opcao == 4) {
            int a1, a2;
            cout << "Ano inicial: "; cin >> a1;
            cout << "Ano final:   "; cin >> a2;
            
            auto inicio = chrono::high_resolution_clock::now();
            resultado = filtrarPorAno(resultado, a1, a2);
            auto fim = chrono::high_resolution_clock::now();
            chrono::duration<double> dur = fim - inicio;
            cout << "Tempo de busca: " << dur.count()*1000<< " ms\n";
            
        } else if (opcao == 5) {
            int qtd;
            cout << "Quantos resultados deseja exibir? ";
            cin >> qtd;
            
            int limite = qtd;
            if (qtd > (int)resultado.size()) {
                limite = min((int)resultado.size(), 10);
                cout << "[Aviso] Quantidade solicitada excede o total de resultados. Exibindo ate os " << limite << " primeiros...\n";
            }
            
            cout << "\n--- RESULTADOS ---" << endl;
            for (int i = 0; i < limite; ++i) {
                cout << i + 1 << ". " << resultado[i].getTituloPrimario() << " (" << resultado[i].getAnoLancamento() << ")" << endl;
            }
            cout << "------------------\n";
        }

        // Exibe quantidade parcial apenas se a opção foi um filtro
        if (opcao >= 1 && opcao <= 4)
            cout << "Resultados parciais: " << resultado.size() << endl;

    } while (opcao != 0);
    return resultado;
}

vector<Cinema> Buscador::buscarCinemas() {
    vector<Cinema> resultado(cinemas);
    int opcao;
    do {
        cout << "\n=== FILTROS DE CINEMA ===" << endl;
        cout << "1. Por tipo de filme" << endl;
        cout << "2. Por genero de filme" << endl;
        cout << "3. Por duracao de filme" << endl;
        cout << "4. Por ano de filme" << endl;
        cout << "5. Por distancia" << endl;
        cout << "6. Por preco" << endl;
        cout << "7. Por titulo de filme" << endl;
        cout << "8. Exibir resultados" << endl;
        cout << "0. Concluir" << endl;
        cout << "Opcao: ";
        cin >> opcao;

        if (opcao == 1) {
            int op, n; cout << "Operador (1=OU 2=E): "; cin >> op;
            cout << "Quantos tipos? "; cin >> n;
            vector<string> tipos(n);
            for (auto& t : tipos) { cout << "Tipo: "; cin >> t; }
            
            auto inicio = chrono::high_resolution_clock::now();
            resultado = filtrarCinemaPorTipo(resultado, tipos, op == 2);
            auto fim = chrono::high_resolution_clock::now();
            chrono::duration<double> dur = fim - inicio;
            cout << "Tempo de busca: " << dur.count()*1000<< " ms\n";

        } else if (opcao == 2) {
            int op, n; cout << "Operador (1=OU 2=E): "; cin >> op;
            cout << "Quantos generos? "; cin >> n;
            vector<string> gens(n);
            for (auto& g : gens) { cout << "Genero: "; cin >> g; }
            
            auto inicio = chrono::high_resolution_clock::now();
            resultado = filtrarCinemaPorGenero(resultado, gens, op == 2);
            auto fim = chrono::high_resolution_clock::now();
            chrono::duration<double> dur = fim - inicio;
            cout << "Tempo de busca: " << dur.count()*1000<< " ms\n";

        } else if (opcao == 3) {
            int mn, mx;
            cout << "Duracao minima (min): "; cin >> mn;
            cout << "Duracao maxima (min): "; cin >> mx;
            
            auto inicio = chrono::high_resolution_clock::now();
            resultado = filtrarCinemaPorDuracao(resultado, mn, mx);
            auto fim = chrono::high_resolution_clock::now();
            chrono::duration<double> dur = fim - inicio;
            cout << "Tempo de busca: " << dur.count()*1000<< " ms\n";

        } else if (opcao == 4) {
            int a1, a2;
            cout << "Ano inicial: "; cin >> a1;
            cout << "Ano final:   "; cin >> a2;
            
            auto inicio = chrono::high_resolution_clock::now();
            resultado = filtrarCinemaPorAno(resultado, a1, a2);
            auto fim = chrono::high_resolution_clock::now();
            chrono::duration<double> dur = fim - inicio;
            cout << "Tempo de busca: " << dur.count()*1000<< " ms\n";

        } else if (opcao == 5) {
            int x, y; double dist;
            cout << "X: "; cin >> x;
            cout << "Y: "; cin >> y;
            cout << "Distancia maxima: "; cin >> dist;
            
            auto inicio = chrono::high_resolution_clock::now();
            resultado = filtrarPorDistancia(resultado, x, y, dist);
            auto fim = chrono::high_resolution_clock::now();
            chrono::duration<double> dur = fim - inicio;
            cout << "Tempo de busca: " << dur.count()*1000<< " ms\n";

        } else if (opcao == 6) {
            double pmax;
            cout << "Preco maximo: "; cin >> pmax;
            
            auto inicio = chrono::high_resolution_clock::now();
            resultado = filtrarPorPreco(resultado, pmax);
            auto fim = chrono::high_resolution_clock::now();
            chrono::duration<double> dur = fim - inicio;
            cout << "Tempo de busca: " << dur.count()*1000<< " ms\n";

        } else if (opcao == 7) {
            string titulo;
            cout << "Titulo do filme: ";
            cin.ignore();
            getline(cin, titulo);
            
            auto inicio = chrono::high_resolution_clock::now();
            resultado = filtrarCinemaPorTitulo(resultado, titulo);
            auto fim = chrono::high_resolution_clock::now();
            chrono::duration<double> dur = fim - inicio;
            cout << "Tempo de busca: " << dur.count()*1000<< " ms\n";
            
        } else if (opcao == 8) {
            int qtd;
            cout << "Quantos resultados deseja exibir? ";
            cin >> qtd;
            
            int limite = qtd;
            if (qtd > (int)resultado.size()) {
                limite = min((int)resultado.size(), 10);
                cout << "Quantidade solicitada excede o total de resultados. Apenas os " << limite << " primeiros serão exibidos!\n";
            }
            
            cout << "\n--- RESULTADOS ---" << endl;
            for (int i = 0; i < limite; ++i) {
                cout << i + 1 << ". " << resultado[i].getNomeCinema() << endl; // *Nota: Ajuste para o método que retorna o nome do seu Cinema
            }
            cout << "------------------\n";
        }

        // Exibe quantidade parcial apenas se a opção foi um filtro
        if (opcao >= 1 && opcao <= 7)
            cout << "Resultados parciais: " << resultado.size() << endl;

    } while (opcao != 0);
    return resultado;
}