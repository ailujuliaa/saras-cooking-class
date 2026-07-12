#include <iostream>
#include <string>
#include "Receita.h"
#include "Menu.h"
#include "GerenciadorDeReceitas.h"

int main (){
    GerenciadorDeReceitas gerenciadorMain;
    gerenciadorMain.lerArquivo();
    Menu menu;
    menu.exibirMenuPrincipal(gerenciadorMain);
	return 0;
}