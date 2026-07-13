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
	Receita(): nome("") {

	}

	Receita(string nome) : nome(nome) {

	}

	virtual ~Receita() {
	}

	void setId(int id) {
		this->id = id;
	}

	int getId() const{ 
		return id; 
	}


	string getNome() const { 
		return nome; 
	}
	void setNome(string nome) { 
		this->nome = nome; 
	}

	vector<Ingrediente>& getIngredientes() { 
		return ingrediente; 
	}

	
	void adicionarIngrediente(Ingrediente novoIngrediente) {
		ingrediente.push_back(novoIngrediente);
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

	bool removerEtapa(int num) {
		if (num >= 0 && num < etapa.size()) {
            
            etapa.erase(etapa.begin() + num);
            return true;
        }
		return false;
	}
 
	vector<shared_ptr<Receita>>& getComponentes() { 
		return componentes; 
	}
 
	void adicionarComponente(shared_ptr<Receita> componente) {
		componentes.push_back(componente);
	}

	int calcularTempoEtapas() const {
		int total = 0;
		for (size_t i = 0; i < etapa.size(); i++) {
			total += etapa[i].getTempo();
		}
		return total;
	}

	virtual string getLugarGelado () = 0;
	virtual string getLugarQuente() = 0;
	virtual int calcularTempo() = 0;
	virtual string getTipo() const = 0;
	virtual string getIntensidade() = 0;
	virtual int getTempo() = 0;
	virtual int getTempoCongelamento() = 0;
	
};
#endif