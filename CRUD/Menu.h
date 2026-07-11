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
	vector<Ingrediente> ingredientesTemporarios;
	vector<Etapa> etapasTemporarias;

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
		string nome;
		do{
		cout << "Escolha uma opção:\n"
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
					
					break;
				case 3:
					exibirMenuEdicao();
					break;
				case 4:
					exibirMenuBusca(gerenciador);
				case 5:
					exibirMenuEdicao();
					break;
				case 6:
					gerenciador.listarReceitas();
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
			adicionarIngredientesReceita(ingredientesTemporarios);
			cout << "Quais etapas antecedem o aquecimento?";
			adicionarEtapasReceita(etapasTemporarias);
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
			adicionarEtapasReceita(etapasTemporarias);

			a = shared_ptr<Receita>(new ReceitaQuente(nome, tempoPreparo, intensidade, tempoQuente));

				break;
				
			case '2':

			cout << "Digite o nome da receita: ";
			getline(cin >> ws, nome);
			cout << "Digite o tempo de preparo: ";
			cin >> tempoPreparo;
			adicionarIngredientesReceita(ingredientesTemporarios);
			cout << "Quais etapas antecedem o resfriamento?";
			adicionarEtapasReceita(etapasTemporarias);
			cout << "Digite o tempo de resfriamento: ";
			cin >> tempoCongelamento;
			cout << "Quais são as etapas necessárias para finalizar a receita?" << endl;
			adicionarEtapasReceita(etapasTemporarias);

				a = shared_ptr<Receita>(new ReceitaGelada(nome, tempoPreparo, tempoCongelamento));

				break;
			
			case '3':

				cout << "Digite o nome da receita: ";
				getline(cin >> ws, nome);
				cout << "Digite o tempo de preparo: ";
				cin >> tempoPreparo;
				adicionarIngredientesReceita(ingredientesTemporarios);
				cout << "Quais etapas iniciam essa receita, antecipando os processos térmicos?";
				adicionarEtapasReceita(etapasTemporarias);
			 
				while (opcoes <= 1){

					cout << "1- Forno \n2- Fogão \n3- Geladeira" << endl;
					cin >> opcao;
					if (opcao == '1' && tempoQuente == 0) {
					cout << "Digite a temperatura do forno: ";
					getline(cin >> ws, intensidade);
					cout << "Digite o tempo do forno: ";
					cin >> tempoQuente;
					opcoes++;

					} else if (opcao == '2' && tempoQuente == 0) {
					cout << "Digite a intensidade do fogão: ";
					getline(cin >> ws, intensidade);
					cout << "Digite o tempo do fogão: ";
					cin >> tempoQuente;
					opcoes++;
					
					} else if (opcao == '3') {
					cout << "Digite o tempo de congelamento: ";
					cin >> tempoCongelamento;
					opcoes++;
					
					} else {
					cout << "Opção inválida!" << endl;
					continue;
					}
					cout << "Quais são as etapas necessárias antes do próximo processo térmico";
					adicionarEtapasReceita(etapasTemporarias);
				}

				cout << "Quais são as etapas necessárias para finalizar a receita?" << endl;
				adicionarEtapasReceita(etapasTemporarias);

				a = shared_ptr<Receita>(new ReceitaMista(nome, tempoPreparo, intensidade, tempoQuente, tempoCongelamento));
					break;

			default:
				cout << "Opção inválida!" << endl;
				return;
		}
		gerenciadorDeReceitas.criarReceita(a);
		for (int i = 0; i < etapasTemporarias.size(); i++) {
    		gerenciadorDeReceitas.adicionarEtapa(nome, etapasTemporarias[i]); 
		}

		for (int i = 0; i < ingredientesTemporarios.size(); i++) {
    		gerenciadorDeReceitas.adicionarIngrediente(nome, ingredientesTemporarios[i]); 
		}

		cout << "Receita cadastrada com sucesso!" << endl;

	}

	void exibirMenuLeitura () {
		
		
	}

	void exibirMenuBusca(GerenciadorDeReceitas& gerenciador) {
		string nomeBuscado;
    
    cout << "\n--- BUSCAR RECEITA ---" << endl;
    cout << "Digite o nome exato da receita: ";
    
    // getline com 'ws' ignora sujeiras do buffer e pega a linha inteira com os espaços
    getline(cin >> ws, nomeBuscado); 

    // Chama o back-end para fazer o trabalho pesado
    auto receitaEncontrada = gerenciador.buscarPorNome(nomeBuscado);

    // Avalia o resultado
    if (receitaEncontrada != nullptr) {
        cout << "\nReceita Encontrada com Sucesso!" << endl;
        cout << "-----------------------------------" << endl;
        
        // Aqui você chama a função que imprime a receita na tela.
        // Pode ser algo como:
        // receitaEncontrada->imprimirDetalhes();
        
    } else {
        cout << "\nOps! Nenhuma receita encontrada com o nome '" << nomeBuscado << "'." << endl;
    }
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

	void adicionarIngredientesReceita(vector<Ingrediente>& Ingredientes) {
		char continuar;
		do {
			string nome, unidade;

			cout << "Nome do ingrediente: ";
			getline(cin >> ws, nome);
			cout << "Qual a quantidade e unidade (g, ml, xícara...): ";
			getline(cin >> ws, unidade);

			Ingrediente ingrediente(0, nome, unidade); // id é definido pelo gerenciador
			ingredientesTemporarios.push_back(ingrediente);

			cout << "Adicionar outro ingrediente? (s/n): ";
			cin >> continuar;
			cin.ignore();
		} while (continuar == 's' || continuar == 'S');
	}

	void adicionarEtapasReceita(vector<Etapa>& Etapas) {
		char continuar;
		do {
			Etapa etapa = perguntarEtapa();
			
			etapasTemporarias.push_back(etapa);

			cout << "Adicionar outra etapa? (s/n): ";
			cin >> continuar;
			cin.ignore();
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