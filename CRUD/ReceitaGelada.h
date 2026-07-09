#ifndef RECEITA_GELADA_H
#define RECEITA_GELADA_H

#include "Receita.h"

class ReceitaGelada : public Receita
{
private:
	int tempoCongelamento;

public:
	ReceitaGelada() : Receita(), tempoCongelamento(0) {
	}

	ReceitaGelada(int id, string nome, int tempoPreparo, int tempoCongelamento) : Receita(id, nome, tempoPreparo), tempoCongelamento(tempoCongelamento) {
	}

	int getTempoCongelamento() const { 
		return tempoCongelamento; 
	}
	void setTempoCongelamento(int tempoCongelamento) { 
		this->tempoCongelamento = tempoCongelamento; 
	}

	int calcularTempo() override {
		return tempoPreparo + tempoCongelamento + calcularTempoComponentes();
	}

	string getTipo() const override {
        return "Gelada";
    }
};
#endif