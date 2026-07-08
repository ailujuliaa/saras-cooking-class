#ifndef RECEITA_MISTA_H
#define RECEITA_MISTA_H

#include "Receita.h"

class ReceitaMista : public Receita
{
private:
	int temperaturaForno;
	int tempoForno;
	int tempoCongelamento;

public:
	ReceitaMista() : Receita(), temperaturaForno(0), tempoForno(0), tempoCongelamento(0) {
		
	}

	ReceitaMista(int id, string nome, string categoria, int tempoPreparo, int temperaturaForno, int tempoForno, int tempoCongelamento) : Receita(id, nome, categoria, tempoPreparo), temperaturaForno(temperaturaForno), tempoForno(tempoForno), tempoCongelamento(tempoCongelamento) {

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

	int getTempoCongelamento() const { 
		return tempoCongelamento; 
	}
	void setTempoCongelamento(int tempoCongelamento) { 
		this->tempoCongelamento = tempoCongelamento; 
	}

	int calcularTempo() override {
		return tempoPreparo + tempoForno + tempoCongelamento + calcularTempoComponentes();
	}
};
#endif