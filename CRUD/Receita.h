#ifndef RECEITA_H
#define RECEITA_H

#include <string>
#include <vector>
#include <memory> 

#include "Ingrediente.h"
#include "Etapa.h"

using namespace std;

class Receita {
protected:
	int id;
	string nome;
	int tempoPreparo;
	vector<Ingrediente> ingrediente;
	vector<Etapa> etapa;
	vector<shared_ptr<Receita>> componentes;

public:
	Receita():id(0), nome(""), tempoPreparo(0) {

	}

	Receita(int id, string nome, int tempoPreparo) : id(id), nome(nome), tempoPreparo(tempoPreparo) {

		}

	virtual ~Receita() {
	}

	int getId() const{ 
		return id; 
	}
	void setId(int id) { 
		this->id = id; 
	}

	string getNome() const { 
		return nome; 
	}
	void setNome(string nome) { 
		this->nome = nome; 
	}

	int getTempoPreparo() const { 
		return tempoPreparo; 
	}
	void setTempoPreparo(int tempoPreparo) { 
		this->tempoPreparo = tempoPreparo; 
	}

	vector<Ingrediente>& getIngredientes() { 
		return ingrediente; 
	}

	void adicionarIngrediente(Ingrediente novoIngrediente) {
		ingrediente.push_back(novoIngrediente);
	}

	void adicionarEtapa(etapaPreparo* novaEtapa) {
        etapas.push_back(novaEtapa);
	}

	bool removerIngrediente(int idIngrediente) {
		for (size_t i = 0; i < ingrediente.size(); i++) {
			if (ingrediente[i].getId() == idIngrediente) {
				ingrediente.erase(ingrediente.begin() + i);
				return true;
			}
		}
		return false;
	}

	vector<Etapa>& getEtapas() { 
		return etapa; 
	}
 
	void adicionarEtapa(Etapa novaEtapa) {
		etapa.push_back(novaEtapa);
	}
 
	vector<shared_ptr<Receita>>& getComponentes() { 
		return componentes; 
	}
 
	void adicionarComponente(shared_ptr<Receita> componente) {
		componentes.push_back(componente);
	}

	int calcularTempoComponentes() const {
		int total = 0;
		for (size_t i = 0; i < componentes.size(); i++) {
			total += componentes[i]->calcularTempo();
		}
		return total;
	}

	virtual int calcularTempo() = 0;
	virtual string getTipo() const = 0;
};
#endif;