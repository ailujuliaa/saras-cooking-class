#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>
#include "GerenciadorDeReceitas.h"
#include "Receita.h"
#include "ReceitaQuente.h"
#include "ReceitaGelada.h"
#include "ReceitaMista.h"
#include "Etapa.h"

using namespace std;

class Menu
{
private:
	GerenciadorDeReceitas gerenciadorDeReceitas;
	shared_ptr<Receita> a;

public:
	Menu() {
		gerenciadorDeReceitas.lerArquivo();
		if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
	}
	void exibirMenuPrincipal(GerenciadorDeReceitas& gerenciador) {
		int opcao;
		do{
		cout << "Escolha uma opção: "
			<< "1- Criar receita\n" 
			<< "2- Ler receita\n" 
			<< "3- Atualizar receita\n" 
			<< "4- Procurar receita\n" 
			<< "5- Excluir receita\n" 
			<< "6- Ver todas as receitas\n" 
			<< "7- Sair" << endl;

			cin >> opcao;

			switch (opcao) {
				case 1:
					exibirMenuCadastro(gerenciador);
					break;
				case 2:
					exibirMenuLeitura();
					break;
				case 3:
					exibirMenuEdicao();
					break;
				case 4:
					exibirMenuBusca();
					break;
				case 5:
					exibirMenuEdicao();
					break;
				case 6:
					exibirListaReceitas(gerenciadorDeReceitas.listarTodas());
					break;
				case 7:
					gerenciadorDeReceitas.salvarArquivo();
					cout << "Saindo..." << endl;
					break;
				default:
					cout << "Opção inválida!" << endl;
			}
		} while (opcao != 7);
	}

	void exibirMenuCadastro(GerenciadorDeReceitas& gerenciador) {
		char opcao;
		string intensidade, nome;
		int tempoQuente = 0, opcoes = 0, tempoCongelamento, tempoPreparo;

		cout << "Qual é o tipo da receita?" << "1- Receita de Forno ou Fogão\n" 
		<< "2- Receita de Geladeira\n" << "3- Receita Mista\n" << endl;
		cin >> opcao;

		switch (opcao) {
			case '1':
			cout << "Digite o nome da receita: ";
			getline(cin >> ws, nome);
			cout << "Digite o tempo de preparo: ";
			cin >> tempoPreparo;
			adicionarIngredientesReceita(gerenciador, nome);
			cout << "Quais etapas antecedem o aquecimento?";
			adicionarEtapasReceita(gerenciador, nome);
			cout << "1- Forno \n2- Fogão? ";
			cin >> opcao;
			if (opcao == '1') {
				cout << "Digite a temperatura do forno: ";
				getline(cin >> ws, intensidade);
				cout << "Digite o tempo do forno: ";
				cin >> tempoQuente;

			} else if (opcao == '2') {
				cout << "Digite a intensidade do fogão: ";
				getline(cin >> ws, intensidade);
				cout << "Digite o tempo do fogão: ";
				cin >> tempoQuente;

			} else {
				cout << "Opção inválida!" << endl;
			}

			cout << "Quais são as etapas necessárias para finalizar a receita?" << endl;
			adicionarEtapasReceita(gerenciador, nome);

			a = shared_ptr<Receita>(new ReceitaQuente(nome, tempoPreparo, intensidade, tempoQuente));

				break;
				
			case '2':

			cout << "Digite o nome da receita: ";
			getline(cin >> ws, nome);
			cout << "Digite o tempo de preparo: ";
			cin >> tempoPreparo;
			adicionarIngredientesReceita(gerenciador, nome);
			cout << "Quais etapas antecedem o resfriamento?";
			adicionarEtapasReceita(gerenciador, nome);
			cout << "Digite o tempo de resfriamento: ";
			cin >> tempoCongelamento;
			cout << "Quais são as etapas necessárias para finalizar a receita?" << endl;
			adicionarEtapasReceita(gerenciador, nome);

				a = shared_ptr<Receita>(new ReceitaGelada(nome, tempoPreparo, tempoCongelamento));

				break;
			
			case '3':

				cout << "Digite o nome da receita: ";
				getline(cin >> ws, nome);
				cout << "Digite o tempo de preparo: ";
				cin >> tempoPreparo;
				adicionarIngredientesReceita(gerenciador, nome);
				cout << "Quais etapas iniciam essa receita, antecipando os processos térmicos?";
				adicionarEtapasReceita(gerenciador, nome);
				cout << "1- Forno \n2- Fogão \n3- Geladeira" << endl;
			 
				while ((opcao == '1' || opcao == '2' || opcao != '3') && opcoes < 1)
			 	{
					cin >> opcao;
					if (opcao == '1' && tempoQuente == 0) {
					cout << "Digite a temperatura do forno: ";
					getline(cin >> ws, intensidade);
					cout << "Digite o tempo do forno: ";
					cin >> tempoQuente;
					opcoes++;
					break;
					} else if (opcao == '2' && tempoQuente == 0) {
					cout << "Digite a intensidade do fogão: ";
					getline(cin >> ws, intensidade);
					cout << "Digite o tempo do fogão: ";
					cin >> tempoQuente;
					opcoes++;
					break;
					} else if (opcao == '3') {
					cout << "Digite o tempo de congelamento: ";
					cin >> tempoCongelamento;
					opcoes++;
					break;
					} else {
					cout << "Opção inválida!" << endl;
					}
					cout << "Quais são as etapas necessárias antes do próximo processo térmico";
					adicionarEtapasReceita(gerenciador, nome);
				}

				cout << "Quais são as etapas necessárias para finalizar a receita?" << endl;
				adicionarEtapasReceita(gerenciador, nome);

				a = shared_ptr<Receita>(new ReceitaMista(nome, tempoPreparo, intensidade, tempoQuente, tempoCongelamento));
					break;

			default:
				cout << "Opção inválida!" << endl;
				return;
		}
		gerenciadorDeReceitas.criarReceita(a);
		cout << "Receita cadastrada com sucesso!" << endl;

		
	}

	void exibirMenuLeitura() {

		
	}

	void exibirMenuBusca() {


	}

	void exibirMenuEdicao() {
		
	}

	void exibirMenuIngredientes() {
		
	}

	void exibirReceita(shared_ptr<Receita> receita) {
		
	}

	void exibirListaReceitas(vector<shared_ptr<Receita>> receitas) {
		
	}

	vector<string> listarAcoes(){
		return vector<string>();
	}

	void adicionarIngredientesReceita(GerenciadorDeReceitas& gerenciador, string nomeReceita) {
		char continuar;
		do {
			string nome, unidade;

			cout << "Nome do ingrediente: ";
			getline(cin >> ws, nome);
			cout << "Qual a quantidade e unidade (g, ml, xícara...): ";
			getline(cin >> ws, unidade);

			Ingrediente ingrediente(0, nome, unidade); // id é definido pelo gerenciador
			gerenciadorDeReceitas.adicionarIngrediente(nomeReceita, ingrediente);

			cout << "Adicionar outro ingrediente? (s/n): ";
			cin >> continuar;
		} while (continuar == 's' || continuar == 'S');
	}

	void adicionarEtapasReceita(GerenciadorDeReceitas& gerenciador, string nomeReceita) {
		char continuar;
		do {
			Etapa etapa = perguntarEtapa();
			gerenciadorDeReceitas.adicionarEtapa(nomeReceita, etapa);

			cout << "Adicionar outra etapa? (s/n): ";
			cin >> continuar;
		} while (continuar == 's' || continuar == 'S');
	}

	Etapa perguntarEtapa(){
		string acao, recipiente;
		int tempo;

		cout << "Ação da etapa (ex: misturar, assar): ";
		getline(cin >> ws, acao);
		cout << "Tempo da etapa (minutos): ";
		cin >> tempo;
		cout << "Recipiente utilizado: ";
		getline(cin >> ws, recipiente);

		return Etapa(acao, tempo, recipiente);
	}

};
#endif