#include "Buscador.h"
#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;

Buscador::Buscador(const vector<Filme>& f, const vector<Cinema>& c,
                   const vector<pair<string,int>>& idx)
    : filmes(f), cinemas(c), indice(idx) {}

// ── AUXILIAR ─────────────────────────────────────────────────────────────────

const Filme* Buscador::buscarFilmePorID(const string& id) const {
    // Busca binária O(log n) no índice ordenado
    int esq = 0, dir = (int)indice.size() - 1;
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        if      (indice[meio].first == id) return &filmes[indice[meio].second];
        else if (indice[meio].first  < id) esq = meio + 1;
        else                               dir = meio - 1;
    }
    // Fallback: ID maior mais próximo via upper_bound binário
    int ub = (int)indice.size();
    esq = 0; dir = ub;
    while (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        if (indice[meio].first <= id) esq = meio + 1;
        else                          dir = meio;
    }
    return (esq < ub) ? &filmes[indice[esq].second] : nullptr;
}

// ── FILTROS DE FILME ──────────────────────────────────────────────────────────

vector<Filme> Buscador::filtrarPorTipo(const vector<Filme>& lista,
                                       const vector<string>& tipos, bool op) {
    vector<Filme> resultado;
    for (const Filme& f : lista) {
        bool match = op; // true para E, false para OU
        for (const string& tipo : tipos) {
            bool igual = (f.getTipoTitulo() == tipo);
            if (op) match = match && igual;
            else    match = match || igual;
        }
        if (match) resultado.push_back(f);
    }
    return resultado;
}

vector<Filme> Buscador::filtrarPorGenero(const vector<Filme>& lista,
                                         const vector<string>& generos, bool op) {
    vector<Filme> resultado;
    for (const Filme& f : lista) {
        const vector<string>& gf = f.getGenero();
        bool match = op;
        for (const string& g : generos) {
            bool tem = false;
            for (const string& gf2 : gf)
                if (gf2 == g) { tem = true; break; }
            if (op) match = match && tem;
            else    match = match || tem;
        }
        if (match) resultado.push_back(f);
    }
    return resultado;
}

vector<Filme> Buscador::filtrarPorDuracao(const vector<Filme>& lista, int mn, int mx) {
    vector<Filme> resultado;
    for (const Filme& f : lista) {
        int t = f.getTempoFilme();
        if (t > 0 && t >= mn && t <= mx) resultado.push_back(f);
    }
    return resultado;
}

vector<Filme> Buscador::filtrarPorAno(const vector<Filme>& lista, int a1, int a2) {
    vector<Filme> resultado;
    for (const Filme& f : lista) {
        int ano = f.getAnoLancamento();
        if (ano > 0 && ano >= a1 && ano <= a2) resultado.push_back(f);
    }
    return resultado;
}

// ── FILTROS DE CINEMA ─────────────────────────────────────────────────────────

vector<Cinema> Buscador::filtrarPorPreco(const vector<Cinema>& lista, double pmax) {
    vector<Cinema> resultado;
    for (const Cinema& c : lista)
        if (c.getPrecoIngresso() <= pmax) resultado.push_back(c);
    return resultado;
}

vector<Cinema> Buscador::filtrarPorDistancia(const vector<Cinema>& lista,
                                             int x, int y, double distMax) {
    vector<Cinema> resultado;
    for (const Cinema& c : lista) {
        double dx = c.getCoordenadaX() - x;
        double dy = c.getCoordenadaY() - y;
        if (sqrt(dx*dx + dy*dy) <= distMax) resultado.push_back(c);
    }
    return resultado;
}

vector<Cinema> Buscador::filtrarCinemaPorTitulo(const vector<Cinema>& lista,
                                                const string& titulo) {
    vector<Cinema> resultado;
    for (const Cinema& c : lista) {
        for (const string& id : c.getFilmesEmExibicao()) {
            const Filme* f = buscarFilmePorID(id);
            if (f && (f->getTituloPrimario() == titulo ||
                      f->getTituloOriginal() == titulo)) {
                resultado.push_back(c);
                break;
            }
        }
    }
    return resultado;
}

vector<Cinema> Buscador::filtrarCinemaPorTipo(const vector<Cinema>& lista,
                                              const vector<string>& tipos, bool op) {
    vector<Cinema> resultado;
    for (const Cinema& c : lista) {
        bool cinemaMatch = false;
        for (const string& id : c.getFilmesEmExibicao()) {
            const Filme* f = buscarFilmePorID(id);
            if (!f) continue;
            bool filmeMatch = op;
            for (const string& tipo : tipos) {
                bool igual = (f->getTipoTitulo() == tipo);
                if (op) filmeMatch = filmeMatch && igual;
                else    filmeMatch = filmeMatch || igual;
            }
            if (filmeMatch) { cinemaMatch = true; break; }
        }
        if (cinemaMatch) resultado.push_back(c);
    }
    return resultado;
}

vector<Cinema> Buscador::filtrarCinemaPorGenero(const vector<Cinema>& lista,
                                                const vector<string>& generos, bool op) {
    vector<Cinema> resultado;
    for (const Cinema& c : lista) {
        bool cinemaMatch = false;
        for (const string& id : c.getFilmesEmExibicao()) {
            const Filme* f = buscarFilmePorID(id);
            if (!f) continue;
            const vector<string>& gf = f->getGenero();
            bool filmeMatch = op;
            for (const string& g : generos) {
                bool tem = false;
                for (const string& gf2 : gf)
                    if (gf2 == g) { tem = true; break; }
                if (op) filmeMatch = filmeMatch && tem;
                else    filmeMatch = filmeMatch || tem;
            }
            if (filmeMatch) { cinemaMatch = true; break; }
        }
        if (cinemaMatch) resultado.push_back(c);
    }
    return resultado;
}

vector<Cinema> Buscador::filtrarCinemaPorDuracao(const vector<Cinema>& lista,
                                                 int mn, int mx) {
    vector<Cinema> resultado;
    for (const Cinema& c : lista) {
        bool match = false;
        for (const string& id : c.getFilmesEmExibicao()) {
            const Filme* f = buscarFilmePorID(id);
            if (!f) continue;
            int t = f->getTempoFilme();
            if (t > 0 && t >= mn && t <= mx) { match = true; break; }
        }
        if (match) resultado.push_back(c);
    }
    return resultado;
}

vector<Cinema> Buscador::filtrarCinemaPorAno(const vector<Cinema>& lista,
                                             int a1, int a2) {
    vector<Cinema> resultado;
    for (const Cinema& c : lista) {
        bool match = false;
        for (const string& id : c.getFilmesEmExibicao()) {
            const Filme* f = buscarFilmePorID(id);
            if (!f) continue;
            int ano = f->getAnoLancamento();
            if (ano > 0 && ano >= a1 && ano <= a2) { match = true; break; }
        }
        if (match) resultado.push_back(c);
    }
    return resultado;
}

// ── MENUS ─────────────────────────────────────────────────────────────────────

vector<Filme> Buscador::buscarFilmes() {
    vector<Filme> resultado(filmes);
    int opcao;
    do {
        cout << "\n=== FILTROS DE FILME ===\n"
             << "1. Por tipo\n2. Por genero\n3. Por duracao\n4. Por ano\n0. Concluir\n"
             << "Opcao: ";
        cin >> opcao;

        auto inicio = chrono::high_resolution_clock::now();

        if (opcao == 1) {
            int op, n; cout << "Operador (1=OU 2=E): "; cin >> op;
            cout << "Quantos tipos? "; cin >> n;
            vector<string> tipos(n);
            for (auto& t : tipos) { cout << "Tipo: "; cin >> t; }
            resultado = filtrarPorTipo(resultado, tipos, op == 2);

        } else if (opcao == 2) {
            int op, n; cout << "Operador (1=OU 2=E): "; cin >> op;
            cout << "Quantos generos? "; cin >> n;
            vector<string> gens(n);
            for (auto& g : gens) { cout << "Genero: "; cin >> g; }
            resultado = filtrarPorGenero(resultado, gens, op == 2);

        } else if (opcao == 3) {
            int mn, mx;
            cout << "Duracao minima (min): "; cin >> mn;
            cout << "Duracao maxima (min): "; cin >> mx;
            resultado = filtrarPorDuracao(resultado, mn, mx);

        } else if (opcao == 4) {
            int a1, a2;
            cout << "Ano inicial: "; cin >> a1;
            cout << "Ano final:   "; cin >> a2;
            resultado = filtrarPorAno(resultado, a1, a2);
        }

        if (opcao != 0) {
            auto fim = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> dur = fim - inicio;
            cout << "Resultados parciais: " << resultado.size()
                 << "  (" << dur.count() << " ms)\n";
        }
    } while (opcao != 0);
    return resultado;
}

vector<Cinema> Buscador::buscarCinemas() {
    vector<Cinema> resultado(cinemas);
    int opcao;
    do {
        cout << "\n=== FILTROS DE CINEMA ===\n"
             << "1. Por tipo de filme\n2. Por genero de filme\n"
             << "3. Por duracao de filme\n4. Por ano de filme\n"
             << "5. Por distancia\n6. Por preco\n7. Por titulo de filme\n0. Concluir\n"
             << "Opcao: ";
        cin >> opcao;

        auto inicio = chrono::high_resolution_clock::now();

        if (opcao == 1) {
            int op, n; cout << "Operador (1=OU 2=E): "; cin >> op;
            cout << "Quantos tipos? "; cin >> n;
            vector<string> tipos(n);
            for (auto& t : tipos) { cout << "Tipo: "; cin >> t; }
            resultado = filtrarCinemaPorTipo(resultado, tipos, op == 2);

        } else if (opcao == 2) {
            int op, n; cout << "Operador (1=OU 2=E): "; cin >> op;
            cout << "Quantos generos? "; cin >> n;
            vector<string> gens(n);
            for (auto& g : gens) { cout << "Genero: "; cin >> g; }
            resultado = filtrarCinemaPorGenero(resultado, gens, op == 2);

        } else if (opcao == 3) {
            int mn, mx;
            cout << "Duracao minima (min): "; cin >> mn;
            cout << "Duracao maxima (min): "; cin >> mx;
            resultado = filtrarCinemaPorDuracao(resultado, mn, mx);

        } else if (opcao == 4) {
            int a1, a2;
            cout << "Ano inicial: "; cin >> a1;
            cout << "Ano final:   "; cin >> a2;
            resultado = filtrarCinemaPorAno(resultado, a1, a2);

        } else if (opcao == 5) {
            int x, y; double dist;
            cout << "X: "; cin >> x;
            cout << "Y: "; cin >> y;
            cout << "Distancia maxima: "; cin >> dist;
            resultado = filtrarPorDistancia(resultado, x, y, dist);

        } else if (opcao == 6) {
            double pmax;
            cout << "Preco maximo: "; cin >> pmax;
            resultado = filtrarPorPreco(resultado, pmax);

        } else if (opcao == 7) {
            string titulo;
            cout << "Titulo do filme: ";
            cin.ignore();
            getline(cin, titulo);
            resultado = filtrarCinemaPorTitulo(resultado, titulo);
        }

        if (opcao != 0) {
            auto fim = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> dur = fim - inicio;
            cout << "Resultados parciais: " << resultado.size()
                 << "  (" << dur.count() << " ms)\n";
        }
    } while (opcao != 0);
    return resultado;
}