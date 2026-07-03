#ifndef BEBIDA_DOCE_H
#define BEBIDA_DOCE_H

#include "Receita.h"

class BebidaDoce : public Receita
{
private:
	bool precisaLiquidificador;
	bool servidaGelada;
	float volume;

public:
	BebidaDoce():Receita(), precisaLiquidificador(false), servidaGelada(false), volume(0.0f) {

	}

	BebidaDoce(int id, string nome, string categoria, string modoPreparo, int tempoPreparo, bool precisaLiquidificador, bool servidaGelada, float volume)
		: Receita(id, nome, categoria, modoPreparo, tempoPreparo), precisaLiquidificador(precisaLiquidificador), servidaGelada(servidaGelada), volume(volume) {

		}

	bool getPrecisaLiquidificador() const { 
		return precisaLiquidificador; 
	}
	void setPrecisaLiquidificador(bool precisaLiquidificador) { 
		this->precisaLiquidificador = precisaLiquidificador; 
	}

	bool getServidaGelada() const { 
		return servidaGelada; 
	}
	void setServidaGelada(bool servidaGelada) { 
		this->servidaGelada = servidaGelada; 
	}

	float getVolume() const { 
		return volume; 
	}
	void setVolume(float volume) { 
		this->volume = volume; 
	}

	int calcularTempo() override {
		return tempoPreparo; 
	}
};
#endif