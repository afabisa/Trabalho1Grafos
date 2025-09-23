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

    // Ordenar os graus
    sort(degrees.begin() + 1, degrees.end()); 

    // Encontrar grau máximo, mínimo e calcular estatísticas
    int maxDegree = degrees[numVertices];
    int minDegree = degrees[1];
    double averageDegree = static_cast<double>(degreeSum) / numVertices;
    double medianDegree; //declarando variável para mediana

    // Calcular a mediana do grau
    if (numVertices % 2 == 0) {
        medianDegree = (degrees[numVertices / 2] + degrees[(numVertices / 2) + 1]) / 2.0;
    } else {
        medianDegree = degrees[(numVertices + 1) / 2];
    }

    // Função para calcular componentes conexas
    vector<vector<int>> componentes; //vetor de componentes
    vector<int> tamanhos; //vetor com o tamanho de cada componente
    int quant_componentes = 0; //número de componentes
    vector<bool> visitados(graph.size(), false); //vetor que indica se o nó foi visitado ou não. 
    queue<int> fila;
    int iterador = 0; 

    for (int node = 1; node < graph.size(); node++) { //percorrendo os vértices do grafo
        if (!visitados[node]) { //verifica se o vértice não foi visitado
            quant_componentes++;
            componentes.push_back(vector<int>()); //adiciona um vetor vazio no vetor de componentes
            tamanhos.push_back(0); //adiciona um valor no vetor com o tamanho das componentes. 
            fila.push(node); //adiciona o vértice na fila 
            visitados[node] = true; //marca o vértice como visitado
            componentes[iterador].push_back(node); //adiciona o vértice no vetor da componente
            tamanhos[iterador]++;//incrementa o tamanho da componente atual (em 1)

            while (!fila.empty()) { 
                //obtém e remove o vértice da fila
                int atual = fila.front(); 
                fila.pop(); 

                for (int vizinho : graph[atual]) { 
                    //para cada vizinho do vértice atual, verificar se foi visitado. 
                    // Se não, colocar o vizinho na fila. 
                    // Alterar valor no vetor de visitados para 1 (true)
                    // Adicionar vizinho na sua componente
                    // Incrementar o tamanho da componente no vetor de tamanhos. 
                    if (!visitados[vizinho]) {
                        fila.push(vizinho);
                        visitados[vizinho] = true;
                        componentes[iterador].push_back(vizinho);
                        tamanhos[iterador]++;
                    }
                }
            }
            iterador++;
        }
    }
    //ordena componentes em ordem decrescente
    sort(componentes.begin(), componentes.end(), [](const vector<int>& a, const vector<int>& b) {
        return a.size() > b.size();
    }); 
    sort(tamanhos.begin(), tamanhos.end()); 
    reverse(tamanhos.begin(), tamanhos.end()); //coloca vetor de tamanhos em ordem decrescente

    // Gravar os resultados no arquivo de saída no modo append (adiciona ao final do arquivo)
    ofstream arquivo_de_saida(nome_do_arquivo_de_saida_principal, std::ios::app);

    if (arquivo_de_saida.is_open()) {
        arquivo_de_saida << "Número de vértices: " << numVertices << endl;
        arquivo_de_saida << "Número de arestas: " << numArestas << endl;
        arquivo_de_saida << "Grau mínimo: " << minDegree << endl;
        arquivo_de_saida << "Grau máximo: " << maxDegree << endl;
        arquivo_de_saida << "Grau médio: " << averageDegree << endl;
        arquivo_de_saida << "Mediana de grau: " << medianDegree << '\n' << endl;

        // Adicionar os resultados das componentes conexas
        arquivo_de_saida << "Número de componentes conexas: " << quant_componentes << endl << endl;
        for (int j = 0; j < tamanhos.size(); j++) {
            arquivo_de_saida << "Componente " << j + 1 << " tem " << tamanhos[j] << " vértices, e eles são: " << endl;
            for (int i = 0; i < componentes[j].size(); i++) {
                arquivo_de_saida << componentes[j][i] << " ";
            }
            arquivo_de_saida << endl << endl << endl;
        }
        //Salva o arquivo e sinaliza no terminal. 
        arquivo_de_saida.close();
        cout << "Resultados gravados no arquivo " << nome_do_arquivo_de_saida_principal << endl;
    } else {
        cout << "Erro ao abrir o arquivo de resultados!" << endl;
    }

        return graph;
}
