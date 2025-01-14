#ifndef DELIVEXPRESS_HPP
#define DELIVEXPRESS_HPP

#include <string>
#include <vector>
#include <limits>
#define INF 2147483647

// Estrutura para armazenar a solução
struct Solution {
    std::vector<int> path;      // Caminho encontrado (índices das cidades)
    int total_distance;         // Distância total do caminho
    
    Solution() : total_distance(INF) {}
};

class Graph {
private:
    int V;                                  // Número de vértices
    std::vector<std::vector<int>> adj;      // Matriz de adjacência
    std::vector<std::string> city_names;    // Nomes das cidades
    std::vector<int> city_index;            // Mapa de índices das cidades

public:
    Graph(int vertices);
    
    // Adiciona uma aresta com peso
    void addEdge(const std::string& city1, const std::string& city2, int weight);
    
    // Retorna o número de vértices
    int getV() const { return V; }
    
    // Retorna a matriz de adjacência
    const std::vector<std::vector<int>>& getAdj() const { return adj; }
    
    // Retorna o nome da cidade dado seu índice
    const std::string& getCityName(int index) const { return city_names[index]; }
    
    // Retorna o índice da cidade dado seu nome
    int getCityIndex(const std::string& city) const;
    
    // Retorna a lista de nomes das cidades
    const std::vector<std::string>& getCityNames() const { return city_names; }
    
    // Algoritmo de força bruta para encontrar o menor caminho
    Solution bruteForce(int start_city);
    
private:
    // Função auxiliar recursiva para o algoritmo de força bruta
    void bruteForceUtil(int start_city, std::vector<bool>& visited, 
                       std::vector<int>& current_path, int current_distance,
                       Solution& best_solution);
};

// Estrutura para armazenar os dados de entrada
struct InputData {
    char strategy;           // 'b', 'd' ou 'g'
    Graph* graph;           // Grafo representando as cidades e estradas
};

// Função para ler a entrada
InputData parse_input();

#endif // DELIVEXPRESS_HPP
