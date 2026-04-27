#include "Filme.h"
#include "Cinema.h"
#include "LeitorDados.h"
#include "Buscador.h"
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

int main() {
    LeitorDados leitor;
    leitor.lerDados();

    Buscador buscador(leitor.getFilmes(), leitor.getCinemas(), leitor.getIndice());

    int opcao;
    cout << "\nO que deseja buscar?" << endl;
    cout << "1. Filmes"  << endl;
    cout << "2. Cinemas" << endl;
    cout << "Opcao: ";
    cin >> opcao;

    auto inicio = chrono::high_resolution_clock::now();

    if (opcao == 1) {
        vector<Filme> resultado = buscador.buscarFilmes();

        auto fim = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracao = fim - inicio;

        cout << "\n--- Resultados: " << resultado.size() << " filme(s) encontrado(s) ---\n";
        for (const Filme& f : resultado) {
            cout << f.getID() << " | "
                 << f.getTituloPrimario() << " ("
                 << f.getAnoLancamento() << ")\n";
        }
        cout << "Tempo de busca: " << duracao.count() << " ms\n";

    } else if (opcao == 2) {
        vector<Cinema> resultado = buscador.buscarCinemas();

        auto fim = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracao = fim - inicio;

        cout << "\n--- Resultados: " << resultado.size() << " cinema(s) encontrado(s) ---\n";
        for (const Cinema& c : resultado) {
            cout << c.getID() << " | "
                 << c.getNomeCinema() << "\n";
        }
        cout << "Tempo de busca: " << duracao.count() << " ms\n";

    } else {
        cout << "Opcao invalida.\n";
    }

    return 0;
}