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
        cout << "1- Forno \n2- Fogão?\n3- Outro... ";
        opcao = lerChar();
        if (opcao == '1') {
            cout << "Digite a temperatura do forno: ";
            getline(cin >> ws, intensidade);
            cout << "Digite o tempo do forno: ";
            tempoQuente = lerInteiro();
            cout << "Faca uma breve descrição:\nLevar ao forno... ";
            getline(cin >> ws, lugarQuente);

            lugarQuente = "Levar ao forno a ~" + lugarQuente;

        } else if (opcao == '2') {
            cout << "Digite a intensidade do fogão: ";
            getline(cin >> ws, intensidade);
            cout << "Digite o tempo do fogão: ";
            tempoQuente = lerInteiro();
            cout << "Faca uma breve descrição:\nLevar ao fogao... ";
            getline(cin >> ws, lugarQuente);
            lugarQuente = "Levar ao fogão em ~" + lugarQuente;

        } else if (opcao == '3') {
            cout << "Nome do aparelho: " << endl;
            getline(cin >> ws, lugarQuente);
            cout << "Faca uma breve descrição:\n(ex:levar ao airfryer à 150 graus ou levar ao microondas retirando de 15 em 15 segundos) ";
            getline(cin >> ws, intensidade);
            cout << "Digite o tempo de aquecimento: ";
            tempoQuente = lerInteiro();
        
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
                 << "6- Relátorio\n" 
                 << "7- Sair" << endl;

            opcao = lerInteiro();

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
                    exibirMenuEdicao(gerenciador);
                    break;
                }
                case 4:{
                    gerenciador.listarReceitas();
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
        opcao = lerChar();

        switch (opcao) {
            case '1':
                cout << "Digite o nome da receita: ";
                getline(cin >> ws, nome);
                if (gerenciador.buscarPorNome(nome) != nullptr){
                    cout << "receita já registrada";
                    break;
                }

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
                
                a = shared_ptr<Receita>(new ReceitaQuente(nome, lugarQuente, intensidade, tempoQuente));
                break;
        
            case '2':
                cout << "Digite o nome da receita: ";
                getline(cin >> ws, nome);
                if (gerenciador.buscarPorNome(nome) != nullptr){
                    cout << "receita já registrada";
                    break;
                }
                adicionarIngredientesReceita(ingredientesTemporarios);
                cout << "Quais etapas antecedem o resfriamento?";
                adicionarEtapasReceita(etapasTemporarias);
                if (!etapasTemporarias.empty()) {
                    indentificador = etapasTemporarias.back().getRecipiente() + "~";
                    etapasTemporarias.back().setRecipiente(indentificador);
                }
                cout << "Aonde deseja resfriar (ex: geladeira, frezzer...)\n" << "Além disso, existe alguma breve descrição? (caso contrário, apenas não escreva)" << endl;
                getline(cin >> ws, lugarGelado);
                cout << "Digite o tempo de resfriamento:(minutos) ";
                tempoCongelamento = lerInteiro();
                cout << "Quais são as etapas necessárias para finalizar a receita?" << endl;
                adicionarEtapasReceita(etapasTemporarias);

                a = shared_ptr<Receita>(new ReceitaGelada(nome, lugarGelado, tempoCongelamento));
                break;
            
            case '3':{
                cout << "Digite o nome da receita: ";
                getline(cin >> ws, nome);
                if (gerenciador.buscarPorNome(nome) != nullptr){
                    cout << "receita já registrada";
                    break;
                }

                adicionarIngredientesReceita(ingredientesTemporarios);
                cout << "Quais etapas antecedem o aquecimento?" <<endl;
                adicionarEtapasReceita(etapasTemporarias);
                if (!etapasTemporarias.empty()) {
                    indentificador = etapasTemporarias.back().getRecipiente() + "~";
                    etapasTemporarias.back().setRecipiente(indentificador);
                }
                
                while (opcoes <= 1){
                    cout << "O processo térmico usado agora é:\n1-Quente\n2-Frio " << endl;
                    opcao = lerChar();
                    if (opcao == '1' && lugarQuente == "") {
                        etapaQuente (opcao,intensidade,tempoQuente,lugarQuente);
                        opcoes++;

                    } else if (opcao == '2' && lugarGelado == "") {
                        cout << "Aonde deseja resfriar (ex: geladeira, frezzer...)\n" << "Além disso, existe alguma breve descrição? (caso contrário, apenas não escreva)" << endl;
                        getline(cin >> ws, lugarGelado);
                        cout << "Digite o tempo de resfriamento:(minutos) ";
                        tempoCongelamento = lerInteiro();
                        opcoes++;
                        
                    } else {
                        cout << "Opção inválida!" << endl;
                        continue;
                    }
                    if (opcoes == 1){ 
                        cout << "Quais são as etapas necessárias antes do próximo processo térmico";
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


    void exibirMenuEdicao(GerenciadorDeReceitas& gerenciador){
        int i = 0, a;
        ingredientesTemporarios.clear();
        etapasTemporarias.clear();
        string nomeBuscado, novoNome, nomeVelho;
        int novoTempo;
        char o;

        cout << "\n--- BUSCAR RECEITA PARA EDITAR---" << endl;
        cout << "Digite o nome exato da receita: ";
        getline(cin >> ws, nomeBuscado); 

        auto receitaEncontrada = gerenciador.buscarPorNome(nomeBuscado);
        
        if (receitaEncontrada != nullptr) {
            nomeVelho = receitaEncontrada->getNome();
            cout << "\nDeseja editar o que nessa receita?" << endl;
            cout << "1- Nome \n2- Ingredientes\n3- Etapas\n4- Sair" << endl;
            o = lerChar();
            
            switch (o){
                case '1':
                    cout << "Digite o novo nome da receita: ";
                    getline(cin >> ws, novoNome);
                    
                    receitaEncontrada->setNome(novoNome);

                    cout << "\nReceita alterada com sucesso!\n"<<endl;
                    break;

                case '2':
                    cout << "Deseja:\n1- Adicionar ingredientes\n2- Remover ingredientes\n3- Sair ";
                    o = lerChar();
                    
                    if (o=='1'){
                        for(int i = 0; i < receitaEncontrada->getIngredientes().size(); i++){
                            cout << receitaEncontrada->getIngredientes()[i].getNome()<<"\n"<<endl;
                        }
                        adicionarIngredientesReceita(ingredientesTemporarios);
                        for (i = 0; i < ingredientesTemporarios.size(); i++){
                            gerenciador.adicionarIngrediente(nomeVelho, ingredientesTemporarios[i]);
                        }
                        if (i==1){
                            cout << "\nIngrediente adicionado com sucesso!"<<endl;
                        }else{
                            cout << "\nIngredientes adicionados com sucesso!"<<endl;
                        }
                    }else if(o=='2'){
                        for(int i = 0; i < receitaEncontrada->getIngredientes().size(); i++){
                            cout <<receitaEncontrada->getIngredientes()[i].getNome()<<endl;
                        }
                        cout << "\nDigite o nome do ingrediente que quer excluir: ";
                        getline (cin >> ws, novoNome);
                        for (i = 0; i < receitaEncontrada->getIngredientes().size(); i++){
                            if (receitaEncontrada->getIngredientes()[i].getNome() == novoNome){
                                a = receitaEncontrada->getIngredientes()[i].getId();
                                gerenciador.removerIngrediente(receitaEncontrada->getNome(), a);
                                cout << "\nIngrediente excluído com sucesso!"<<endl;
                                break;
                            }else{
                                continue;
                            }
                        }
                        if (i == receitaEncontrada->getIngredientes().size()){
                            cout << "\nIngrediente não encontrado na receita, tente novamente."<<endl;
                        }
                    }
                    else if (o=='3'){
                        cout << "\nSaindo...\n" << endl;
                        break;
                    }else{
                        cout << "\nNúmero inválido!\n" << endl;
                    }
                    break;

                case '3':
                    cout << "Deseja:\n1- Adicionar etapas\n2-Remover etapas\n3-Sair ";
                    o = lerChar();
                    if (o == '1'){
                        for (i = 0; i < receitaEncontrada->getEtapas().size(); i++){
                            cout << "\n" << i+1 << "-" << receitaEncontrada->getEtapas()[i].getAcao()
                                 << " em um(a) " << receitaEncontrada->getEtapas()[i].getRecipiente()
                                 << " por " << receitaEncontrada->getEtapas()[i].getTempo()
                                 << " minutos\n";
                        }
                        vector<Etapa>& etapasOficiais = receitaEncontrada->getEtapas();
                        
                        adicionarEtapasReceita(etapasOficiais, true);
                        
                        cout << "\nEtapas adicionadas e organizadas com sucesso!" << endl;

                    }else if(o=='2'){
                        cout << "Digite o numero da etapa que quer excluir: ";
                        for (i = 0; i < receitaEncontrada->getEtapas().size(); i++){
                            cout << "\n" << i+1 << "-" << receitaEncontrada->getEtapas()[i].getAcao()
                                 << " em um(a) " << receitaEncontrada->getEtapas()[i].getRecipiente()
                                 << " por " << receitaEncontrada->getEtapas()[i].getTempo()
                                 << " minutos\n";
                        }
                        novoTempo = lerInteiro();
                        if (gerenciador.removerEtapa(receitaEncontrada->getNome(), novoTempo - 1)) {
                            cout << "Etapa removida com sucesso!" << endl;
                        } else {
                            cout << "\nNúmero inválido!" << endl;
                        }
                    }
                    else if (o=='3'){
                        cout << "\nSaindo...\n" << endl;
                        break;
                    }else{
                        cout << "\nNúmero inválido!\n" << endl;
                    }
                    break;

                case '4':
                    cout << "\nSaindo ...\n" << endl;
                    break;

                default:
                    cout << "\nOpção inválida!\n" << endl;
                    return;
            }
        }
        else {
            cout << "\nOps! Nenhuma receita encontrada com o nome '" << nomeBuscado << "'.\n" << endl;
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
            cout << "\nDeseja excluir essa receita(s/n)?" << endl;
            cout << "-----------------------------------" << endl;
            o = lerChar();
            if (o == 's' || o == 'S'){
                if (gerenciador.removerReceita(receitaEncontrada) == true){
                    cout << "Operação executada com sucesso\n!" << endl;
                }
            }else {
                cout << "\nOperação cancelada\n" << endl;
            }
        } else {
            cout << "\nOps! Nenhuma receita encontrada com o nome '" << nomeBuscado << "'.\n" << endl;
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

    bool adicionarIngredientesReceita(vector<Ingrediente>& Ingredientes) {
        char continuar;
        do {
            string nome, unidade;

            cout << "Nome do ingrediente: ";
            getline(cin >> ws, nome);
            cout << "Qual a quantidade e unidade (g, ml, xícara...): ";
            getline(cin >> ws, unidade);

            for (size_t i = 0; i < Ingredientes.size(); i++) {
                if (Ingredientes[i].getNome() == nome) {
                    return false; 
                }
            }

            Ingrediente ingrediente(0, nome, unidade); 
            Ingredientes.push_back(ingrediente);

            cout << "Adicionar outro ingrediente? (s/n): ";
            continuar = lerChar();
        } while (continuar == 's' || continuar == 'S');
        return true;
    }

    void adicionarEtapasReceita(vector<Etapa>& Etapas, bool a = false) {
        char continuar, c;
        int b;
        string indentificador1, indentificador;

        do {
            Etapa etapa = perguntarEtapa();
            
            if (a) {
                cout << "Qual o numero da etapa que antecede essa? ";
                b = lerInteiro();
                
                if (b >= 0 && b < Etapas.size()) {
                    
                    cout << "Essa etapa antecede algum processo térmico(s/n)? ";
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
                    cout << "\n[Aviso] Posição inválida. Etapa adicionada ao final da lista." << endl;
                    Etapas.push_back(etapa);
                }

            } else {
                Etapas.push_back(etapa);
            }
            
            cout << "\nAdicionar outra etapa? (s/n): ";
            continuar = lerChar();
            
        } while (continuar == 's' || continuar == 'S');
    }

    Etapa perguntarEtapa(){
        string acao, recipiente;
        int tempo;

        cout << "Ação da etapa (ex: misturar, assar): ";
        getline(cin >> ws, acao);
        cout << "Recipiente utilizado: ";
        getline(cin >> ws, recipiente);
        cout << "Tempo da etapa (minutos): ";
        tempo = lerInteiro();
        

        return Etapa(acao, tempo, recipiente);
    }
    
};

#endif