#ifndef SOBREMESA_DE_COLHER_H
#define SOBREMESA_DE_COLHER_H

#include "Receita.h"

class SobremesaDeColher : public Receita
{
private:
	bool precisaIrAoFogao;
	int tempoFogao;
	string intensidadeFogo;

public:
	int fogao (bool precisaIrAoFogao, string intensidadeFogo, int tempoFogao) override{
	
		return tempoFogao;
	}
	
	SobremesaDeColher()
		: Receita(), precisaIrAoFogao(false), tempoFogao(0) {

		}

	SobremesaDeColher(int id, string nome, string categoria, string modoPreparo, int tempoPreparo, bool precisaRefrigerar, bool precisaIrAoFogao, int tempoFogao)
		: Receita(), precisaIrAoFogao(precisaIrAoFogao), tempoFogao(tempoFogao) {
			setNome(nome);
			setCategoria(categoria);
			setModoPreparo(modoPreparo);
		    setTempoPreparo(tempoPreparo);


		}

	bool getPrecisaIrAoFogao() const { 
		return precisaIrAoFogao; 
	}
	void setPrecisaIrAoFogao(bool precisaIrAoFogao) { 
		this->precisaIrAoFogao = precisaIrAoFogao; 
	}

	int getTempoNoFogao() const { 
		return tempoFogao; 
	}
	void setTempoFogao(int tempoFogao) { 
		this->tempoFogao = tempoFogao; 
	}

	int calcularTempo() override {
		return precisaIrAoFogao ? tempoPreparo + tempoFogao : tempoPreparo; 
	}
};
#endif