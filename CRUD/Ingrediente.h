#pragma once
#ifndef INGREDIENTE_H
#define INGREDIENTE_H

#include <string>

using namespace std;

class Ingrediente
{
private:
	int id;
	string nome;
	//float quantidade;
	string unidade;

public:
	Ingrediente():id(0), nome(""), unidade("") {
	}

	Ingrediente(int id, string nome, string unidade) : id(id), nome(nome), unidade(unidade) {
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

	/*float getQuantidade() const { 
		return quantidade; 
	}
	void setQuantidade(float quantidade) { 
		this->quantidade = quantidade; 
	}*/

	string getUnidade() const { 
		return unidade; 
	}
	void setUnidade(string unidade) { 
		this->unidade = unidade; 
	}
};
#endif