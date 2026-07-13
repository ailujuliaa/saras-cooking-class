#ifndef RECEITA_MISTA_H
#define RECEITA_MISTA_H

#include "Receita.h"

class ReceitaMista : public Receita
{
private: 
    string lugarGelado, lugarQuente, intensidade;
    int tempo;
    int tempoCongelamento;

public:
    ReceitaMista() : Receita(), lugarGelado("0"), lugarQuente("0"), intensidade("0"), tempo(0), tempoCongelamento(0) {
    }

	ReceitaMista(string nome, string lugarGelado, string lugarQuente, string intensidade, int tempo, int tempoCongelamento) : Receita(nome), lugarGelado(lugarGelado), lugarQuente(lugarQuente), intensidade(intensidade), tempo(tempo), tempoCongelamento(tempoCongelamento) {
    }

    string getLugarQuente () override {
        return lugarQuente;
    }

    void setLugarQuente(string lugarQuente) {
        this->lugarQuente = lugarQuente; 
    }

     string getLugarGelado () override {
        return lugarGelado;
    }

     void setLugarGelado(string lugarGelado) {
        this->lugarGelado = lugarGelado; 
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

    int getTempoCongelamento() override { 
        return tempoCongelamento; 
    }
    void setTempoCongelamento(int tempoCongelamento) { 
        this->tempoCongelamento = tempoCongelamento; 
    }

    int calcularTempo() override {
        return tempo + tempoCongelamento + calcularTempoEtapas();
    }

    string getTipo() const override {
        return "Mista";
    }
};
#endif