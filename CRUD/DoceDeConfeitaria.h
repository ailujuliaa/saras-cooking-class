#ifndef DOCE_DE_CONFEITARIA_H
#define DOCE_DE_CONFEITARIA_H

#include "Receita.h"

class DoceDeConfeitaria : public Receita
{
private:
	bool precisaEmbalagem;
	int rendimento;

public:
	DoceDeConfeitaria() : Receita(), precisaEmbalagem(false), rendimento(0) {

	}

	DoceDeConfeitaria(int id, string nome, string categoria, string modoPreparo, int tempoPreparo, bool precisaEmbalagem, int rendimento)
		: Receita(id, nome, categoria, modoPreparo, tempoPreparo), precisaEmbalagem(precisaEmbalagem), rendimento(rendimento) {

		}

	bool getPrecisaEmbalagem() const { 
		return precisaEmbalagem; 
	}
	void setPrecisaEmbalagem(bool precisaEmbalagem) {
		this->precisaEmbalagem = precisaEmbalagem; 
		}

	int getRendimento() const {
		return rendimento; 
	}
	void setRendimento(int rendimento) { 
		this->rendimento = rendimento; 
	}

	int calcularTempo() override {
		return tempoPreparo;
	}
};
#endif