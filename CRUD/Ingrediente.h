#ifndef INGREDIENTE_H
#define INGREDIENTE_H

#include <string>

using namespace std;

class Ingrediente
{
private:
	int id;
	string nome;
	string quantidade;

public:
	Ingrediente():id(0), nome(""), quantidade("") {
	}

	Ingrediente(int id, string nome, string quantidade) : id(id), nome(nome), quantidade(quantidade) {
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

	string getQuantidade() const { 
		return quantidade; 
	}
	void setQuantidade(string quantidade) { 
		this->quantidade = quantidade; 
	}
};
#endif