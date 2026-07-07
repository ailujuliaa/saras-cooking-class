#ifndef RECEITA_H
#define RECEITA_H

#include <string>
#include <vector>
#include "Ingrediente.h"
#include "EtapasDePreparo.h"

using namespace std;

class Receita {
protected:
	int id;
	string nome;
	string categoria;
	vector<etapaPreparo*> etapas;
	int tempoPreparo;
	vector<Ingrediente> ingrediente;
	string metodos_cozinha;
	

public:
	Receita():id(0), nome(""), categoria(""), tempoPreparo(0) {

	}

	Receita(int id, string nome, string categoria, string modoPreparo, int tempoPreparo)
		: id(id), nome(nome), categoria(categoria), tempoPreparo(tempoPreparo) {

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

	string getCategoria() const { 
		return categoria; 
	}
	void setCategoria(string categoria) {
		 this->categoria = categoria; 
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
	
	virtual int calcularTempo() = 0;
};
#endif;