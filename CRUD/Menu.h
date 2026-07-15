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
	shared_ptr<Receita> a;
    vector<Ingrediente> ingredientesTemporarios;
    vector<Etapa> etapasTemporarias;
    int lerInteiro() {
        int valor;
        while (!(cin >> valor)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Digite novamente: ";
        }
        return valor;
    }

    char lerChar() {
        char valor;
        cin >> valor;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return valor;
    }

    void etapaQuente (char& opcao, string& intensidade, int& tempoQuente, string& lugarQuente){
		cout << "\n🔥 PROCESSO DE AQUECIMENTO\n";
		cout << "Onde será realizado?\n\n";
		cout << "1 │ 🔥 Forno\n";
		cout << "2 │ 🍳 Fogão\n";
		cout << "3 │ ⚙️  Outro equipamento\n";
		cout << "👉 Escolha: ";        
		opcao = lerChar();
        if (opcao == '1') {
            cout << "🌡️ Temperatura do forno: ";
            getline(cin >> ws, intensidade);
            cout << "⏳ Tempo de forno (min): ";
            tempoQuente = lerInteiro();
            cout << "Faca uma breve descrição (Levar ao forno...):\n ";
            getline(cin >> ws, lugarQuente);

            lugarQuente = "Levar ao forno a ~" + lugarQuente;

        } 
		else if (opcao == '2') {
            cout << "🔥 Intensidade do fogão: ";
            getline(cin >> ws, intensidade);
            cout << "⏳ Digite o tempo do fogão: ";
            tempoQuente = lerInteiro();
            cout << "Faca uma breve descrição (Levar ao fogao...):  ";
            getline(cin >> ws, lugarQuente);
            lugarQuente = "Levar ao fogão em ~" + lugarQuente;

        } 
		else if (opcao == '3') {
            cout << "⚙️ Nome do aparelho: " << endl;
            getline(cin >> ws, lugarQuente);
            cout << "Faca uma breve descrição:\n(ex:levar ao airfryer à 150 graus ou levar ao microondas retirando de 15 em 15 segundos): \n";
            getline(cin >> ws, intensidade);
            cout << "⏳Digite o tempo de aquecimento: ";
            tempoQuente = lerInteiro();
        
        } 
		else {
            cout << "⚠️ Opção inválida!" << endl;
        }
    }

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
			cout << "╔══════════════════════════════════════════════╗\n"
				 << "║            🍰 SARA'S COOKING CLASS 🍰        ║\n"
				 << "║      Bem-vindo(a) ao livro de receitas!      ║\n"
				 << "╠══════════════════════════════════════════════╣\n";
            cout << "║  1 │🍰 Criar receita                         ║\n";
			cout << "║  2 │🔎 Buscar receita                        ║\n";
			cout << "║  3 │✏️ Editar receita                         ║\n";
			cout << "║  4 │📚 Listar receitas                       ║\n";
			cout << "║  5 │🗑️ Remover receita                        ║\n";
			cout << "║  6 │📊 Exibir relatorio                      ║\n";
			cout << "║  7 │🚪 Sair                                  ║\n";
			cout << "╚══════════════════════════════════════════════╝\n";
			cout << "➜ Escolha uma opção: \n";
            opcao = lerInteiro();
			cout << "\n";

            switch (opcao) {
                case 1:{
					cout << "╔══════════════════════════════════════════════╗\n";
					cout << "║        🍰 Vamos criar uma nova receita!      ║ \n";
					cout << "╚══════════════════════════════════════════════╝\n";
                    exibirMenuCadastro(gerenciador);
                    break;
                }
                case 2:{    
                    exibirMenuBusca(gerenciador);               
                    break;
                }
                case 3:{
                    exibirMenuEdicao(gerenciador);
                    break;
                }
                case 4:{
                    gerenciador.listarReceitas(true);
                    break;
                }
                case 5:{
                    exibirMenuExclusao(gerenciador);
                    break;
                }
                case 6:{
                    gerenciador.exibirRelatorioSistema();
                    break;
                }
                case 7:{
                    gerenciador.salvarArquivo();
                    cout << "\n╔══════════════════════════════════════════════╗\n";
					cout << "║   👋 Até logo! Obrigado por usar o sistema.  ║\n";
					cout << "║        Continue cozinhando com carinho! 🍰   ║\n";
					cout << "╚══════════════════════════════════════════════╝\n";
                    break;
                }
                default:
                    cout << "⚠️ Opção inválida!" << endl;
            }
        } while (opcao != 7);
    }

    void exibirMenuCadastro(GerenciadorDeReceitas& gerenciador) {
        char opcao;
        string intensidade, nome, indentificador, lugarQuente, lugarGelado;
        int tempoQuente = 0, opcoes = 0, tempoCongelamento = 0, tempoPreparo;
        etapasTemporarias.clear();
        ingredientesTemporarios.clear();

        cout << "\n╔══════════════════════════════════════════════╗\n";
		cout << "║          👩‍🍳 NOVA RECEITA                   ║\n";
		cout << "╠══════════════════════════════════════════════╣\n";
		cout << "║ Qual tipo de receita deseja criar?           ║\n";
		cout << "║                                              ║\n";
		cout << "║ 1 │ 🔥 Receita Quente (forno/fogão)          ║\n";
		cout << "║ 2 │ ❄️  Receita Gelada                        ║\n";
		cout << "║ 3 │ 🍰 Receita Mista                         ║\n";
		cout << "╚══════════════════════════════════════════════╝\n";
		cout << "➜ Escolha uma opção: \n";
        opcao = lerChar();

        switch (opcao) {
            case '1':
				cout << "\n📝 Vamos começar!\n";
				cout << "Digite o nome da receita: ";
                getline(cin >> ws, nome);
                if (gerenciador.buscarPorNome(nome) != nullptr){
					cout << "\n⚠️ Já existe uma receita com esse nome.\n";
                    return;
                }

				cout << "\n🥣 HORA DOS INGREDIENTES\n";
				cout << "Adicione todos os ingredientes da receita.\n";
				cout << "Você poderá adicionar quantos quiser.\n\n";
                adicionarIngredientesReceita(ingredientesTemporarios);

                cout << "\n👩‍🍳 MODO DE PREPARO\n";
				cout << "Agora vamos montar o passo a passo.\n\n";
				cout << "Quais etapas antecedem o aquecimento?" <<endl;
                adicionarEtapasReceita(etapasTemporarias);
                if (!etapasTemporarias.empty()) {
                    indentificador = etapasTemporarias.back().getRecipiente() + "~";
                    etapasTemporarias.back().setRecipiente(indentificador);
                }
                
                etapaQuente(opcao, intensidade, tempoQuente, lugarQuente);

                cout << "Quais são as etapas necessárias para finalizar a receita?" << endl;
                adicionarEtapasReceita(etapasTemporarias);
                
                a = shared_ptr<Receita>(new ReceitaQuente(nome, lugarQuente, intensidade, tempoQuente));
                break;
        
            case '2':
                cout << "\n📝 Vamos começar!\n";
				cout << "Digite o nome da receita: ";
                getline(cin >> ws, nome);
                if (gerenciador.buscarPorNome(nome) != nullptr){
					cout << "\n⚠️ Já existe uma receita com esse nome.\n";
                    return;
                }

				cout << "\n🥣 HORA DOS INGREDIENTES\n";
				cout << "Adicione todos os ingredientes da receita.\n";
				cout << "Você poderá adicionar quantos quiser.\n\n";
                adicionarIngredientesReceita(ingredientesTemporarios);

                cout << "\n👩‍🍳 MODO DE PREPARO\n";
				cout << "Agora vamos montar o passo a passo.\n\n";
                cout << "Quais etapas antecedem o resfriamento?";
                adicionarEtapasReceita(etapasTemporarias);
                if (!etapasTemporarias.empty()) {
                    indentificador = etapasTemporarias.back().getRecipiente() + "~";
                    etapasTemporarias.back().setRecipiente(indentificador);
                }

				cout << "\n❄️ PROCESSO DE RESFRIAMENTO\n";
                cout << "🧊 Onde deseja resfriar? (ex: geladeira, frezzer...) e 📝 Alguma observação? (Opcional): ";
                getline(cin >> ws, lugarGelado);
				cout << "⏳ Tempo de resfriamento (min): ";
                tempoCongelamento = lerInteiro();
                cout << "Quais são as etapas necessárias para finalizar a receita?" << endl;
                adicionarEtapasReceita(etapasTemporarias);

                a = shared_ptr<Receita>(new ReceitaGelada(nome, lugarGelado, tempoCongelamento));
                break;
            
            case '3':{
                cout << "\n📝 Vamos começar!\n";
				cout << "Digite o nome da receita: ";
                getline(cin >> ws, nome);
                if (gerenciador.buscarPorNome(nome) != nullptr){
					cout << "\n⚠️ Já existe uma receita com esse nome.\n";
                    return;
                }

				cout << "\n🥣 HORA DOS INGREDIENTES\n";
				cout << "Adicione todos os ingredientes da receita.\n";
				cout << "Você poderá adicionar quantos quiser.\n\n";
                adicionarIngredientesReceita(ingredientesTemporarios);

                cout << "\n👩‍🍳 MODO DE PREPARO\n";
				cout << "Agora vamos montar o passo a passo.\n\n";
                cout << "Quais etapas antecedem o aquecimento?" <<endl;
                adicionarEtapasReceita(etapasTemporarias);
                if (!etapasTemporarias.empty()) {
                    indentificador = etapasTemporarias.back().getRecipiente() + "~";
                    etapasTemporarias.back().setRecipiente(indentificador);
                }

                while (opcoes <= 1){
                    cout << "Qual processo térmico será utilizado agora?\n";
					cout << "1 │ 🔥 Quente\n";
					cout << "2 │ ❄️  Frio\n";
					cout << "👉 Escolha: ";
					cin.clear();
                    opcao = lerChar();
                    if (opcao == '1' && lugarQuente == "") {
                        etapaQuente (opcao,intensidade,tempoQuente,lugarQuente);
                        opcoes++;

                    } else if (opcao == '2' && lugarGelado == "") {
                        cout << "🧊 Onde deseja resfriar? (ex: geladeira, frezzer...): \n" << "📝 Alguma observação? (Opcional): \n";
						getline(cin >> ws, lugarGelado);
						cout << "⏳ Tempo de resfriamento (min): ";
                        tempoCongelamento = lerInteiro();
                        opcoes++;
                        
                    } else {
                        cout << "⚠️ Opção inválida!" << endl;
                        continue;
                    }
                    if (opcoes == 1){ 
                        cout << "\nQuais são as etapas necessárias antes do próximo processo térmico? ";
                        adicionarEtapasReceita(etapasTemporarias);
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

                a = shared_ptr<Receita>(new ReceitaMista(nome, lugarGelado, lugarQuente, intensidade, tempoQuente, tempoCongelamento));
                break;
            }                   
            default:
                cout << "⚠️ Opção inválida!" << endl;
                return;
        }
        
        gerenciador.criarReceita(a);

        for (int i = 0; i < etapasTemporarias.size(); i++) {
            gerenciador.adicionarEtapa(nome, etapasTemporarias[i]); 
        }

        for (int i = 0; i < ingredientesTemporarios.size(); i++) {
            gerenciador.adicionarIngrediente(nome, ingredientesTemporarios[i]); 
        }

		cout << "\n╔══════════════════════════════════════════════╗\n";
		cout << "║          🎉 RECEITA CADASTRADA!              ║\n";
		cout << "║  Mais uma delícia entrou no livro! 🍓        ║\n";
		cout << "╚══════════════════════════════════════════════╝\n";
    }

    void exibirMenuBusca(GerenciadorDeReceitas& gerenciador) {
        string nomeBuscado;
    
		cout << "\n╔══════════════════════════════════════════════╗\n";
		cout << "║           🔍 BUSCAR RECEITA                  ║\n";
		cout << "╚══════════════════════════════════════════════╝\n";
		cout << "\n╔══════════════════════════════════════════════╗\n";
			cout << "║       📚 RECEITAS DISPONÍVEIS                ║\n";
			cout << "╚══════════════════════════════════════════════╝\n";
		gerenciador.listarReceitas();
		cout << "Digite o nome da receita: ";
        
        getline(cin >> ws, nomeBuscado); 

        auto receitaEncontrada = gerenciador.buscarPorNome(nomeBuscado);

        if (receitaEncontrada != nullptr) {
            cout << "\n╔══════════════════════════════════════════════╗\n";
			cout << "║      🎉 RECEITA ENCONTRADA COM SUCESSO        ║\n";
			cout << "╚══════════════════════════════════════════════╝\n";
            
            gerenciador.printarReceita(receitaEncontrada);
            
        } else {
			cout << "\n╔══════════════════════════════════════════════╗\n";
            cout << "\n║ OPS, NENHUMA RECEITA COM O NOME '" << nomeBuscado << "'. ║" << endl;
			cout << "╚══════════════════════════════════════════════╝\n";
        }
    }

    void exibirMenuEdicao(GerenciadorDeReceitas& gerenciador){
		int i = 0, a;
		ingredientesTemporarios.clear();
		etapasTemporarias.clear();
		string nomeBuscado, novoNome, nomeVelho;
		int novoTempo;
		char o;

		cout << "\n╔══════════════════════════════════════════════╗\n";
		cout << "║           ✏️ EDITAR RECEITA                   ║\n";
		cout << "╚══════════════════════════════════════════════╝\n";
		cout << "Digite o nome exato da receita: ";
		getline(cin >> ws, nomeBuscado); 

		auto receitaEncontrada = gerenciador.buscarPorNome(nomeBuscado);
		
		if (receitaEncontrada != nullptr) {
			nomeVelho = receitaEncontrada->getNome();

			cout << "\n╔══════════════════════════════════════════════╗\n";
			cout << "║        🍰 O QUE DESEJA EDITAR?               ║\n";
			cout << "╠══════════════════════════════════════════════╣\n";
			cout << "║ 1 │ 📝 Nome                                   ║\n";
			cout << "║ 2 │ 🥕 Ingredientes                           ║\n";
			cout << "║ 3 │ 📋 Etapas                                 ║\n";
			cout << "║ 4 │ 🚪 Sair                                   ║\n";
			cout << "╚══════════════════════════════════════════════╝\n";
			cout << "👉 Escolha: ";
			o = lerChar();
			
			switch (o){
				case '1':
					cout << "\n📝 Digite o novo nome da receita: ";
					getline(cin >> ws, novoNome);
					
					receitaEncontrada->setNome(novoNome);

					cout << "\n✅ Receita renomeada com sucesso!\n";
					break;

				case '2':
					cout << "\n🥕 INGREDIENTES\n";
					cout << "1 │ ➕ Adicionar ingredientes\n";
					cout << "2 │ ➖ Remover ingredientes\n";
					cout << "3 │ 🚪 Sair\n";
					cout << "👉 Escolha: ";
					o = lerChar();
					
					if (o=='1'){
						cout << "\n📋 Ingredientes atuais:\n";
						for(int i = 0; i < receitaEncontrada->getIngredientes().size(); i++){
							cout << "  • " << receitaEncontrada->getIngredientes()[i].getNome() << "\n";
						}
						adicionarIngredientesReceita(ingredientesTemporarios);
						for (i = 0; i < ingredientesTemporarios.size(); i++){
							gerenciador.adicionarIngrediente(nomeVelho, ingredientesTemporarios[i]);
						}
						if (i==1){
							cout << "\n✅ Ingrediente adicionado com sucesso!\n";
						}else{
							cout << "\n✅ Ingredientes adicionados com sucesso!\n";
						}
					}else if(o=='2'){
						cout << "\n📋 Ingredientes atuais:\n";
						for(int i = 0; i < receitaEncontrada->getIngredientes().size(); i++){
							cout << "  • " << receitaEncontrada->getIngredientes()[i].getNome() << "\n";
						}
						cout << "\n🗑️ Digite o nome do ingrediente que quer excluir: ";
						getline (cin >> ws, novoNome);
						for (i = 0; i < receitaEncontrada->getIngredientes().size(); i++){
							if (receitaEncontrada->getIngredientes()[i].getNome() == novoNome){
								a = receitaEncontrada->getIngredientes()[i].getId();
								gerenciador.removerIngrediente(receitaEncontrada->getNome(), a);
								cout << "\n✅ Ingrediente excluído com sucesso!\n";
								break;
							}else{
								continue;
							}
						}
						if (i == receitaEncontrada->getIngredientes().size()){
							cout << "\n😕 Ingrediente não encontrado na receita, tente novamente.\n";
						}
					}
					else if (o=='3'){
						cout << "\n🚪 Saindo...\n";
						break;
					}else{
						cout << "\n⚠️ Número inválido!\n";
					}
					break;

				case '3':
					cout << "\n📋 ETAPAS\n";
					cout << "1 │ ➕ Adicionar etapas\n";
					cout << "2 │ ➖ Remover etapas\n";
					cout << "3 │ 🚪 Sair\n";
					cout << "👉 Escolha: ";
					o = lerChar();
					if (o == '1'){
						cout << "\n📋 Etapas atuais:\n";
						for (i = 0; i < receitaEncontrada->getEtapas().size(); i++){
							cout << "\n" << i+1 << " - " << receitaEncontrada->getEtapas()[i].getAcao()
								<< " em um(a) " << receitaEncontrada->getEtapas()[i].getRecipiente()
								<< " por " << receitaEncontrada->getEtapas()[i].getTempo()
								<< " minutos\n";
						}
						vector<Etapa>& etapasOficiais = receitaEncontrada->getEtapas();
						
						adicionarEtapasReceita(etapasOficiais, true);
						
						cout << "\n✅ Etapas adicionadas e organizadas com sucesso!\n";

					}else if(o=='2'){
						cout << "\n🗑️ Digite o número da etapa que quer excluir:\n";
						for (i = 0; i < receitaEncontrada->getEtapas().size(); i++){
							cout << "\n" << i+1 << " - " << receitaEncontrada->getEtapas()[i].getAcao()
								<< " em um(a) " << receitaEncontrada->getEtapas()[i].getRecipiente()
								<< " por " << receitaEncontrada->getEtapas()[i].getTempo()
								<< " minutos\n";
						}
						novoTempo = lerInteiro();
						if (gerenciador.removerEtapa(receitaEncontrada->getNome(), novoTempo - 1)) {
							cout << "\n✅ Etapa removida com sucesso!\n";
						} else {
							cout << "\n⚠️ Número inválido!\n";
						}
					}
					else if (o=='3'){
						cout << "\n🚪 Saindo...\n";
						break;
					}else{
						cout << "\n⚠️ Número inválido!\n";
					}
					break;

				case '4':
					cout << "\n🚪 Saindo...\n";
					break;

				default:
					cout << "\n⚠️ Opção inválida!\n";
					return;
			}
		}
		else {
			cout << "\n╔══════════════════════════════════════════════╗\n";
			cout << "\n║ 😕 NENHUMA RECEITA COM O NOME '" << nomeBuscado << "'. ║\n";
			cout << "╚══════════════════════════════════════════════╝\n";
		}
	}         

    void exibirMenuExclusao(GerenciadorDeReceitas& gerenciador) {
    string nomeBuscado;
    char o;

    cout << "\n╔══════════════════════════════════════════════╗\n";
    cout << "║           🗑️ REMOVER RECEITA                  ║\n";
    cout << "╚══════════════════════════════════════════════╝\n";
    cout << "Digite o nome exato da receita: ";
    getline(cin >> ws, nomeBuscado); 

    auto receitaEncontrada = gerenciador.buscarPorNome(nomeBuscado);

    if (receitaEncontrada != nullptr) {
        cout << "\n⚠️ Tem certeza que deseja excluir '" << nomeBuscado << "'? (s/n): ";
        o = lerChar();
        if (o == 's' || o == 'S'){
            if (gerenciador.removerReceita(receitaEncontrada) == true){
                cout << "\n✅ Receita removida com sucesso!\n";
            }
        }else {
            cout << "\n❌ Operação cancelada.\n";
        }
    } else {
        cout << "\n╔══════════════════════════════════════════════╗\n";
        cout << "\n║ 😕 NENHUMA RECEITA COM O NOME '" << nomeBuscado << "'. ║\n";
        cout << "╚══════════════════════════════════════════════╝\n";
    }
}
    

    void adicionarIngredientesReceita(vector<Ingrediente>& Ingredientes) {
        char continuar;
        do {
            string nome, unidade;

			cout << "\n🥕 Nome do ingrediente: ";
            getline(cin >> ws, nome);
			cout << "⚖️ Quantidade e unidade (g, ml, xícara...): ";
            getline(cin >> ws, unidade);

            
            Ingrediente ingrediente(0, nome, unidade); 
        	Ingredientes.push_back(ingrediente);
               

            cout << "\n➕ Deseja adicionar outro ingrediente? (s/n): ";
            continuar = lerChar();
        } while (continuar == 's' || continuar == 'S');
    }

   void adicionarEtapasReceita(vector<Etapa>& Etapas, bool a = false) {
		char continuar, c;
		int b;
		string indentificador1, indentificador;

		cout << "\n╔══════════════════════════════════════════════╗\n";
		cout << "║          📋 MONTANDO AS ETAPAS               ║\n";
		cout << "╚══════════════════════════════════════════════╝\n";

		do {
			Etapa etapa = perguntarEtapa();
			
			if (a) {
				cout << "\n🔢 Qual o número da etapa que antecede essa? ";
				b = lerInteiro();
				
				if (b >= 0 && b < Etapas.size()) {
					
					cout << "🔥 Essa etapa antecede algum processo térmico? (s/n): ";
					c = lerChar();
					
					if (c == 's' || c == 'S') {
						indentificador1 = Etapas[b-1].getRecipiente();
						
						if (!indentificador1.empty() && indentificador1.back() == '~') {
							indentificador1.pop_back();
							Etapas[b-1].setRecipiente(indentificador1);
						}
						
						indentificador = etapa.getRecipiente() + "~";
						etapa.setRecipiente(indentificador);
					}
					
					Etapas.insert(Etapas.begin() + b , etapa);
					
				} else {
					cout << "\n⚠️ Posição inválida. Etapa adicionada ao final da lista.\n";
					Etapas.push_back(etapa);
				}

			} else {
				Etapas.push_back(etapa);
			}
			
			cout << "\n➕ Adicionar outra etapa? (s/n): ";
			continuar = lerChar();
			
		} while (continuar == 's' || continuar == 'S');
	}

    Etapa perguntarEtapa(){
        string acao, recipiente;
        int tempo;

		cout << "\n📌 O que deve ser feito?\n";
		cout << "Ação: ";
        getline(cin >> ws, acao);
		cout << "🥣 Recipiente utilizado: ";        
		getline(cin >> ws, recipiente);
		cout << "⏳ Tempo (minutos): ";        
		tempo = lerInteiro();

        return Etapa(acao, tempo, recipiente);
    }
    
};

#endif
