#include "Filme.cc"
#include "Cinema.cc"
#include "LeitorDados.cc"
#include "Buscador.cc"
#include <iostream>
#include <chrono>
using namespace std;

int main() {
    LeitorDados leitor;
    leitor.lerDados();
    
    Buscador buscador(leitor.getFilmes(), leitor.getCinemas(), leitor.getIndice());

    int opcao;
    cout << "\nO que deseja buscar?" << endl;
    cout << "1. Filmes" << endl;
    cout << "2. Cinemas" << endl;
    cout << "Opcao: ";
    cin >> opcao;

    auto inicio = chrono::high_resolution_clock::now();

    if (opcao == 1) {
        vector<Filme> result = buscador.buscarFilmes();

    } else if (opcao == 2) {
        vector<Cinema> result = buscador.buscarCinemas();
    }

    return 0;
}