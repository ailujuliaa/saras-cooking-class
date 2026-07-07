#include <string>
#include <vector>
using namespace std;

class etapaPreparo {
	public:
		virtual ~etapaPreparo() {}
		virtual int tempo() = 0;
		virtual string descricao() = 0;
	};


class assar: public etapaPreparo{
	private:
		int tempoAssar;
		int temperatura;
		string descricao;

	public:
		assar(int tempoAssar, int temperatura) : tempoAssar(tempoAssar), temperatura(temperatura) {}
		int tempo() override {
			return tempoAssar;
		}
		string descricao() override {
			return "Assar por " + to_string(tempoAssar) + " minutos a " + to_string(temperatura) + " graus.";
		}
	};

class refrigerar: public etapaPreparo{
	private:
		bool geladeiraOuFreezer;
		int tempoRefrigeracao;
		string descricao;
	public:
		refrigerar(bool geladeiraOuFreezer, int tempoRefrigeracao, string descricao) 
		: geladeiraOuFreezer(geladeiraOuFreezer), tempoRefrigeracao(tempoRefrigeracao),
		 descricao(descricao) {}

		int tempo() override {
			return tempoRefrigeracao;
		}
		string descricao() override {
			return descricao;
		}

	};

class fogao: public etapaPreparo{
	private:
		bool precisaMexer;
		string intensidadeFogo;
		int tempoFogao;

	public:
		fogao(bool precisaMexer, string intensidadeFogo, int tempoFogao) 
		:precisaMexer(precisaMexer), intensidadeFogo(intensidadeFogo), tempoFogao(tempoFogao) {}

		int tempo() override {
			return tempoFogao;
		}
		string descricao() override {
			return "Cozinhar no fogão por " + to_string(tempoFogao) + " minutos em fogo " + intensidadeFogo + (precisaMexer ? ", mexendo ocasionalmente." : ".");
		}
	};

class bater: public etapaPreparo{
	private:
		string utensilioBater;
		string intensidade;
		int tempoBater;

	public:
		bater(string utensilio, int tempoBater, string intensidadeBater) 
		: utensilioBater(utensilio), intensidade(intensidadeBater), tempoBater(tempoBater) {}

		int tempo() override {
			return tempoBater;
		}
		string descricao() override {
			return "Bater com " + utensilioBater + " por " + to_string(tempoBater) + " minutos em intensidade " + intensidade + ".";
		}

	};

class fritar: public etapaPreparo {
	private:
		int tempoFritar;

	public:
		fritar(int tempoFritar) : tempoFritar(tempoFritar) {}

		int tempo() override {
			return tempoFritar;
		}
		string descricao() override {
			return "Fritar por " + to_string(tempoFritar) + " minutos.";
		}

	};