#ifndef SOBREMESA_DE_COLHER_H
#define SOBREMESA_DE_COLHER_H

#include "Receita.h"

class SobremesaDeColher : public Receita
{
private:
	bool precisaRefrigerar;
	int tempoRefrigeracao;

public:
	SobremesaDeColher()
		: Receita(), precisaRefrigerar(false), tempoRefrigeracao(0) {

		}

	SobremesaDeColher(int id, string nome, string categoria, string modoPreparo, int tempoPreparo, bool precisaRefrigerar, int tempoRefrigeracao)
		: Receita(id, nome, categoria, modoPreparo, tempoPreparo), precisaRefrigerar(precisaRefrigerar), tempoRefrigeracao(tempoRefrigeracao) {

		}

	bool getPrecisaRefrigerar() const { 
		return precisaRefrigerar; 
	}
	void setPrecisaRefrigerar(bool precisaRefrigerar) { 
		this->precisaRefrigerar = precisaRefrigerar; 
	}

	int getTempoRefrigeracao() const { 
		return tempoRefrigeracao; 
	}
	void setTempoRefrigeracao(int tempoRefrigeracao) { 
		this->tempoRefrigeracao = tempoRefrigeracao; 
	}

	int calcularTempo() override {
		return precisaRefrigerar ? tempoPreparo + tempoRefrigeracao : tempoPreparo; 
	}
};
#endif