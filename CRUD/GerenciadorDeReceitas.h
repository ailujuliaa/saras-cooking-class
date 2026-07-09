#ifndef GERENCIADOR_DE_RECEITAS_H
#define GERENCIADOR_DE_RECEITAS_H

#include <string>
#include <vector>
#include <memory>
#include "Receita.h"
#include "Ingrediente.h"
#include "Etapa.h"

using namespace std;

class GerenciadorDeReceitas
{
private:
	string caminhoArquivo;
	vector<shared_ptr<Receita>> receitas;

public:
	bool criarReceita(shared_ptr<Receita> receita) {
		receitas.push_back(receita);
		return true;
	}

	shared_ptr<Receita> buscarPorId(int id) {
		for (int i = 0; i < receitas.size(); i++) {
        if (receitas[i]->getId() == id) {
            return receitas[i];
        }
    }
    return nullptr;
	}

	shared_ptr<Receita> buscarPorNome(string nome) {
		for (int i = 0; i < receitas.size(); i++) {
			if (receitas[i]->getNome() == nome) {
				return receitas[i];
			}
		}
    return nullptr;
	}

	vector<shared_ptr<Receita>> listarTodas() {
		return receitas; 
	}

	vector<shared_ptr<Receita>> listarPorTipo(string tipo) {
		vector<shared_ptr<Receita>> resultado;
		for (int i = 0; i < receitas.size(); i++) {
			if (receitas[i]->getTipo() == tipo) 
				resultado.push_back(receitas[i]);
		}
    return resultado;
	}

	bool atualizarReceita(int id, shared_ptr<Receita> novaReceita) {
		shared_ptr<Receita> receita = buscarPorId(id);
		if (receita == nullptr) return false;
		
		receita->setNome(novaReceita->getNome());
		receita->setTempoPreparo(novaReceita->getTempoPreparo());
		return true;

	}

	bool adicionarIngrediente(int idReceita, Ingrediente ingrediente) {
		shared_ptr<Receita> receita = buscarPorId(idReceita);
		if (receita == nullptr) return false;

		receita->adicionarIngrediente(ingrediente); 
		return true;

	}

	bool removerIngrediente(int idReceita, int idIngrediente) {
		shared_ptr<Receita> receita = buscarPorId(idReceita);
		if (receita == nullptr) return false;

		receita->removerIngrediente(idIngrediente);
		return true;
	}

	bool removerReceita(int idReceita) { //ta com erros!!
		shared_ptr<Receita> receita = buscarPorId(idReceita);
		if (receita == nullptr) return false;
		
		for (int i = 0; i < receitas.size(); i++) {
			if (receitas[i] == receita) {
				receitas.erase(receitas.begin() + i);
				return true;
			}
		}
	}

	bool adicionarEtapa(int idReceita, Etapa etapa){
		shared_ptr<Receita> receita = buscarPorId(idReceita);
		if (receita == nullptr) return false;

		receita->adicionarEtapa(etapa);
	}

	bool adicionarComponente(int idReceitaPrincipal, int idReceitaComponente) {
		return false; // idReceitaComponente != idReceitaPrincipal e o componente n pode criar ciclo (A usa B que usa A)
	}

	int gerarProximoId() {
		return 0; 
	}

	int gerarProximoIdIngrediente() {
		return 0; 
	}
};
#endif