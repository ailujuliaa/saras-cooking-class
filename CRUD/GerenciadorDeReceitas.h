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
		cout << "Quantidade de receitas na memoria: " << receitas.size() << endl;
		fstream arquivo;
		arquivo.open("caminhoReceitas.txt", ios_base::out);
		if (! arquivo.is_open()) {
			cout << "Erro ao abrir arquivo." << endl;
			return;
		}

		for (int i=0; i < receitas.size(); i++){
			string tipo = receitas[i]->getTipo();

			arquivo << receitas[i]->getTipo() << ";" << receitas[i]->getNome() << ";" << receitas[i]->calcularTempo();
			if (tipo == "Quente") {
				arquivo << ";" << receitas[i]->getLugarQuente() << ";" << receitas[i]->getIntensidade() << ";" << receitas[i]->getTempo();
			}
			else if (tipo == "Gelada") {
				arquivo << ";" <<  receitas[i]->getLugarGelado() << ";" << receitas[i]->getTempoCongelamento();
			}
			else if (tipo == "Mista") {
				arquivo << ";" << receitas[i]->getLugarGelado() << ";" << receitas[i]->getLugarQuente() << ";"<< receitas[i]->getIntensidade() << ";" << receitas[i]->getTempo() << ";" << receitas[i]->getTempoCongelamento();
			}

			arquivo <<"\n";
			vector<Ingrediente>& ingredientes = receitas[i]->getIngredientes();
			for (int j = 0; j < ingredientes.size(); j++) {
				if (j > 0) {
					arquivo << ";";
				}
				arquivo << ingredientes[j].getId() << ":" << ingredientes[j].getNome() << ":"
						<< /*ingredientes[j].getQuantidade() << ":" << */ ingredientes[j].getUnidade();
			}

			arquivo << "\n";
			vector<Etapa>& etapas = receitas[i]->getEtapas();
			for (int j = 0; j < etapas.size(); j++) {
				if (j > 0){ 
					arquivo << ",";
				}
				arquivo << etapas[j].getAcao() << ":" << etapas[j].getTempo() << ":" << etapas[j].getRecipiente();
			}

			arquivo << "\n\n";
		}
		arquivo.close();
	}
	
	void lerArquivo() {
		receitas.clear();
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
				string intensidade, strTempo, lugar;
				getline(ss, lugar, ';');
				getline(ss, intensidade, ';');
				getline(ss, strTempo, ';');
				int tempo = stoi(strTempo);
				receita = shared_ptr<Receita>(new ReceitaQuente(nome, lugar, intensidade, tempo));
			}
			else if (tipo == "Gelada") {
				string strTempoCongelamento, lugar;
				getline(ss, lugar, ';');
				getline(ss, strTempoCongelamento, ';');
				int tempoCongelamento = stoi(strTempoCongelamento);
				receita = shared_ptr<Receita>(new ReceitaGelada(nome, lugar, tempoCongelamento));

			}
			else if (tipo == "Mista") {
				string intensidade, strTempo, strTempoCongelamento, lugarGelado, lugarQuente;

				getline(ss, lugarGelado, ';');
				getline(ss, lugarQuente, ';');
				getline(ss, intensidade, ';');
				getline(ss, strTempo, ';');
				getline(ss, strTempoCongelamento, ';');
				int tempo = stoi(strTempo);
				int tempoCongelamento = stoi(strTempoCongelamento);
				receita = shared_ptr<Receita>(new ReceitaMista(nome, lugarGelado, lugarQuente, intensidade, tempo, tempoCongelamento));
			
			}
			
			getline(arquivo, linha);

			stringstream ssIng(linha);
			string ingredienteStr;

			while (getline(ssIng, ingredienteStr, ';')) {
				stringstream dadosIng(ingredienteStr);
				string idStr, nomeIng, unidade;

				getline(dadosIng, idStr, ':');
				getline(dadosIng, nomeIng, ':');
				//getline(dadosIng, qtdStr, ':');
				getline(dadosIng, unidade, ':');
				int id = stoi(idStr);
				//float qtd = stof(qtdStr);

				Ingrediente ingrediente(id, nomeIng, unidade);
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

	void listarReceitas(bool a = false){
		if (receitas.empty()){
        cout << "Nenhuma receita foi carregada do arquivo." << endl;
        return;
    	}
    	cout << "--- Receitas Disponíveis ---" << endl;
    	for (int i = 0; i < receitas.size(); i++) {
			if (a){
        	cout << i + 1 << " - ";
			printarReceita(receitas[i]);
			}
			else {
				cout << i + 1 << " - " << receitas[i]->getNome() << "\n";
			}
    	}
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

	/*vector<shared_ptr<Receita>> listarTodas() {
		return receitas; 
	}*/

	vector<shared_ptr<Receita>> listarPorNome(string nome) { 
		vector<shared_ptr<Receita>> resultado;
		for (int i = 0; i < receitas.size(); i++) {
			if (receitas[i]->getNome() == nome) 
				resultado.push_back(receitas[i]);
		}
    return resultado;
	}

	void printarReceita(shared_ptr<Receita> receita){
		int j = 0;
		bool p = 0;
		string lugarQuente, lugarquente = "", descricao = "";
		cout << receita->getNome() << "\n\n" << receita->getTipo() 
		<< "\nTempo de Preparo: " << receita->calcularTempo() << "minutos\n\nIgredientes:\n" <<endl;
		for(int i = 0; i < receita->getIngredientes().size(); i++){
			cout << receita->getIngredientes()[i].getUnidade() << " de " << receita->getIngredientes()[i].getNome()<<endl;
		}

		cout << "\nEtapas:\n" << endl;

		while (p == 0 && j < receita->getEtapas().size()) {

   			 string recipienteAtual = receita->getEtapas()[j].getRecipiente();

    		if (!recipienteAtual.empty() && recipienteAtual.back() == '~') {
        	recipienteAtual.pop_back();
        	p = true;
    	}

    	cout << "*" << receita->getEtapas()[j].getAcao()
         << " em um(a) " << recipienteAtual
         << " por " << receita->getEtapas()[j].getTempo()
         << " minutos\n";

    	j++;

    	if (p)
        break;
}

	
		if (receita->getTipo() == "Quente") {
			lugarQuente = receita->getLugarQuente();
			size_t posicao = lugarQuente.find("~");
			if (posicao != string::npos) {

    		lugarquente = lugarQuente.substr(0, posicao); 
    
    		descricao = lugarQuente.substr(posicao + 1);

			cout << "*" << lugarquente <<" "<< receita->getIntensidade() 
			<< " por aproximadamente " << receita->getTempo() << " minutos "<< descricao << endl;

			}
		}
			else if (receita->getTipo() == "Gelada") {
				cout <<"*"<< "Levar à(o) " << receita->getLugarGelado() << " por aproximadamente " 
			    << receita->getTempoCongelamento() <<" minutos"<< endl;

			}
			
			else if (receita->getTipo() == "Mista") {
			
			lugarQuente = receita->getLugarQuente();
			size_t posicao = lugarQuente.find("~");
			if (posicao != string::npos) {
    

    		lugarquente = lugarQuente.substr(0, posicao); 
    
    		descricao = lugarQuente.substr(posicao + 1);
			}
			
				string ordem = receita->getLugarGelado();
				if (ordem.back() == '~'){
					ordem.pop_back();
					cout << "*" << "Levar à(o)" << ordem << " por aproximadamente " 
					<< receita->getTempoCongelamento() <<" minutos"<<  endl;
					
					p = false;
					while (p == 0 && j < receita->getEtapas().size()) {

   			 		string recipienteAtual = receita->getEtapas()[j].getRecipiente();

    				if (!recipienteAtual.empty() && recipienteAtual.back() == '~') {
        				recipienteAtual.pop_back();
        				p = true;
    				}

    				cout << "*" << receita->getEtapas()[j].getAcao()
         				<< " em um(a) " << recipienteAtual
         				<< " por " << receita->getEtapas()[j].getTempo()
         				<< " minutos\n";

    					j++;

    					if (p)
        					break;
						}

					lugarQuente = receita->getLugarQuente();
					size_t posicao = lugarQuente.find("~");
					if (posicao != string::npos) {

    				lugarquente = lugarQuente.substr(0, posicao); 
    
    				descricao = lugarQuente.substr(posicao + 1);

					cout <<"*"<< lugarquente << receita->getIntensidade() 
					<< " por aproximadamente " << receita->getTempo() << " minutos "<< descricao << endl;
			}
			}
			else {
				lugarQuente = receita->getLugarQuente();
				size_t posicao = lugarQuente.find("~");
				if (posicao != string::npos) {

    			lugarquente = lugarQuente.substr(0, posicao); 
    
    			descricao = lugarQuente.substr(posicao + 1);

				cout<< "*" << lugarquente <<" " << receita->getIntensidade() 
				<< " por aproximadamente " << receita->getTempo() << " minutos "<< descricao << endl;

				p = false;
				while (p == 0 && j < receita->getEtapas().size()) {

   			 string recipienteAtual = receita->getEtapas()[j].getRecipiente();

    		if (!recipienteAtual.empty() && recipienteAtual.back() == '~') {
        	recipienteAtual.pop_back();
        	p = true;
    	}

    		cout << "*" << receita->getEtapas()[j].getAcao()
         		<< " em um(a) " << recipienteAtual
         		<< " por " << receita->getEtapas()[j].getTempo()
         		<< " minutos\n";

    			j++;

    			if (p)
        			break;
}

		cout << "Levar à(o)" << ordem << " por aproximadamente " 
					<< receita->getTempoCongelamento() <<  endl;
			}
		}
		
}
		p = false;
		while (p == 0 && j < receita->getEtapas().size()) {

   			 string recipienteAtual = receita->getEtapas()[j].getRecipiente();

    		if (!recipienteAtual.empty() && recipienteAtual.back() == '~') {
        	recipienteAtual.pop_back();
        	p = true;
    	}

    	cout << "*" << receita->getEtapas()[j].getAcao()
         << " em um(a) " << recipienteAtual
         << " por " << receita->getEtapas()[j].getTempo()
         << " minutos\n";

    	j++;

    	if (p)
        break;
}
cout << "\n";
}

	bool atualizarReceita(shared_ptr<Receita> a, shared_ptr<Receita> novaReceita) {
		shared_ptr<Receita> receita = a;
		
		receita->setNome(novaReceita->getNome());
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

	bool removerReceita(shared_ptr<Receita> a) {
		shared_ptr<Receita> receita = a;
		
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

	bool removerEtapa(string nome, int num) {//por nome
		shared_ptr<Receita> receita = buscarPorNome(nome);
		if (receita == nullptr) return false;

		receita->removerEtapa(num);
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
	void exibirRelatorioSistema() {
		if (receitas.empty()) {
			cout << "\n--- RELATORIO DO SISTEMA ---" << endl;
			cout << "Nenhuma receita cadastrada no momento." << endl;
			return;
		}

		int totalReceitas = receitas.size();
		int totalQuentes = 0, totalGeladas = 0, totalMistas = 0;
		int totalIngredientes = 0;
		int tempoTotal = 0;
		int maiorTempo = 0;
		string receitaMaisDemorada = "";

	
		for (int i = 0; i < totalReceitas; i++) {
			string tipo = receitas[i]->getTipo();
			
		
			if (tipo == "Quente") totalQuentes++;
			else if (tipo == "Gelada") totalGeladas++;
			else if (tipo == "Mista") totalMistas++;

		
			totalIngredientes += receitas[i]->getIngredientes().size();

			
			int tempoAtual = receitas[i]->calcularTempo();
			tempoTotal += tempoAtual;
			
			if (tempoAtual > maiorTempo) {
				maiorTempo = tempoAtual;
				receitaMaisDemorada = receitas[i]->getNome();
			}
		}

		float tempoMedio = (float)tempoTotal / totalReceitas;

		
		cout << "\n---------------------RELATORIO -----------------------" << endl;
		cout << "Total de Receitas Cadastradas : " << totalReceitas << endl;
		cout << "  -> Receitas Quentes         : " << totalQuentes << endl;
		cout << "  -> Receitas Geladas         : " << totalGeladas << endl;
		cout << "  -> Receitas Mistas          : " << totalMistas << endl;
		cout << "-----------------------------------------------------" << endl;
		cout << "Total Geral de Ingredientes   : " << totalIngredientes << endl;
		cout << "Tempo Medio de Preparo        : " << tempoMedio << " minutos" << endl;
		if (maiorTempo > 0) {
			cout << "Receita Mais Demorada         : " << receitaMaisDemorada 
			     << " (" << maiorTempo << " min)" << endl;
		}
		cout << "-----------------------------------------------------" << endl;
		
	}
	
};
#endif