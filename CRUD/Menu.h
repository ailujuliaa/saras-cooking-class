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

	void etapaQuente (char& opcao, string& intensidade, int& tempoQuente, string& lugarQuente){
	cout << "1- Forno \n2- Fogão?\n3- Outro... ";
			cin >> opcao;
			if (opcao == '1') {
				cout << "Digite a temperatura do forno: ";
				getline(cin >> ws, intensidade);
				cout << "Digite o tempo do forno: ";
				cin >> tempoQuente;
				cout << "Faca uma breve descrição: ";
				getline(cin >> ws, lugarQuente);

				lugarQuente = "Levar ao forno ~" + lugarQuente;

			} else if (opcao == '2') {
				cout << "Digite a intensidade do fogão: ";
				getline(cin >> ws, intensidade);
				cout << "Digite o tempo do fogão: ";
				cin >> tempoQuente;
				cout << "Faca uma breve descrição: ";
				getline(cin >> ws, lugarQuente);
				lugarQuente = "Levar ao fogão ~" + lugarQuente;

				} else if (opcao == '3') {
				cout << "Nome do aparelho: " << endl;
				getline(cin >> ws, lugarQuente);
				cout << "Faca uma breve descrição: ";
				getline(cin >> ws, intensidade);
				cout << "Digite o tempo de aquecimento: ";
				cin >> tempoQuente;
			
			} else {
				cout << "Opção inválida!" << endl;
			}
		
}

	shared_ptr<Receita> a;
	vector<Ingrediente> ingredientesTemporarios;
	vector<Etapa> etapasTemporarias;

public:
	Menu() {

		if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
	}
	void exibirMenuPrincipal(GerenciadorDeReceitas& gerenciador) {
		int opcao;
		string nome;
		do{
		cout << "Escolha uma opção:\n"
			<< "1- Criar receita\n" 
			<< "2- Ler receita\n" 
			<< "3- Atualizar receita\n" 
			<< "4- Exibir receitas\n" 
			<< "5- Excluir receita\n" 
			<< "6- Ver todas as receitas\n" 
			<< "7- Sair" << endl;

			cin >> opcao;

			switch (opcao) {
				case 1:{
					exibirMenuCadastro(gerenciador);
					break;
				}
				case 2:{ 	
					exibirMenuBusca(gerenciador);				
					break;
				}
				case 3:{
					
					break;
				}
				case 4:{
					gerenciador.listarReceitas();
					break;
				}
				case 5:{
					exibirMenuExclusao(gerenciador);
					break;
				}
				case 6:{
					gerenciador.listarReceitas(true);
					break;
				}
				case 7:{
					gerenciador.salvarArquivo();
					cout << "Saindo..." << endl;
					break;
				}
				default:
					cout << "Opção inválida!" << endl;
			}
		} while (opcao != 7);
	}

	void exibirMenuCadastro(GerenciadorDeReceitas& gerenciador) {
		char opcao;
		string intensidade, nome, indentificador, lugarQuente, lugarGelado;
		int tempoQuente = 0, opcoes = 0, tempoCongelamento, tempoPreparo;
		etapasTemporarias.clear();
    	ingredientesTemporarios.clear();

		cout << "Qual é o tipo da receita?\n" << "1- Receita de Forno ou Fogão\n" 
		<< "2- Receita de Geladeira\n" << "3- Receita Mista\n" << endl;
		cin >> opcao;

		switch (opcao) {
			case '1':
			cout << "Digite o nome da receita: ";
			getline(cin >> ws, nome);
			if (gerenciador.buscarPorNome(nome) != nullptr){
				cout << "receita já registrada";
				break;
			}
			cout << "Digite o tempo de preparo: ";
			cin >> tempoPreparo;

			adicionarIngredientesReceita(ingredientesTemporarios);
			cout << "Quais etapas antecedem o aquecimento?" <<endl;
			adicionarEtapasReceita(etapasTemporarias);
			if (!etapasTemporarias.empty()) {
    		indentificador = etapasTemporarias.back().getRecipiente() + "~";
    		etapasTemporarias.back().setRecipiente(indentificador);
			}
			
			etapaQuente(opcao, intensidade, tempoQuente, lugarQuente);

			cout << "Quais são as etapas necessárias para finalizar a receita?" << endl;
			adicionarEtapasReceita(etapasTemporarias);
			if (!etapasTemporarias.empty()) {
    		indentificador = etapasTemporarias.back().getRecipiente() + "~";
    		etapasTemporarias.back().setRecipiente(indentificador);
			}

			a = shared_ptr<Receita>(new ReceitaQuente(nome, tempoPreparo, lugarQuente, intensidade, tempoQuente));
		
		
				break;
		
			case '2':

			cout << "Digite o nome da receita: ";
			getline(cin >> ws, nome);
			if (gerenciador.buscarPorNome(nome) != nullptr){
				cout << "receita já registrada";
				break;
			}
			cout << "Digite o tempo de preparo: ";
			cin >> tempoPreparo;
			adicionarIngredientesReceita(ingredientesTemporarios);
			cout << "Quais etapas antecedem o resfriamento?";
			adicionarEtapasReceita(etapasTemporarias);
			if (!etapasTemporarias.empty()) {
   			indentificador = etapasTemporarias.back().getRecipiente() + "~";
   			etapasTemporarias.back().setRecipiente(indentificador);
			}
			cout << "Aonde deseja resfriar (ex: geladeira, frezzer...)\n" << "Existe alguma breve descrição? (caso contrário, apenas não escreva)" << endl;
			getline(cin >> ws, lugarGelado);
			cout << "Digite o tempo de resfriamento: ";
			cin >> tempoCongelamento;
			cout << "Quais são as etapas necessárias para finalizar a receita?" << endl;
			adicionarEtapasReceita(etapasTemporarias);
			if (!etapasTemporarias.empty()) {
    		indentificador = etapasTemporarias.back().getRecipiente() + "~";
    		etapasTemporarias.back().setRecipiente(indentificador);
			}
		

				a = shared_ptr<Receita>(new ReceitaGelada(nome, lugarGelado, tempoPreparo, tempoCongelamento));

				break;
			
			case '3':{
				cout << "Digite o nome da receita: ";
				getline(cin >> ws, nome);
				if (gerenciador.buscarPorNome(nome) != nullptr){
				cout << "receita já registrada";
				break;
			}
				cout << "Digite o tempo de preparo: ";
				cin >> tempoPreparo;

				adicionarIngredientesReceita(ingredientesTemporarios);
				cout << "Quais etapas antecedem o aquecimento?" <<endl;
				adicionarEtapasReceita(etapasTemporarias);
				if (!etapasTemporarias.empty()) {
    			indentificador = etapasTemporarias.back().getRecipiente() + "~";
    			etapasTemporarias.back().setRecipiente(indentificador);
				}
				
				while (opcoes <= 1){

					cout << "O processo térmico usado agora é:\n1-Quente\n2-Frio " << endl;
					cin >> opcao;
					if (opcao == '1' && lugarQuente == "") {
					etapaQuente (opcao,intensidade,tempoQuente,lugarQuente);
					opcoes++;

					} else if (opcao == '2' && lugarGelado == "") {
					cout << "Aonde deseja resfriar (ex: geladeira, frezzer...)\n" << "Existe alguma breve descrição? (caso contrário, apenas não escreva)" << endl;
					getline(cin >> ws, lugarGelado);
					cout << "Digite o tempo de resfriamento: ";
					cin >> tempoCongelamento;
					opcoes++;
					
					} else {
					cout << "Opção inválida!" << endl;
					continue;
					}
					if (opcoes == 1){ 
					cout << "Quais são as etapas necessárias antes do próximo processo térmico";
					if (!etapasTemporarias.empty()) {
    				indentificador = etapasTemporarias.back().getRecipiente() + "~";
    				etapasTemporarias.back().setRecipiente(indentificador);
					}
					if (tempoCongelamento != 0){
					lugarGelado = lugarGelado + "~";
					}
					
					} else {
						break;
					}			
				}

				cout << "Quais são as etapas necessárias para finalizar a receita?" << endl;
				adicionarEtapasReceita(etapasTemporarias);
				if (!etapasTemporarias.empty()) {
    			indentificador = etapasTemporarias.back().getRecipiente() + "~";
    			etapasTemporarias.back().setRecipiente(indentificador);
				}

				a = shared_ptr<Receita>(new ReceitaMista(nome, tempoPreparo, lugarGelado, lugarQuente, intensidade, tempoQuente, tempoCongelamento));
					break;
						}					
			default:
				cout << "Opção inválida!" << endl;
				return;
			}
		
		gerenciador.criarReceita(a);

		for (int i = 0; i < etapasTemporarias.size(); i++) {
    		gerenciador.adicionarEtapa(nome, etapasTemporarias[i]); 
		}

		for (int i = 0; i < ingredientesTemporarios.size(); i++) {
    		gerenciador.adicionarIngrediente(nome, ingredientesTemporarios[i]); 
		}

		cout << "Receita cadastrada com sucesso!" << endl;

	}


	void exibirMenuBusca(GerenciadorDeReceitas& gerenciador) {
		string nomeBuscado;
    
    cout << "\n--- BUSCAR RECEITA ---" << endl;
    cout << "Digite o nome exato da receita: ";
    
    
    getline(cin >> ws, nomeBuscado); 

    auto receitaEncontrada = gerenciador.buscarPorNome(nomeBuscado);

    if (receitaEncontrada != nullptr) {
        cout << "\nReceita Encontrada com Sucesso!" << endl;
        cout << "-----------------------------------" << endl;
        
        gerenciador.printarReceita(receitaEncontrada);
        
    } else {
        cout << "\nOps! Nenhuma receita encontrada com o nome '" << nomeBuscado << "'." << endl;
    }
}



	void exibirMenuExclusao(GerenciadorDeReceitas& gerenciador) {
		string nomeBuscado;
		char o;
		cout << "\n--- BUSCAR RECEITA PARA EXCLUIR ---" << endl;
    	cout << "Digite o nome exato da receita: ";
    	getline(cin >> ws, nomeBuscado); 

    	auto receitaEncontrada = gerenciador.buscarPorNome(nomeBuscado);

    if (receitaEncontrada != nullptr) {
        cout << "\nDeseja excluir essa receita?" << endl;
        cout << "-----------------------------------" << endl;
		cin >> o;
		if (o == 's' || o == 'S'){
			if (gerenciador.removerReceita(receitaEncontrada) == true){
			cout << "Operação executada com sucesso!" << endl;
			}

		}else {
			 cout << "\nOperação cancelada" << endl;
		}
        
    
    } else {
        cout << "\nOps! Nenhuma receita encontrada com o nome '" << nomeBuscado << "'." << endl;
    }
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

	void adicionarIngredientesReceita(vector<Ingrediente>& Ingredientes) {
		char continuar;
		do {
			string nome, unidade;

			cout << "Nome do ingrediente: ";
			getline(cin >> ws, nome);
			cout << "Qual a quantidade e unidade (g, ml, xícara...): ";
			getline(cin >> ws, unidade);

			Ingrediente ingrediente(0, nome, unidade); // id é definido pelo gerenciador
			Ingredientes.push_back(ingrediente);

			cout << "Adicionar outro ingrediente? (s/n): ";
			cin >> continuar;
			cin.ignore();
		} while (continuar == 's' || continuar == 'S');
	}

	void adicionarEtapasReceita(vector<Etapa>& Etapas) {
		char continuar;
		do {
			Etapa etapa = perguntarEtapa();
			
			Etapas.push_back(etapa);

			cout << "Adicionar outra etapa? (s/n): ";
			cin >> continuar;
			cin.ignore();
		} while (continuar == 's' || continuar == 'S');
		if (continuar != 's' || continuar != 'S'){
			 
		}
	}

	Etapa perguntarEtapa(){
		string acao, recipiente;
		int tempo;

		cout << "Ação da etapa (ex: misturar, assar): ";
		getline(cin >> ws, acao);
		cout << "Recipiente utilizado: ";
		getline(cin >> ws, recipiente);
		cout << "Tempo da etapa (minutos): ";
		cin >> tempo;
		

		return Etapa(acao, tempo, recipiente);
	}
	
};



#endif