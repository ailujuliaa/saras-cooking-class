#ifndef SOBREMESA_ASSADA_H
#define SOBREMESA_ASSADA_H

#include "Receita.h"

class SobremesaAssada : public Receita
{
private:
	int temperaturaForno;
	int tempoForno;

public:
	SobremesaAssada(): Receita(), temperaturaForno(0), tempoForno(0) {

		}

	SobremesaAssada(int id, string nome, string categoria, string modoPreparo, int tempoPreparo, int temperaturaForno, int tempoForno)
		: Receita(id, nome, categoria, modoPreparo, tempoPreparo), temperaturaForno(temperaturaForno), tempoForno(tempoForno) {}

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
		return tempoPreparo + tempoForno;
	}
};
#endif