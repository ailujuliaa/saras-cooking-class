#ifndef RECEITA_FORNO_H
#define RECEITA_FORNO_H

#include "Receita.h"

class ReceitaForno : public Receita
{
private:
	int temperaturaForno;
	int tempoForno;

public:
	ReceitaForno() : Receita(), temperaturaForno(0), tempoForno(0) {

	}

	ReceitaForno (string nome, int tempoPreparo, int temperaturaForno, int tempoForno)	: Receita (nome, tempoPreparo), temperaturaForno(temperaturaForno), tempoForno(tempoForno) {

	}

	int getTemperaturaForno() const { 
		return temperaturaForno; 
	}
	void setTemperaturaForno(int temperaturaForno) {
		this->temperaturaForno = temperaturaForno; 
	}

	int getTempoForno() const { 
		return tempoForno; 
	}
	void setTempoForno(int tempoForno) { 
		this->tempoForno = tempoForno; 
	}

	int calcularTempo() override {
		return tempoPreparo + tempoForno + calcularTempoComponentes();
	}
	string getTipo() const override {
        return "Forno";
    }
};
#endif