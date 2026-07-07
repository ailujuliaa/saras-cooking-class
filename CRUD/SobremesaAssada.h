#ifndef SOBREMESA_ASSADA_H
#define SOBREMESA_ASSADA_H

#include "Receita.h"

class SobremesaAssada : public Receita
{
private:
	int tempoForno;
	int temperaturaForno;
	string tamanhoForma;

public:

	SobremesaAssada(): Receita(), tamanhoForma("20cm x 20cm") {
	
		}


	SobremesaAssada(int id, string nome, string categoria, string modoPreparo, int tempoPreparo, string tamanhoForma, int tempoAssar, int temperaturaForno)
		: Receita(), tamanhoForma(tamanhoForma), temperaturaForno(temperaturaForno), tempoForno(tempoForno) {
			setId(id);
			setNome(nome);
			setCategoria(categoria);
		    setTempoPreparo(tempoPreparo);
		}

	

	int calcularTempo() override {
		return tempoPreparo + tempoForno;
	}
};
#endif