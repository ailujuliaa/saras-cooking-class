#ifndef ETAPA_H
#define ETAPA_H

#include <string>
#include <iostream>

using namespace std;

class Etapa
{
private:
	string acao;
	int tempo;
	string recipiente;

public:
	Etapa() : acao(""), tempo(0), recipiente("") {

    }

	Etapa(string acao, int tempo, string recipiente) : acao(acao), tempo(tempo), recipiente(recipiente) {

    }

	string getAcao() const { 
        return acao; 
    }
	void setAcao(string acao) { 
        this->acao = acao; 
    }

	int getTempo() const { 
        return tempo; 
    }
	void setTempo(int tempo) { 
        if (tempo > 0)
            this->tempo = tempo; 
        else cout << "Tempo Inválido" << endl;
    }

	string getRecipiente() const { 
        return recipiente; 
    }
	void setRecipiente(string recipiente) { 
        this->recipiente = recipiente; 
    }
};
#endif
