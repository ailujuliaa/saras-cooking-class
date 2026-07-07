#include <iostream>
#include <string>
#include <fstream>
#include "receitas.h"

using namespace std;

int main() {
    char name;
    cout << "Escolha uma opção: "
        << "1- Criar receita\n" 
        << "2- Ler receita\n" 
        << "3- Atualizar receita\n" 
        << "4- Procurar receita\n" 
        << "5- Excluir receita\n" 
        << "6- Sair" << endl;
        cin >> name;
        
        switch (name) {
            case '1':
                system.criar();
                break;
            case '2':
                system.ler();
                break;
            case '3':
                system.atualizar();
                break;
            case '4':
                system.procurar();
                break;
            case '5':
                system.excluir();
                break;
            case '6':
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    return 0;
}