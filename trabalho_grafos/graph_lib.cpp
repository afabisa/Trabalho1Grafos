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
//Função 1 --> Faz a BFS para vetor de adjacência
void BFS_tree_vector(const vector<vector<int>>& graph, int origem, string nome_do_arquivo_de_saida = "arvoreBFS.txt"){
    int INF = 1e9;
    vector<int> nivel(graph.size(), INF);
    vector<int> pai(graph.size(), INF);
    vector<bool> visitados(graph.size(), false);
    queue <int> fila;
    visitados[origem] = true;
    nivel[origem] = 0;
    pai[origem] = -1;
    fila.push(origem);
    while(!fila.empty()) {
        int atual = fila.front();
        fila.pop();
        for(int vizinho : graph[atual]){
            if(!visitados[vizinho]){
                fila.push(vizinho);
                visitados[vizinho] = true;
                nivel[vizinho] = nivel[atual] + 1;
                pai[vizinho] = atual;
            }       
        }       
    }

    ofstream arquivo_de_saida(nome_do_arquivo_de_saida);
    
    for(int i = 1; i < graph.size(); i++){
        arquivo_de_saida  << "Vértice: " << i << endl;
        arquivo_de_saida << "Nível: " << nivel[i] << endl;
        arquivo_de_saida << "Pai: " << pai[i] << '\n' << '\n';
    }

    cout << "Resultados gravados no arquivo " << nome_do_arquivo_de_saida << endl;
    arquivo_de_saida.close();

}
//Retorna o tempo de execução da BFS no vetor de adjacência
double BFS_tree_vector_with_execution_time(const vector<vector<int>>& graph, int origem, string nome_do_arquivo_de_saida = "arvoreBFS.txt"){
    using namespace std::chrono; 
    int INF = 1e9;
    vector<int> nivel(graph.size(), INF);
    vector<int> pai(graph.size(), INF);
    vector<bool> visitados(graph.size(), false);
    queue <int> fila;

    auto inicio = high_resolution_clock::now();

    visitados[origem] = true;
    nivel[origem] = 0;
    pai[origem] = -1;
    fila.push(origem);

    while(!fila.empty()) {
        int atual = fila.front();
        fila.pop();
        for(int vizinho : graph[atual]){
            if(!visitados[vizinho]){
                fila.push(vizinho);
                visitados[vizinho] = true;
                nivel[vizinho] = nivel[atual] + 1;
                pai[vizinho] = atual;
            }       
        }       
    }

    auto fim = high_resolution_clock::now(); // fim do algoritmo

    duration<double> tempo_execucao = fim - inicio;

    ofstream arquivo_de_saida(nome_do_arquivo_de_saida);
    
    for(int i = 1; i < graph.size(); i++){
        if (nivel[i] != INF) {
            arquivo_de_saida  << "Vértice: " << i << endl;
            arquivo_de_saida << "Nível: " << nivel[i] << endl;
            arquivo_de_saida << "Pai: " << pai[i] << '\n' << '\n';
        }
    }

    //cout << "Resultados gravados no arquivo " << nome_do_arquivo_de_saida << endl;
    arquivo_de_saida.close();

    return tempo_execucao.count();

}

//Faz a DFS para vetor de adjacência
void DFS_tree_vector(const vector<vector<int>>& graph, int origem, string nome_do_arquivo_de_saida = "arvoreDFS.txt") {
    int INF = 1e9;
    vector<int> nivel(graph.size(), INF);
    vector<int> pai(graph.size(), INF);
    vector<bool> visitados(graph.size(), false);
    stack<int> pilha;

    visitados[origem] = true;
    nivel[origem] = 0;
    pai[origem] = -1;
    pilha.push(origem);

    while (!pilha.empty()) {
        int atual = pilha.top();
        pilha.pop();
        for (int vizinho : graph[atual]) {
            if (!visitados[vizinho]) {
                pilha.push(vizinho);
                visitados[vizinho] = true;
                nivel[vizinho] = nivel[atual] + 1;
                pai[vizinho] = atual;
            }
        }
    }

    ofstream arquivo_de_saida(nome_do_arquivo_de_saida);

    for (int i = 1; i < graph.size(); i++) {

        arquivo_de_saida << "Vértice: " << i << endl;
        arquivo_de_saida << "Nível: " << nivel[i] << endl;
        arquivo_de_saida << "Pai: " << pai[i] << '\n' << '\n';
        
    }

    arquivo_de_saida.close();
    
    cout << "Resultados gravados no arquivo " << nome_do_arquivo_de_saida << endl;

}
//Retorna o tempo de execução da DFS para vetor de adjacência
double DFS_tree_vector_with_execution_time(const vector<vector<int>>& graph, int origem, string nome_do_arquivo_de_saida = "arvoreDFS.txt") {
    using namespace std::chrono; 

    int INF = 1e9;
    vector<int> nivel(graph.size(), INF);
    vector<int> pai(graph.size(), INF);
    vector<bool> visitados(graph.size(), false);
    stack<int> pilha;
    
    auto inicio = high_resolution_clock::now(); // início do algoritmo

    visitados[origem] = true;
    nivel[origem] = 0;
    pai[origem] = -1;
    pilha.push(origem);

    while (!pilha.empty()) {
        int atual = pilha.top();
        pilha.pop();
        for (int vizinho : graph[atual]) {
            if (!visitados[vizinho]) {
                pilha.push(vizinho);
                visitados[vizinho] = true;
                nivel[vizinho] = nivel[atual] + 1;
                pai[vizinho] = atual;
            }
        }
    }


    auto fim = high_resolution_clock::now(); // fim do algoritmo

    duration<double> tempo_execucao = fim - inicio;

    ofstream arquivo_de_saida(nome_do_arquivo_de_saida);

    for (int i = 1; i < graph.size(); i++) {
        arquivo_de_saida << "Vértice: " << i << endl;
        arquivo_de_saida << "Nível: " << nivel[i] << endl;
        arquivo_de_saida << "Pai: " << pai[i] << '\n' << '\n';

    }

    arquivo_de_saida.close();
    
   // cout << "Resultados gravados no arquivo " << nome_do_arquivo_de_saida << endl;
    return tempo_execucao.count();

}
//Faz o diâmetro aproximado da matriz de adjacência
int Approximate_diameter_vector(const vector<vector<int>>& graph){
    int max_distancia = 0;
    for(int i = 0; i < 5000; i ++){
        vector<int> dist(graph.size(), -1);
        int origem = rand() % graph.size();
        dist[origem] = 0;
        queue <int> fila;
        fila.push(origem);
        while(!fila.empty()) {
            int atual = fila.front();
            fila.pop();
            for(int vizinho : graph[atual]){
                if(dist[vizinho] == -1){
                    dist[vizinho] = dist[atual] + 1;
                    fila.push(vizinho);
                    if (dist[vizinho] > max_distancia) {
                        max_distancia = dist[vizinho];
                    }
                }       
            }       
        }  
    }
    cout << "Diametro do grafo aproximado: " << max_distancia << endl;
}

//Faz o diâmetro real da vetor de adjacência
int Diameter_vector(const vector<vector<int>>& graph){

    if(graph.size() >= 500000){
        return Approximate_diameter_vector(graph);
    }
    else{
        int max_distancia = 0;
        for(int i = 1; i < graph.size(); i ++){
            vector<int> dist(graph.size(), -1);
            int origem = i;
            dist[origem] = 0;
            queue <int> fila;
            fila.push(origem);
            while(!fila.empty()) {
                int atual = fila.front();
                fila.pop();
                for(int vizinho : graph[atual]){
                    if(dist[vizinho] == -1){
                        dist[vizinho] = dist[atual] + 1;
                        fila.push(vizinho);
                        if (dist[vizinho] > max_distancia) {
                            max_distancia = dist[vizinho];
                        }
                    }       
                }       
            }  
        }
        cout << "Diametro do grafo: " << max_distancia << endl;
    }
}


//Imprime a distância entre dois pontos
void Distance_vector(const vector<vector<int>>& graph, int origem, int destino){
    vector<int> dist(graph.size(), -1);
    vector<bool> visitados(graph.size(), false);
    queue <int> fila;
    int distancia = -1;
    visitados[origem] = true;
    dist[origem] = 0;
    fila.push(origem);
    while(!fila.empty()) {
        int atual = fila.front();
        fila.pop();
        for(int vizinho : graph[atual]){
            if(!visitados[vizinho]){
                fila.push(vizinho);
                visitados[vizinho] = true;
                dist[vizinho] = dist[atual] + 1;
                if(vizinho == destino){    
                    distancia = dist[vizinho];
                    cout << "A distancia entre " << origem << " e " << destino << " igual a: " << distancia << endl;
                    return;
                }
            }       
        }       
    }
    cout << "Impossivel ligar os vertices "  << origem << " e " << destino << "." << endl;
} 
//Todas as funções para matriz de adjacência 
vector<vector<bool>> txt_to_adjacency_matrix(const string& nome_arquivo, string nome_do_arquivo_de_saida_principal = "resultados.txt") {
    
    ifstream arquivo(nome_arquivo);
    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo de entrada!");
    }

    int numVertices, numArestas, u, v, degreeSum;
    
    // Ler o número de vértices
    arquivo >> numVertices;
    numArestas = 0;
    degreeSum = 0;

    // Inicializar o vetor de graus e a matriz de adjacência com base no número de vértices
    vector<int> degrees(numVertices + 1, 0);
    vector<vector<bool>> matrix(numVertices + 1, vector<bool>(numVertices + 1, false));

    // Ler as arestas e preencher a matriz de adjacência
    while (arquivo >> u >> v) {
        matrix[u][v] = true;  
        matrix[v][u] = true; 

        numArestas++;
        degrees[u]++;
        degrees[v]++;
        degreeSum += 2;
    }

    arquivo.close();

    // Ordenar os graus
    sort(degrees.begin() + 1, degrees.end());

    // Encontrar grau máximo, mínimo e calcular estatísticas
    int maxDegree = degrees[numVertices];
    int minDegree = degrees[1];
    double averageDegree = static_cast<double>(degreeSum) / numVertices;
    double medianDegree;

    // Calcular a mediana do grau
    if (numVertices % 2 == 0) {
        medianDegree = (degrees[numVertices / 2] + degrees[(numVertices / 2) + 1]) / 2.0;
    } else {
        medianDegree = degrees[(numVertices + 1) / 2];
    }

    // Função para calcular componentes conexas
    vector<vector<int>> componentes;
    vector<int> tamanhos;
    int quant_componentes = 0;
    vector<bool> visitados(matrix.size(), false);
    queue<int> fila;
    int iterador = 0;

    for (int node = 1; node < matrix.size(); node++) {
        if (!visitados[node]) {
            quant_componentes++;
            componentes.push_back(vector<int>()); 
            tamanhos.push_back(0); 
            fila.push(node);
            visitados[node] = true;
            componentes[iterador].push_back(node);
            tamanhos[iterador]++;

            while (!fila.empty()) {
                int atual = fila.front();
                fila.pop();

                for (int vizinho = 1; vizinho < matrix.size(); vizinho++) {
                    if (matrix[atual][vizinho] && !visitados[vizinho]) {
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

    sort(componentes.begin(), componentes.end(), [](const vector<int>& a, const vector<int>& b) {
        return a.size() > b.size();
    });

    sort(tamanhos.begin(), tamanhos.end());
    reverse(tamanhos.begin(), tamanhos.end());

    // Gravar os resultados no arquivo de saída
    ofstream arquivo_de_saida(nome_do_arquivo_de_saida_principal, std::ios::app);

    if (arquivo_de_saida.is_open()) {
        arquivo_de_saida << "Número de vértices: " << numVertices << endl;
        arquivo_de_saida << "Número de arestas: " << numArestas << endl;
        arquivo_de_saida << "Grau mínimo: " << minDegree << endl;
        arquivo_de_saida << "Grau máximo: " << maxDegree << endl;
        arquivo_de_saida << "Grau médio: " << averageDegree << endl;
        arquivo_de_saida << "Mediana de grau: " << medianDegree << endl;

        // Adicionar os resultados das componentes conexas
        arquivo_de_saida << "Número de componentes conexas: " << quant_componentes << endl << endl;
        for (int j = 0; j < tamanhos.size(); j++) {
            arquivo_de_saida << "Componente " << j + 1 << " tem " << tamanhos[j] << " vértices, e eles são: " << endl;
            for (int i = 0; i < componentes[j].size(); i++) {
                arquivo_de_saida << componentes[j][i] << " ";
            }
            arquivo_de_saida << endl << endl << endl;

        }

        arquivo_de_saida.close(); 
        cout << "Resultados gravados no arquivo " << nome_do_arquivo_de_saida_principal << endl;
    } else {
        cout << "Erro ao abrir o arquivo de resultados!" << endl;
    }

    return matrix;
}

void BFS_tree_matrix(const vector<vector<bool>>& matrix, int origem, string nome_do_arquivo_de_saida = "arvoreBFS.txt"){
    int INF = 1e9;
    vector<int> nivel(matrix.size(), INF);
    vector<int> pai(matrix.size(), INF);
    vector<bool> visitados(matrix.size(), false);
    queue <int> fila;
    visitados[origem] = true;
    nivel[origem] = 0;
    pai[origem] = -1;
    fila.push(origem);
    while(!fila.empty()){
        int atual = fila.front();
        fila.pop();
        for(int vizinho = 1; vizinho < matrix.size(); vizinho ++){
            if(matrix[atual][vizinho] == 1 & !visitados[vizinho]){
                fila.push(vizinho);
                visitados[vizinho] = true;
                nivel[vizinho] = nivel[atual] + 1;
                pai[vizinho] = atual;
            }
        }      
    }

    ofstream arquivo_de_saida(nome_do_arquivo_de_saida);
    
    for(int i = 1; i < matrix.size(); i++){
        arquivo_de_saida  << "Vértice: " << i << endl;
        arquivo_de_saida << "Nível: " << nivel[i] << endl;
        arquivo_de_saida << "Pai: " << pai[i] << '\n' << '\n';
    }

    cout << "Resultados gravados no arquivo " << nome_do_arquivo_de_saida << endl;
    arquivo_de_saida.close();

}

double BFS_tree_matrix_with_execution_time(const vector<vector<bool>>& matrix, int origem, string nome_do_arquivo_de_saida = "arvoreBFS.txt"){
    using namespace std::chrono;

    int INF = 1e9;
    vector<int> nivel(matrix.size(), INF);
    vector<int> pai(matrix.size(), INF);
    vector<bool> visitados(matrix.size(), false);
    queue <int> fila;

    auto inicio = high_resolution_clock::now();

    visitados[origem] = true;
    nivel[origem] = 0;
    pai[origem] = -1;
    fila.push(origem);
    while(!fila.empty()){
        int atual = fila.front();
        fila.pop();
        for(int vizinho = 1; vizinho < matrix.size(); vizinho ++){
            if(matrix[atual][vizinho] == 1 & !visitados[vizinho]){
                fila.push(vizinho);
                visitados[vizinho] = true;
                nivel[vizinho] = nivel[atual] + 1;
                pai[vizinho] = atual;
            }
        }      
    }

    auto fim = high_resolution_clock::now(); // fim do algoritmo

    duration<double> tempo_execucao = fim - inicio;

    ofstream arquivo_de_saida(nome_do_arquivo_de_saida);
    
    for(int i = 1; i < matrix.size(); i++){
        
            arquivo_de_saida  << "Vértice: " << i << endl;
            arquivo_de_saida << "Nível: " << nivel[i] << endl;
            arquivo_de_saida << "Pai: " << pai[i] << '\n' << '\n';
    }


    //cout << "Resultados gravados no arquivo " << nome_do_arquivo_de_saida << endl;
    arquivo_de_saida.close();

    return tempo_execucao.count();

}

void DFS_tree_matrix(const vector<vector<bool>>& matrix, int origem, string nome_do_arquivo_de_saida = "arvoreDFS.txt"){
    int INF = 1e9;
    vector<int> nivel(matrix.size(), INF);
    vector<int> pai(matrix.size(), INF);
    vector<bool> visitados(matrix.size(), false);
    stack <int> pilha;
    visitados[origem] = true;
    nivel[origem] = 0;
    pai[origem] = -1;
    pilha.push(origem);
    while(!pilha.empty()){
        int atual = pilha.top();
        pilha.pop();
        for(int vizinho = 1; vizinho < matrix.size(); vizinho ++){
            if(matrix[atual][vizinho] == 1 & !visitados[vizinho]){
                pilha.push(vizinho);
                visitados[vizinho] = true;
                nivel[vizinho] = nivel[atual] + 1;
                pai[vizinho] = atual;
            }
        }      
    }

    ofstream arquivo_de_saida(nome_do_arquivo_de_saida);
    
    for(int i = 1; i < matrix.size(); i++){
        if (nivel[i] != 1e9) {

            arquivo_de_saida  << "Vértice: " << i << endl;
            arquivo_de_saida << "Nível: " << nivel[i] << endl;
            arquivo_de_saida << "Pai: " << pai[i] << '\n' << '\n';

        }
    }

    cout << "Resultados gravados no arquivo " << nome_do_arquivo_de_saida << endl;
    arquivo_de_saida.close();

}

double DFS_tree_matrix_with_execution_time(const vector<vector<bool>>& matrix, int origem, string nome_do_arquivo_de_saida = "arvoreDFS.txt"){
    using namespace std::chrono;

    int INF = 1e9;
    vector<int> nivel(matrix.size(), INF);
    vector<int> pai(matrix.size(), INF);
    vector<bool> visitados(matrix.size(), false);
    stack <int> pilha;

    auto inicio = high_resolution_clock::now(); // início do algoritmo


    visitados[origem] = true;
    nivel[origem] = 0;
    pai[origem] = -1;
    pilha.push(origem);
    while(!pilha.empty()){
        int atual = pilha.top();
        pilha.pop();
        for(int vizinho = 1; vizinho < matrix.size(); vizinho ++){
            if(matrix[atual][vizinho] && !visitados[vizinho]){
                pilha.push(vizinho);
                visitados[vizinho] = true;
                nivel[vizinho] = nivel[atual] + 1;
                pai[vizinho] = atual;
            }
        }      
    }

    auto fim = high_resolution_clock::now(); // fim do algoritmo

    duration<double> tempo_execucao = fim - inicio;

    ofstream arquivo_de_saida(nome_do_arquivo_de_saida);
    
    for(int i = 1; i < matrix.size(); i++){
        if (nivel[i] != 1e9) {

            arquivo_de_saida  << "Vértice: " << i << endl;
            arquivo_de_saida << "Nível: " << nivel[i] << endl;
            arquivo_de_saida << "Pai: " << pai[i] << '\n' << '\n';

        }
    }

    //cout << "Resultados gravados no arquivo " << nome_do_arquivo_de_saida << endl;
    arquivo_de_saida.close();

    return tempo_execucao.count();

}

int Approximate_diameter_matrix(const vector<vector<bool>>& matrix){
    int max_distancia = 0;
    for(int i = 0; i < 5000; i ++){
        vector<int> dist(matrix.size(), -1);
        int origem = rand() % matrix.size();
        dist[origem] = 0;
        queue <int> fila;
        fila.push(origem);
        while(!fila.empty()) {
            int atual = fila.front();
            fila.pop();
            for(int vizinho = 1; vizinho < matrix.size(); vizinho++){
                if(matrix[atual][vizinho] && dist[vizinho] == -1){
                    dist[vizinho] = dist[atual] + 1;
                    fila.push(vizinho);
                    if (dist[vizinho] > max_distancia) {
                        max_distancia = dist[vizinho];
                    }
                }       
            }       
        }  
    }
    cout << "Diametro do grafo aproximado: " << max_distancia << endl;
}
 

int Diameter_matrix(const vector<vector<bool>>& matrix){

    if(matrix.size() >= 500000){
        return Approximate_diameter_matrix(matrix);
    }
    else{
        int max_distancia = 0;
        for(int i = 1; i < matrix.size(); i ++){
            vector<int> dist(matrix.size(), -1);
            int origem = i;
            dist[origem] = 0;
            queue <int> fila;
            fila.push(origem);
            while(!fila.empty()) {
                int atual = fila.front();
                fila.pop();
                for(int vizinho = 1; vizinho < matrix.size(); vizinho++){
                    if(matrix[atual][vizinho] && dist[vizinho] == -1){
                        dist[vizinho] = dist[atual] + 1;
                        fila.push(vizinho);
                        if (dist[vizinho] > max_distancia) {
                            max_distancia = dist[vizinho];
                        }
                    }       
                }       
            }  
        }
        cout << "Diametro do grafo: " << max_distancia << endl;
    }
}


void Distance_matrix(const vector<vector<bool>>& matrix, int origem, int destino){
    vector<int> dist(matrix.size(), -1);
    vector<bool> visitados(matrix.size(), false);
    queue <int> fila;
    int distancia = -1;
    visitados[origem] = true;
    dist[origem] = 0;
    fila.push(origem);
    while(!fila.empty()) {
        int atual = fila.front();
        fila.pop();
        for(int vizinho = 1; vizinho < matrix.size(); vizinho++){
            if(matrix[atual][vizinho] && !visitados[vizinho]){
                fila.push(vizinho);
                visitados[vizinho] = true;
                dist[vizinho] = dist[atual] + 1;
                if(vizinho == destino){   
                    distancia = dist[vizinho];
                    cout << "A distancia entre " << origem << " e " << destino << " igual a: " << distancia << endl; 
                    return;
                }
            }       
        }       
    }
    cout << "Impossivel ligar os vertices " << origem << " e " << destino << "." << endl;
} 

//Representação visual 
import 'package:flutter/material.dart';

class RecyclingScreen extends StatelessWidget {
  const RecyclingScreen({super.key});

  @override
  Widget build(BuildContext context) {
    final categories = [
      {
        'label': 'Papel',
        'color': const Color(0xFF8CCDED),
        'icon': Icons.article,
        'info': 'A reciclagem do papel desempenha um papel fundamental na preservação ambiental, pois reduz a necessidade de derrubar árvores para produzir mais papel. A indústria do papel é uma das maiores responsáveis pelo desmatamento e pela emissão de gases de efeito estufa, e, ao reciclar o papel, evitamos essas consequências negativas. Além disso, a reciclagem de papel consome menos energia e água do que a produção de papel novo a partir de madeira. Isso contribui para uma menor emissão de poluentes na atmosfera e para a preservação dos recursos hídricos, essenciais para a vida na Terra. O papel reciclado também ajuda a diminuir o volume de lixo nos aterros sanitários, evitando o acúmulo de resíduos e a poluição do solo e das águas. Portanto, a reciclagem do papel é uma maneira eficaz de reduzir o impacto ambiental e promover a sustentabilidade.',
        'recyclables': ['Jornal', 'Revista', 'Folha de caderno', 'Caixa de papelão', 'Caixa de sapato'],
        'nonRecyclables': ['Papel engordurado', 'Papel toalha usado', 'Guardanapo usado', 'Papel higiênico usado', 'Papel plastificado'],
      },
      {
        'label': 'Plástico',
        'color': const Color(0xFFFF8585),
        'icon': Icons.local_drink,
         'info': 'A reciclagem do plástico é uma das questões mais urgentes para a preservação do meio ambiente. O plástico, quando descartado de forma inadequada, pode levar centenas de anos para se decompor, causando sérios danos aos ecossistemas e à vida selvagem. Ao reciclar plásticos, conseguimos reduzir o impacto ambiental causado pela produção de plástico novo e pela poluição nos oceanos e no solo. A reciclagem de plástico diminui a necessidade de extração de petróleo, que é a principal matéria-prima para a fabricação de plásticos, ajudando a preservar os recursos naturais e reduzir a emissão de gases de efeito estufa. Além disso, a reciclagem de plásticos reduz a quantidade de resíduos sólidos nos aterros sanitários e diminui a poluição do ambiente. Embora a reciclagem do plástico seja desafiadora devido à variedade de tipos de plásticos, é uma etapa essencial para um futuro mais sustentável e para a preservação dos ecossistemas marinhos e terrestres.',
        'recyclables': ['Garrafa PET', 'Embalagem plástica', 'Sacola plástica', 'Copo plástico', 'Embalagem de iogurte'],
        'nonRecyclables': ['Canudo plástico', 'Plástico contaminado com alimentos', 'Filme plástico', 'Plástico bolha', 'Talher plástico'],
      },
      {
        'label': 'Metal',
        'color': const Color(0xFFFCE95A),
        'icon': Icons.build,
        'info': 'A reciclagem de metais é uma das formas mais eficientes de preservar os recursos naturais e reduzir os impactos ambientais da extração de minérios. O processo de extração de metais da natureza, como o alumínio e o aço, exige grande quantidade de energia e causa a degradação dos ecossistemas. Ao reciclar metais, como latas de alumínio ou sucata de ferro, conseguimos economizar até 95% da energia que seria utilizada na produção de metal novo. Além disso, a reciclagem de metais evita a exploração de recursos finitos, preservando os ecossistemas e reduzindo a poluição ambiental. A reciclagem de metais também diminui as emissões de gases de efeito estufa, pois exige menos energia do que a produção a partir de minérios, contribuindo para a luta contra as mudanças climáticas. Em resumo, a reciclagem de metais é crucial para a conservação de recursos e a redução dos impactos ambientais negativos.',
        'recyclables': ['Lata de alumínio', 'Lata de alimento', 'Fio de cobre', 'Tampa de frasco', 'Recipiente de metal limpo'],
        'nonRecyclables': ['Panela', 'Metal contaminado', 'Frigideira', 'Lata de alimento não limpa', 'Seringa de metal'],
      },
      {
        'label': 'Vidro',
        'color': const Color(0xFF94E47C),
        'icon': Icons.wine_bar,
          'info': 'A reciclagem de vidro é uma prática essencial para a preservação do meio ambiente, pois o vidro é 100% reciclável e pode ser reutilizado sem perder a qualidade. Ao reciclar vidro, evitamos a necessidade de extrair matérias-primas como areia, calcário e soda, o que reduz o impacto ambiental da mineração e da exploração de recursos naturais. Além disso, a reciclagem de vidro consome muito menos energia do que a produção de vidro novo, ajudando a reduzir a emissão de gases poluentes e a contribuir para a redução do aquecimento global. A reciclagem de vidro também diminui a quantidade de resíduos nos aterros sanitários, ajudando a evitar o acúmulo de lixo e a poluição do solo e da água. Como o vidro pode ser reciclado infinitamente sem perder suas propriedades, ele é uma das opções mais sustentáveis para a redução de resíduos e a preservação do meio ambiente.',
        'recyclables': ['Garrafa de vidro', 'Pote de vidro', 'Frasco de vidro', 'Copo de vidro', 'Vidro de medicamento'],
        'nonRecyclables': ['Vidro quebrado', 'Vidro de cerâmica', 'Lâmpada de vidro', 'Vidro temperado', 'Espelho'],
      },
      {
        'label': 'Pilha',
        'color': const Color(0xFFF9AD43),
        'icon': Icons.battery_full,
          'info': 'A reciclagem de pilhas é crucial para evitar a contaminação do solo e da água com substâncias tóxicas e metais pesados presentes nas pilhas. Quando as pilhas são descartadas incorretamente, elas podem vazar substâncias perigosas, como mercúrio, cádmio e chumbo, que são altamente poluentes e prejudiciais à saúde humana e animal. A reciclagem de pilhas ajuda a recuperar esses metais preciosos e evita que eles se acumulem no meio ambiente. Além disso, a reciclagem de pilhas reduz a necessidade de minerar esses metais, contribuindo para a preservação dos recursos naturais. O processo de reciclagem de pilhas também diminui a quantidade de resíduos tóxicos nos aterros sanitários, reduzindo o impacto ambiental e melhorando a saúde do ecossistema. Dessa forma, a reciclagem de pilhas é uma prática essencial para a segurança ambiental e para a conservação dos recursos naturais.',
        'recyclables': ['Pilha alcalina', 'Pilha de lítio', 'Pilha recarregável', 'Pilha de zinco-carbono', 'Bateria recarregável de celular e laptop'],
        'nonRecyclables': ['Pilha de mercúrio', 'Pilha danificada ou vazando', 'Pilha de cádmio', 'Bateria de automóvel', 'Pilha de aparelho de audição'],
      },
    ];

    return Scaffold(
      appBar: AppBar(
        title: const Text('Reciclagem'),
        backgroundColor: const Color(0xFF67AB67),
        leading: IconButton(
          icon: const Icon(Icons.arrow_back),
          onPressed: () {
            Navigator.pushNamed(context, '/profile_selection_screen');
          },
        ),
      ),
      body: ListView.builder(
        padding: const EdgeInsets.all(16.0),
        itemCount: categories.length,
        itemBuilder: (context, index) {
          final Map<String, dynamic> category = categories[index];
          return Container(
            margin: const EdgeInsets.symmetric(vertical: 8.0),
            child: ClipRRect(
              borderRadius: BorderRadius.circular(15),
              child: Material(
                color: category['color'] as Color,
                child: InkWell(
                  splashColor: Colors.transparent,
                  highlightColor: Colors.transparent,
                  onTap: () {},
                  child: ExpansionTile(
                    tilePadding: const EdgeInsets.symmetric(horizontal: 16.0),
                    leading: Icon(
                      category['icon'] as IconData,
                      size: 30,
                      color: Colors.black54,
                    ),
                    title: Text(
                      category['label'] as String,
                      style: const TextStyle(
                        fontSize: 18,
                        fontWeight: FontWeight.bold,
                      ),
                    ),
                    children: [
                      Container(
                        color: Colors.white, // Define o fundo branco
                        padding: const EdgeInsets.all(16.0),
                        child: Column(
                          children: [
                            Text(
                              category['info'] as String,
                              style: const TextStyle(fontSize: 16),
                              textAlign: TextAlign.justify,
                            ),
                            const SizedBox(height: 16),
                            Row(
                              mainAxisAlignment: MainAxisAlignment.center,
                              crossAxisAlignment: CrossAxisAlignment.start,
                              children: [
                                // Coluna para itens recicláveis
                                Expanded(
                                  child: Column(
                                    crossAxisAlignment: CrossAxisAlignment.start,
                                    children: List.generate(
                                      (category['recyclables'] as List<String>).length,
                                      (index) {
                                        return ListTile(
                                          leading: const Icon(Icons.check, color: Colors.green),
                                          title: Text(
                                            category['recyclables'][index] as String,
                                            style: const TextStyle(fontSize: 14),
                                          ),
                                        );
                                      },
                                    ),
                                  ),
                                ),
                                const SizedBox(width: 16),
                                // Coluna para itens não recicláveis
                                Expanded(
                                  child: Column(
                                    crossAxisAlignment: CrossAxisAlignment.start,
                                    children: List.generate(
                                      (category['nonRecyclables'] as List<String>).length,
                                      (index) {
                                        return ListTile(
                                          leading: const Icon(Icons.close, color: Colors.red),
                                          title: Text(
                                            category['nonRecyclables'][index] as String,
                                            style: const TextStyle(fontSize: 14),
                                          ),
                                        );
                                      },
                                    ),
                                  ),
                                ),
                              ],
                            ),
                          ],
                        ),
                      ),
                    ],
                  ),
                ),
              ),
            ),
          );
        },
      ),
      bottomNavigationBar: BottomNavigationBar(
        type: BottomNavigationBarType.fixed,
        backgroundColor: const Color(0xFF67AB67),
        selectedItemColor: Colors.white,
        unselectedItemColor: Colors.black54,
        items: const <BottomNavigationBarItem>[
          BottomNavigationBarItem(
            icon: Icon(Icons.recycling),
            label: 'Reciclagem',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.home),
            label: 'Início',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.bar_chart),
            label: 'Ranking',
          ),
        ],
        onTap: (index) {
          switch (index) {
            case 0:
              break;
            case 1:
              Navigator.pushNamed(context, '/home_screen');
              break;
            case 2:
              Navigator.pushNamed(context, '/ranking');
              break;
          }
        },
      ),
    );
  }
}
