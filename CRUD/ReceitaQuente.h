#ifndef RECEITA_QUENTE_H
#define RECEITA_QUENTE_H

#include "Receita.h"

class ReceitaQuente : public Receita
{
private:
    string lugar;
    string intensidade;
    int tempo;

public:
    ReceitaQuente() : Receita(), lugar(""),  intensidade(""), tempo(0) {

    }

	ReceitaQuente (string nome, int tempoPreparo, string lugar, string intensidade, int tempo): Receita (nome, tempoPreparo), lugar (lugar), intensidade(intensidade), tempo(tempo) {

    }

    string getLugarQuente () override {
        return lugar;
    }

     void setLugar(string lugar) {
        this->lugar = lugar; 
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

    string getLugarGelado() override {
        return "";
    }

	int getTempoCongelamento() override {
		return 0;
	}
};
#endif