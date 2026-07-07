#ifndef SOBREMESA_GELADA_H
#define SOBREMESA_GELADA_H

#include "Receita.h"

class SobremesaGelada : public Receita
{
private:
	bool precisaMaquinaDeSorvete;
	bool precisaRefrigerar;
	int tempoCongelamento;

public:
	SobremesaGelada() : Receita(), precisaMaquinaDeSorvete(false), precisaRefrigerar(false), tempoCongelamento(0) {

	}

	SobremesaGelada(int id, string nome, string categoria, string modoPreparo, int tempoPreparo, bool precisaMaquinaDeSorvete, bool precisaRefrigerar, int tempoCongelamento)
		: Receita(id, nome, categoria, modoPreparo, tempoPreparo),
		  precisaMaquinaDeSorvete(precisaMaquinaDeSorvete),
		  precisaRefrigerar(precisaRefrigerar),
		  tempoCongelamento(tempoCongelamento) {

		  }

	bool getPrecisaRefrigerar() const {
		 return precisaRefrigerar; 
		}	

	void setPrecisaRefrigerar(bool precisaRefrigerar) {
		 this->precisaRefrigerar = precisaRefrigerar; 
		}

	bool getPrecisaMaquinaDeSorvete() const {
		 return precisaMaquinaDeSorvete; 
		}
	void setPrecisaMaquinaDeSorvete(bool precisaMaquinaDeSorvete) {
		 this->precisaMaquinaDeSorvete = precisaMaquinaDeSorvete; 
		}

	int getTempoCongelamento() const { 
		return tempoCongelamento; 
	}
	void setTempoCongelamento(int tempoCongelamento) { 
		this->tempoCongelamento = tempoCongelamento; 
	}

	int calcularTempo() override {
		return tempoPreparo + tempoCongelamento; 
	}
};
#endif