#ifndef RECEITA_GELADA_H
#define RECEITA_GELADA_H

#include "Receita.h"

class ReceitaGelada : public Receita
{
private:
    int tempoCongelamento;
    string lugar;

public:
    ReceitaGelada() : Receita(),lugar(""), tempoCongelamento(0) {
    }

    ReceitaGelada(string nome, string lugar,  int tempoPreparo, int tempoCongelamento) : Receita(nome, tempoPreparo), lugar(lugar), tempoCongelamento(tempoCongelamento) {
    }

    string getLugarGelado() override { 
        return lugar; 
    }
    void setLugar() { 
        this->lugar = lugar; 
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
    string getLugarQuente() override {
        return "";
    }
};
#endif