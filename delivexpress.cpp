#include "delivexpress.hpp"
#include <iostream>
#include <algorithm>

Graph::Graph(int vertices) : V(vertices) {
    // Inicializa a matriz de adjacência com INF
    adj = std::vector<std::vector<int>>(V, std::vector<int>(V, INF));
    
    // Diagonal principal com 0
    for(int i = 0; i < V; i++) {
        adj[i][i] = 0;
    }
    
    // Inicializa o vetor de índices com -1
    city_index = std::vector<int>(V, -1);
}

void Graph::addEdge(const std::string& city1, const std::string& city2, int weight) {
    // Verifica se a cidade1 já existe
    auto it1 = std::find(city_names.begin(), city_names.end(), city1);
    int index1;
    
    if (it1 == city_names.end()) {
        index1 = static_cast<int>(city_names.size());
        city_names.push_back(city1);
        city_index[index1] = index1;
    } else {
        index1 = static_cast<int>(it1 - city_names.begin());
    }
    
    // Verifica se a cidade2 já existe
    auto it2 = std::find(city_names.begin(), city_names.end(), city2);
    int index2;
    
    if (it2 == city_names.end()) {
        index2 = static_cast<int>(city_names.size());
        city_names.push_back(city2);
        city_index[index2] = index2;
    } else {
        index2 = static_cast<int>(it2 - city_names.begin());
    }
    
    // Adiciona a aresta nos dois sentidos (grafo não direcionado)
    adj[index1][index2] = weight;
    adj[index2][index1] = weight;
}

int Graph::getCityIndex(const std::string& city) const {
    auto it = std::find(city_names.begin(), city_names.end(), city);
    if (it != city_names.end()) {
        return static_cast<int>(it - city_names.begin());
    }
    return -1;
}

void Graph::bruteForceUtil(int start_city, std::vector<bool>& visited, 
                          std::vector<int>& current_path, int current_distance,
                          Solution& best_solution) {
    // Se já visitamos todas as cidades
    if (current_path.size() == static_cast<size_t>(V)) {
        // Verifica se há caminho de volta para a cidade inicial
        if (adj[current_path.back()][start_city] != INF) {
            // Adiciona a distância de volta à cidade inicial
            int total_distance = current_distance + adj[current_path.back()][start_city];
            
            // Atualiza a melhor solução se encontramos um caminho menor
            if (total_distance < best_solution.total_distance) {
                best_solution.path = current_path;
                best_solution.path.push_back(start_city); // Adiciona a volta à cidade inicial
                best_solution.total_distance = total_distance;
            }
        }
        return;
    }
    
    // Tenta visitar cada cidade não visitada
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            // Se não houver caminho da última cidade até esta, pula
            if (!current_path.empty() && adj[current_path.back()][i] == INF) {
                continue;
            }
            
            // Calcula a nova distância
            int new_distance = current_distance;
            if (!current_path.empty()) {
                new_distance += adj[current_path.back()][i];
            }
            
            // Se a nova distância já é maior que a melhor solução, poda esta ramificação
            if (new_distance >= best_solution.total_distance) {
                continue;
            }
            
            // Marca como visitado e adiciona ao caminho atual
            visited[i] = true;
            current_path.push_back(i);
            
            // Recursivamente tenta completar o caminho
            bruteForceUtil(start_city, visited, current_path, new_distance, best_solution);
            
            // Backtracking
            visited[i] = false;
            current_path.pop_back();
        }
    }
}

Solution Graph::bruteForce(int start_city) {
    Solution best_solution;
    std::vector<bool> visited(V, false);
    std::vector<int> current_path;
    
    // Marca a cidade inicial como visitada e a adiciona ao caminho
    visited[start_city] = true;
    current_path.push_back(start_city);
    
    // Chama a função auxiliar recursiva
    bruteForceUtil(start_city, visited, current_path, 0, best_solution);
    
    return best_solution;
}

InputData parse_input() {
    InputData data;
    
    // Lê a estratégia (primeira linha)
    std::cin >> data.strategy;
    
    // Lê o número de cidades e estradas (segunda linha)
    int num_cities, num_roads;
    std::cin >> num_cities >> num_roads;
    
    // Cria o grafo
    data.graph = new Graph(num_cities);
    
    // Lê as estradas e adiciona ao grafo
    for (int i = 0; i < num_roads; i++) {
        std::string city1, city2;
        int distance;
        std::cin >> city1 >> city2 >> distance;
        data.graph->addEdge(city1, city2, distance);
    }
    
    return data;
}
