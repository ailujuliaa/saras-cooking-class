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

    ReceitaGelada(string nome, int tempoPreparo, int tempoCongelamento) : Receita(nome, tempoPreparo), tempoCongelamento(tempoCongelamento) {
    }

    int getTempoCongelamento() override { 
        return tempoCongelamento; 
    }
    void setTempoCongelamento(int tempoCongelamento) { 
        this->tempoCongelamento = tempoCongelamento; 
    }

    int calcularTempo() override {
        return tempoPreparo + tempoCongelamento + calcularTempoComponentes();
    }

	string getIntensidade () override {
		return "";
	}

	int getTempo () override {
		return 0;
	}

	string getTipo() const override {
        return "Gelada";
    }
};
#endif