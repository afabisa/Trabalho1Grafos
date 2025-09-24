#ifndef GRAPH_H 
#define GRAPH_H

#include <vector>
#include <fstream>
using namespace std;

// Funções de receber entrada

vector<vector<bool>> txt_to_adjacency_matrix(const string& nome_arquivo, string nome_do_arquivo_de_saida_principal = "resultados.txt");
vector<vector<int>> txt_to_adjacency_vector(const string& nome_arquivo, string nome_do_arquivo_de_saida_principal = "resultados.txt");

// Funções para percorrer o grafo (vetor de adjacência):

void BFS_tree_vector(const vector<vector<int>>& graph, int origem, string nome_do_arquivo_de_saida = "arvoreBFS.txt");
void DFS_tree_vector(const vector<vector<int>>& graph, int origem, string nome_do_arquivo_de_saida = "arvoreDFS.txt");

// Funções de diâmetro e distância entre dois vértices para vetor de adjacência

void Distance_vector(const vector<vector<int>>& graph, int origem, int destino);
void Approximate_diameter_vector(const vector<vector<int>>& graph);
void Diameter_vector(const vector<vector<int>>& graph);

// Funções para percorrer o grafo (matriz de adjacência):

void DFS_tree_matrix(const vector<vector<bool>>& matrix, int origem, string nome_do_arquivo_de_saida = "arvoreDFS.txt");
void BFS_tree_matrix(const vector<vector<bool>>& matrix, int origem, string nome_do_arquivo_de_saida = "arvoreBFS.txt");

//Funções de diâmetro e distância entre dois vértices para matriz de adjacência

void Distance_matrix(const vector<vector<bool>>& matrix, int origem, int destino);
void Approximate_diameter_matrix(const vector<vector<bool>>& matrix);
void Diameter_matrix(const vector<vector<bool>>& matrix);

// Contabilizando o tempo:

double DFS_tree_vector_with_execution_time(const vector<vector<int>>& graph, int origem, string nome_do_arquivo_de_saida = "arvoreDFS.txt");
double BFS_tree_vector_with_execution_time(const vector<vector<int>>& graph, int origem, string nome_do_arquivo_de_saida = "arvoreBFS.txt");

double DFS_tree_matrix_with_execution_time(const vector<vector<bool>>& matrix, int origem, string nome_do_arquivo_de_saida = "arvoreDFS.txt");
double BFS_tree_matrix_with_execution_time(const vector<vector<bool>>& matrix, int origem, string nome_do_arquivo_de_saida = "arvoreBFS.txt");

#endif