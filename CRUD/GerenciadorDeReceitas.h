#ifndef GERENCIADOR_DE_RECEITAS_H
#define GERENCIADOR_DE_RECEITAS_H

#include <string>
#include <vector>
#include <memory>
#include "RepositorioReceitas.h"
#include "Receita.h"
#include "Ingrediente.h"

using namespace std;

class GerenciadorDeReceitas
{
private:
	RepositorioReceitas repositorioReceitas;

public:
	bool criarReceita(shared_ptr<Receita> receita) {
		return false; 
	}

	shared_ptr<Receita> buscarPorId(int id) {
		return nullptr;
	}

	shared_ptr<Receita> buscarPorNome(string nome) {
		return nullptr; 
	}

	vector<shared_ptr<Receita>> listarTodas() {
		return vector<shared_ptr<Receita>>(); 
	}

	vector<shared_ptr<Receita>> listarPorCategoria(string categoria) {
		return vector<shared_ptr<Receita>>(); 
	}

	bool atualizarReceita(int id, shared_ptr<Receita> receita) {
		return false; 
	}

	bool adicionarIngrediente(int idReceita, Ingrediente ingrediente) {
		return false; 
	}

	bool removerIngrediente(int idReceita, int idIngrediente) {
		return false; 
	}

	bool removerReceita(int id) {
		return false; 
	}

	int gerarProximoId() {
		return 0; 
	}

	int gerarProximoIdIngrediente() {
		return 0; 
	}
};
#endif