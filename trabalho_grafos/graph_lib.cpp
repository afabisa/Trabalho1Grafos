//Bibliotecas de Inicialização
#include <iostream> //entrada e saída no console 
#include <fstream> //classes de leitura, escrita e leitura/escrita
#include <bits/stdc++.h> //algumas bibliotecas a mais
#include <chrono> //manipulação de tempo 
using namespace std;

//estrutura: tipo de retorno é um vetor de vetores. Entrada é um arquivo de string. 
vector<vector<int>> txt_to_adjacency_vector(const string& nome_arquivo, string nome_do_arquivo_de_saida_principal = "resultados.txt") {

//Tratamento de erros: abertura do arquivo
    ifstream arquivo(nome_arquivo);
    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo de entrada!");
    }
//Depois de aberto, Declaração de variáveis inteiras
    int numVertices, numArestas, u, v, degreeSum;
    arquivo >> numVertices; //lê o primeiro número do arquivo
    numArestas = 0; //qtd de arestas lidas
    degreeSum = 0; //soma dos graus dos vértices

    //Cria um vetor com o grau de cada vértice.
    vector<int> degrees(numVertices + 1, 0);

    //Cria o vetor de adjacências
    vector<vector<int>> graph(numVertices + 1);

    //lê os pares de vértices e adiciona no vetor de adjacências
    while (arquivo >> u >> v) {
        graph[u].push_back(v); //adiciona v na lista de vizinhos de u
        graph[v].push_back(u); //adiciona u na lista de vizinhos de v

        numArestas++; 
        degrees[u]++; 
        degrees[v]++;
        degreeSum += 2; //cada aresta aumenta a soma dos graus em 2. 
    }

    arquivo.close();
