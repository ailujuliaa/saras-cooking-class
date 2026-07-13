#include <iostream>
#include <string>
#include <cstdlib>
#include "Receita.h"
#include "Menu.h"
#include "GerenciadorDeReceitas.h"

int main (){
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    GerenciadorDeReceitas gerenciadorMain;
    gerenciadorMain.lerArquivo();

    Menu menu;
    menu.exibirMenuPrincipal(gerenciadorMain);
    
	return 0;
}