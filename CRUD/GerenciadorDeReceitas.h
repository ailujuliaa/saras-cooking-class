#ifndef GERENCIADOR_DE_RECEITAS_H
#define GERENCIADOR_DE_RECEITAS_H

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

#include "Receita.h"
#include "ReceitaQuente.h"
#include "ReceitaGelada.h"
#include "ReceitaMista.h"
#include "Ingrediente.h"
#include "Etapa.h"

using namespace std;

class GerenciadorDeReceitas
{
private:
	string caminhoReceitas;
	vector<shared_ptr<Receita>> receitas;

public:

	void salvarArquivo(){
		fstream arquivo;
		arquivo.open("caminhoReceitas.txt", ios_base::out);
		if (! arquivo.is_open()) {
			cout << "Erro ao abrir arquivo." << endl;
			return;
		}

		for (int i=0; i < receitas.size(); i++){
			string tipo = receitas[i]->getTipo();

			arquivo << receitas[i]->getTipo() << ";" << receitas[i]->getNome() << ";" << receitas[i]->getTempoPreparo();
			if (tipo == "Quente") {
				arquivo << ";" << receitas[i]->getIntensidade() << ";" << receitas[i]->getTempo();
			}
			else if (tipo == "Gelada") {
				arquivo << ";" << receitas[i]->getTempoCongelamento();
			}
			else if (tipo == "Mista") {
				arquivo << ";" << receitas[i]->getIntensidade() << ";" << receitas[i]->getTempo() << ";" << receitas[i]->getTempoCongelamento();
			}

			arquivo <<"\n";
			vector<Ingrediente>& ingredientes = receitas[i]->getIngredientes();
			for (int j = 0; j < ingredientes.size(); j++) {
				if (j > 0) arquivo << ";";
				arquivo << ingredientes[j].getId() << ":" << ingredientes[j].getNome() << ":"
						<< ingredientes[j].getQuantidade() << ":" << ingredientes[j].getUnidade();
			}

			arquivo << "\n";
			vector<Etapa>& etapas = receitas[i]->getEtapas();
			for (int j = 0; j < etapas.size(); j++) {
				if (j > 0) arquivo << ",";
				arquivo << etapas[j].getAcao() << ":" << etapas[j].getTempo() << ":" << etapas[j].getRecipiente();
			}

			arquivo << "\n\n";
		}
		arquivo.close();
	}
	
	void lerArquivo() {
		fstream arquivo;
		arquivo.open("caminhoReceitas.txt", ios_base::in);

		if (!arquivo.is_open()) {
			cout << "Erro ao abrir arquivo." << endl;
			return;
		}

		string linha;
		while (getline(arquivo, linha)) {
			if (linha.empty()) continue;
			stringstream ss(linha);
			string tipo, nome, strTempoPreparo;
			getline(ss, tipo, ';');
			getline(ss, nome, ';');
			getline(ss, strTempoPreparo, ';');

			int tempoPreparo = stoi(strTempoPreparo);
			shared_ptr<Receita> receita;

			if (tipo == "Quente") {
				string intensidade, strTempo;
				getline(ss, intensidade, ';');
				getline(ss, strTempo, ';');
				int tempo = stoi(strTempo);
				receita = shared_ptr<Receita>(new ReceitaQuente(nome, tempoPreparo, intensidade, tempo));
			}
			else if (tipo == "Gelada") {
				string strTempoCongelamento;
				getline(ss, strTempoCongelamento, ';');
				int tempoCongelamento = stoi(strTempoCongelamento);
				receita = shared_ptr<Receita>(new ReceitaGelada(nome, tempoPreparo, tempoCongelamento));

			}
			else if (tipo == "Mista") {
				string intensidade, strTempo, strTempoCongelamento;

				getline(ss, intensidade, ';');
				getline(ss, strTempo, ';');
				getline(ss, strTempoCongelamento, ';');
				int tempo = stoi(strTempo);
				int tempoCongelamento = stoi(strTempoCongelamento);
				receita = shared_ptr<Receita>(new ReceitaMista(nome, tempoPreparo, intensidade, tempo, tempoCongelamento));
			}

			getline(arquivo, linha);

			stringstream ssIng(linha);
			string ingredienteStr;

			while (getline(ssIng, ingredienteStr, ';')) {
				stringstream dadosIng(ingredienteStr);
				string idStr, nomeIng, qtdStr, unidade;

				getline(dadosIng, idStr, ':');
				getline(dadosIng, nomeIng, ':');
				getline(dadosIng, qtdStr, ':');
				getline(dadosIng, unidade, ':');
				int id = stoi(idStr);
				float qtd = stof(qtdStr);

				Ingrediente ingrediente(id, nomeIng, qtd, unidade);
				receita->adicionarIngrediente(ingrediente);
			}

			getline(arquivo, linha);

			stringstream ssEtapas(linha);
			string etapaStr;

			while (getline(ssEtapas, etapaStr, ',')) {

				stringstream dadosEtapa(etapaStr);
				string acao, tempoStr, recipiente;

				getline(dadosEtapa, acao, ':');
				getline(dadosEtapa, tempoStr, ':');
				getline(dadosEtapa, recipiente, ':');
				int tempo = stoi(tempoStr);

				Etapa etapa(acao,tempo,recipiente);
				receita->adicionarEtapa(etapa);
			}
			getline(arquivo, linha);
			criarReceita(receita);
		}

		arquivo.close();
	}
		
	bool criarReceita(shared_ptr<Receita> receita) {
		receita->setId(gerarProximoId());
		receitas.push_back(receita);
		return true;
	}

	shared_ptr<Receita> buscarPorNome(string nome) {
		for (int i = 0; i < receitas.size(); i++) {
			if (receitas[i]->getNome() == nome) {
				return receitas[i];
			}
		}
    return nullptr;
	}

	vector<shared_ptr<Receita>> listarTodas() {
		return receitas; 
	}

	vector<shared_ptr<Receita>> listarPorNome(string nome) { 
		vector<shared_ptr<Receita>> resultado;
		for (int i = 0; i < receitas.size(); i++) {
			if (receitas[i]->getNome() == nome) 
				resultado.push_back(receitas[i]);
		}
    return resultado;
	}

	bool atualizarReceita(string nome, shared_ptr<Receita> novaReceita) {
		shared_ptr<Receita> receita = buscarPorNome(nome);
		if (receita == nullptr) return false;
		
		receita->setNome(novaReceita->getNome());
		receita->setTempoPreparo(novaReceita->getTempoPreparo());
		return true;

	}

	bool adicionarIngrediente(string nome, Ingrediente ingrediente) {
		shared_ptr<Receita> receita = buscarPorNome(nome);
		if (receita == nullptr) return false;

		ingrediente.setId(gerarProximoIdIngrediente());
		receita->adicionarIngrediente(ingrediente); 
		return true;

	}

	bool removerIngrediente(string nome, int idIngrediente) {//por nome
		shared_ptr<Receita> receita = buscarPorNome(nome);
		if (receita == nullptr) return false;

		receita->removerIngrediente(idIngrediente);
		return true;
	}

	bool removerReceita(string nome) {
		shared_ptr<Receita> receita = buscarPorNome(nome);
		if (receita == nullptr) return false;
		
		for (int i = 0; i < receitas.size(); i++) {
			if (receitas[i] == receita) {
				receitas.erase(receitas.begin() + i);
				return true;
			}
		}
		return false;
	}

	bool adicionarEtapa(string nome, Etapa etapa){
		shared_ptr<Receita> receita = buscarPorNome(nome);
		if (receita == nullptr) return false;

		receita->adicionarEtapa(etapa);
		return true;
	}

	bool adicionarComponente(string nomePrincipal, string nomeComponente) {
		if (nomePrincipal == nomeComponente) return false;

		shared_ptr<Receita> principal = buscarPorNome(nomePrincipal);
		shared_ptr<Receita> componente = buscarPorNome(nomeComponente);

		if (principal == nullptr || componente == nullptr) return false;

		if (formaCiclo(componente, nomePrincipal)) return false;

		principal->adicionarComponente(componente);
		return true;
	}
	
	bool formaCiclo(shared_ptr<Receita> receita, string nomeAlvo) {
    vector<shared_ptr<Receita>>& componentes = receita->getComponentes();
    for (int i = 0; i < componentes.size(); i++) {
        if (componentes[i]->getNome() == nomeAlvo) return true;
        if (formaCiclo(componentes[i], nomeAlvo)) return true;
    }
    return false;
}

	int gerarProximoId() {
		int maiorId = 0;
		for (int i = 0; i < receitas.size(); i++) {
			if (receitas[i]->getId() > maiorId) {
				maiorId = receitas[i]->getId();
			}
		}
		return maiorId + 1;	
	}

	int gerarProximoIdIngrediente() {
		int maiorId = 0;
		for (int i = 0; i < receitas.size(); i++) {
			vector<Ingrediente>& ingredientes = receitas[i]->getIngredientes();
			for (int j = 0; j < ingredientes.size(); j++) {
				if (ingredientes[j].getId() > maiorId) {
					maiorId = ingredientes[j].getId();
				}
			}
		}
		return maiorId + 1;
	}
};
#endif
