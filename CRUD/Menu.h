#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
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
	Receita* a;

public:
	Menu() {
		gerenciadorDeReceitas.lerArquivo();
	}
	void exibirMenuPrincipal() {
		int opcao;
		do {
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
					exibirMenuCadastro();
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



	void exibirMenuCadastro() {
		char opcao;
		string intensidade, nome;
		int tempoQuente = 0, opcoes, tempoCongelamento, tempoPreparo;

		cout << "Qual é o tipo da receita?" << "1- Receita de Forno\n" 
		<< "2- Receita de Geladeira\n" << "3- Receita Mista\n" 
		<< "4- Sobremesa de Fogão" << endl;
		cin >> opcao;

		switch (opcao) {
			case '1':
			

			cout << "Digite o nome da receita: ";
			cin >> nome;
			cout << "Digite o tempo de preparo: ";
			cin >> tempoPreparo;
			cout << "1- Forno \n2- Fogão? ";
			cin >> opcao;
			if (opcao == '1') {
				cout << "Digite a temperatura do forno: ";
				cin >> intensidade;
				cout << "Digite o tempo do forno: ";
				cin >> tempoQuente;

			} else if (opcao == '2') {
				cout << "Digite a intensidade do fogão: ";
				cin >> intensidade;
				cout << "Digite o tempo do fogão: ";
				cin >> tempoQuente;

			} else {
				cout << "Opção inválida!" << endl;
			}

			a = new ReceitaQuente(nome, tempoPreparo, intensidade, tempoQuente);

				break;
				
			case '2':

			cout << "Digite o nome da receita: ";
			cin >> nome;
			cout << "Digite o tempo de preparo: ";
			cin >> tempoPreparo;
			cout << "Digite o tempo de congelamento: ";
			cin >> tempoCongelamento;

				a = new ReceitaGelada(nome, tempoPreparo, tempoCongelamento);

				break;
			
			case '3':

				cout << "Digite o nome da receita: ";
				cin >> nome;
				cout << "Digite o tempo de preparo: ";
				cin >> tempoPreparo;
				cout << "1- Forno \n2- Fogão \n3- Geladeira" << endl;
			 
				while ((opcao == '1' || opcao == '2' || opcao != '3') && opcoes < 1)
			 	{
					cin >> opcao;
					if (opcao == '1' && tempoQuente == 0) {
					cout << "Digite a temperatura do forno: ";
					cin >> intensidade;
					cout << "Digite o tempo do forno: ";
					cin >> tempoQuente;
					opcoes++;
					break;
					} else if (opcao == '2' && tempoQuente == 0) {
					cout << "Digite a intensidade do fogão: ";
					cin >> intensidade;
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
				}

				a = new ReceitaMista(nome, tempoPreparo, intensidade, tempoQuente, tempoCongelamento);
					break;

				default:
					cout << "Opção inválida!" << endl;
		}
		
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

	Etapa perguntarEtapa(){
		return Etapa();
	}

};
#endif