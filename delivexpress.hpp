#ifndef DELIVEXPRESS_HPP
#define DELIVEXPRESS_HPP

#include <string>
#include <vector>
#include <limits>
#include <unordered_map>
#define INF 2147483647

// Estrutura para armazenar a solução
struct Solution {
    std::vector<int> path;      // Caminho encontrado (índices das cidades)
    int total_distance;         // Distância total do caminho
    
    Solution() : total_distance(INF) {}
};

// Hash para o par estado-vértice usado na PD
struct StateHash {
    size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
    }
};

class Graph {
private:
    int V;                                  // Número de vértices
    std::vector<std::vector<int>> adj;      // Matriz de adjacência
    std::vector<std::string> city_names;    // Nomes das cidades
    std::vector<int> city_index;            // Mapa de índices das cidades

    // Cache para programação dinâmica
    std::unordered_map<std::pair<int, int>, int, StateHash> dp_cache;
    std::unordered_map<std::pair<int, int>, int, StateHash> parent;

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
    
    // Algoritmo de força bruta
    Solution bruteForce(int start_city);
    
    // Algoritmo de Held-Karp (Programação Dinâmica)
    Solution heldKarp(int start_city);
    
    // Algoritmo Guloso (Vizinho Mais Próximo)
    Solution nearestNeighbor(int start_city);
    
private:
    // Função auxiliar recursiva para o algoritmo de força bruta
    void bruteForceUtil(int start_city, std::vector<bool>& visited, 
                       std::vector<int>& current_path, int current_distance,
                       Solution& best_solution);
                       
    // Funções auxiliares para o algoritmo de Held-Karp
    int tsp(int pos, int visited, int start_city);
    void reconstructPath(Solution& solution, int start_city);
    
    // Função auxiliar para encontrar o vizinho mais próximo não visitado
    int findNearestNeighbor(int current_city, const std::vector<bool>& visited) const;
};

// Estrutura para armazenar os dados de entrada
struct InputData {
    char strategy;           // 'b', 'd' ou 'g'
    Graph* graph;           // Grafo representando as cidades e estradas
};

// Função para ler a entrada
InputData parse_input();

#endif // DELIVEXPRESS_HPP
