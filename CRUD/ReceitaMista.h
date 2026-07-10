#ifndef RECEITA_MISTA_H
#define RECEITA_MISTA_H

#include "Receita.h"

class ReceitaMista : public Receita
{
private:
    string intensidade;
    int tempo;
    int tempoCongelamento;

public:
    ReceitaMista() : Receita(), intensidade("0"), tempo(0), tempoCongelamento(0) {
        
    }

    ReceitaMista(string nome, int tempoPreparo, string intensidade, int tempo, int tempoCongelamento) : Receita(nome, tempoPreparo), intensidade(intensidade), tempo(tempo), tempoCongelamento(tempoCongelamento) {

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
        return tempoPreparo + tempo + tempoCongelamento + calcularTempoComponentes();
    }
    string getTipo() const override {
        return "Mista";
    }
};
#endif