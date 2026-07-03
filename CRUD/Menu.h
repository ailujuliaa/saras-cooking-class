#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <memory>
#include "GerenciadorDeReceitas.h"
#include "Receita.h"

using namespace std;

class Menu
{
private:
	GerenciadorDeReceitas gerenciadorDeReceitas;

public:
	void exibirMenuPrincipal() {
		
	}

	void exibirMenuCadastro() {
		
	}

	void exibirMenuBusca() {
		
	}

	void exibirMenuEdicao() {
		
	}

	void exibirMenuIngredientes() {
		
	}

	void exibirReceita(shared_ptr<Receita> receita) {
		
	}

	void exibirListaReceitas(vector<shared_ptr<Receita>> receitas) {
		
	}

	int lerOpcao() {
		return 0;
	}
};
#endif