#include "Buscador.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <chrono>
using namespace std;

Buscador::Buscador(const vector<Filme>& f, const vector<Cinema>& c, const unordered_map<string, int>& idx)
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

        if (opcao != 0)
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
        cout << "0. Concluir" << endl;
        cout << "Opcao: ";
        cin >> opcao;

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

        if (opcao != 0)
            cout << "Resultados parciais: " << resultado.size() << endl;

    } while (opcao != 0);
    return resultado;
}