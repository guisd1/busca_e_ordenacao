#include "Filme.cc"
#include "Cinema.cc"
#include "LeitorDados.cc"
#include <iostream>
#include <chrono>
using namespace std;

int main() {
    LeitorDados leitor;
    leitor.lerDados();

    cout << "\nO que deseja buscar?" << endl;
    cout << "1. Filmes" << endl;
    cout << "2. Cinemas" << endl;
    cout << "Opcao: ";
    int opcao; cin >> opcao;

    cout << "Opcao invalida." << endl;
    return 0;
}