#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "GerenciadorDeReceitas.h"
#include "Receita.h"
#include "ReceitaForno.h"
#include "ReceitaGelada.h"
#include "ReceitaMista.h"
#include "SobremesaDeFogao.h"
#include "Etapa.h"

using namespace std;

class Menu
{
private:
	GerenciadorDeReceitas gerenciadorDeReceitas;

public:
	void exibirMenuPrincipal() {
		int opcao;
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
					cout << "Saindo..." << endl;
					break;
				default:
					cout << "Opção inválida!" << endl;
			}
	}



	void exibirMenuCadastro() {
		Receita* a;
		char opcao;
		string nome;
		int temperaturaForno, tempoForno, tempoCongelamento, tempoPreparo;

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
			cout << "Digite a temperatura do forno: ";
			cin >> temperaturaForno;
			cout << "Digite o tempo do forno: ";
			cin >> tempoForno;

				a = new ReceitaForno(nome, tempoPreparo, temperaturaForno, tempoForno);

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
			cout << "Digite a temperatura do forno: ";
			cin >> temperaturaForno;
			cout << "Digite o tempo do forno: ";
			cin >> tempoForno;
			
				break;
			case '4':
				// Criar sobremesa de fogão
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

	int lerOpcao() {
		int opc;
		cin >> opc;
		return 0;
	}
};
#endif