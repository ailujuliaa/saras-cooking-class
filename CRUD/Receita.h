#ifndef RECEITA_H
#define RECEITA_H

#include <string>
#include <vector>
#include "Ingrediente.h"

using namespace std;

class Receita
{
protected:
	int id;
	string nome;
	string categoria;
	string modoPreparo;
	int tempoPreparo;
	vector<Ingrediente> ingrediente;

public:
	Receita():id(0), nome(""), categoria(""), modoPreparo(""), tempoPreparo(0) {

	}

	Receita(int id, string nome, string categoria, string modoPreparo, int tempoPreparo)
		: id(id), nome(nome), categoria(categoria), modoPreparo(modoPreparo), tempoPreparo(tempoPreparo) {

		}

	virtual ~Receita() {

	}

	int getId() const { 
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

	string getModoPreparo() const { 
		return modoPreparo; 
	}
	void setModoPreparo(string modoPreparo) { 
		this->modoPreparo = modoPreparo; 
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
#endif