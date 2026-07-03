#ifndef REPOSITORIO_RECEITAS_H
#define REPOSITORIO_RECEITAS_H

#include <string>
#include <vector>
#include <memory>
#include "Receita.h"

using namespace std;

class RepositorioReceitas
{
private:
	string caminhoArquivo;

public:
	bool abrirArquivo(string modo) {
		return false; 
	}

	void fecharArquivo() {

	}

	bool salvarReceita() {
		return false; 
	}

	shared_ptr<Receita> lerReceita(int id) {
		return nullptr; 
	}

	vector<shared_ptr<Receita>> lerTodas() {
		return vector<shared_ptr<Receita>>();
	}

	bool atualizarArquivo(int id, shared_ptr<Receita> receita) {
		return false;
	}

	bool removerArquivo(int id) {
		return false; 
	}

	int contarRegistros() {
		return 0; 
	}
};
#endif