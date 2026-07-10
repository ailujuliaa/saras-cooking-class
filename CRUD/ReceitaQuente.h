#ifndef RECEITA_FORNO_H
#define RECEITA_FORNO_H

#include "Receita.h"

class ReceitaQuente : public Receita
{
private:
	string intensidade;
	int tempo;

public:
	ReceitaQuente() : Receita(), intensidade(""), tempo(0) {

	}

	ReceitaQuente (string nome, int tempoPreparo, string intensidade, int tempo): Receita (nome, tempoPreparo), intensidade(intensidade), tempo(tempo) {

	}

	string getIntensidade() override { 
		return intensidade; 
	}
	void setIntensidade(string intensidade) {
		this->intensidade = intensidade; 
	}

	int getTempo() override { 
		return tempo; 
	}
	void setTempo(int tempo) { 
		this->tempo = tempo; 
	}

	int calcularTempo() override {
		return tempoPreparo + tempo + calcularTempoComponentes();
	}
	string getTipo() const override {
        return "Quente";
    }
	int getTempoCongelamento() override {
		return 0;
	}
};
#endif