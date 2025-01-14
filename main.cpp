#include "delivexpress.hpp"
#include <iostream>
#include <iomanip>

void print_matrix(const std::vector<std::vector<int>>& matrix) {
    for(const auto& row : matrix) {
        for(const auto& val : row) {
            if(val == INF) {
                std::cout << std::setw(5) << "INF";
            } else {
                std::cout << std::setw(5) << val;
            }
        }
        std::cout << "\n";
    }
}

void solve_brute_force(Graph* graph) {
    Solution best_solution;
    
    // Testa cada cidade como ponto inicial
    for (int start = 0; start < graph->getV(); ++start) {
        Solution current = graph->bruteForce(start);
        if (current.total_distance < best_solution.total_distance) {
            best_solution = current;
        }
    }
    
    // Imprime a solução
    if (best_solution.total_distance == INF) {
        std::cout << "Não existe solução!\n";
        return;
    }
    
    std::cout << best_solution.total_distance << "\n";
    
    // Imprime o caminho usando os nomes das cidades
    for (size_t i = 0; i < (best_solution.path.size() - 1); ++i) {
        std::cout << graph->getCityName(best_solution.path[i]);
        if (i < best_solution.path.size() - 2) {
            std::cout << " ";
        }
    }
    std::cout << "\n";
}

void solve_dynamic_programming(Graph* graph) {
    Solution best_solution;
    
    // Testa cada cidade como ponto inicial
    for (int start = 0; start < graph->getV(); ++start) {
        Solution current = graph->heldKarp(start);
        if (current.total_distance < best_solution.total_distance) {
            best_solution = current;
        }
    }
    
    // Imprime a solução
    if (best_solution.total_distance == INF) {
        std::cout << "Não existe solução!\n";
        return;
    }
    
    std::cout << best_solution.total_distance << "\n";
    
    // Imprime o caminho usando os nomes das cidades
    for (size_t i = 0; i < (best_solution.path.size() - 1); ++i) {
        std::cout << graph->getCityName(best_solution.path[i]);
        if (i < best_solution.path.size() - 2) {
            std::cout << " ";
        }
    }
    std::cout << "\n";
}

void solve_greedy(Graph* graph) {
    Solution best_solution;
    
    // Testa cada cidade como ponto inicial
    for (int start = 0; start < graph->getV(); ++start) {
        Solution current = graph->nearestNeighbor(start);
        if (current.total_distance < best_solution.total_distance) {
            best_solution = current;
        }
    }
    
    // Imprime a solução
    if (best_solution.total_distance == INF) {
        std::cout << "Não existe solução!\n";
        return;
    }
    
    std::cout << best_solution.total_distance << "\n";
    
    // Imprime o caminho usando os nomes das cidades
    for (size_t i = 0; i < (best_solution.path.size() - 1); ++i) {
        std::cout << graph->getCityName(best_solution.path[i]);
        if (i < best_solution.path.size() - 2) {
            std::cout << " ";
        }
    }
    std::cout << "\n";
}

int main() {
    // Lê os dados de entrada
    InputData data = parse_input();
    
    // Resolve usando a estratégia apropriada
    switch (data.strategy) {
        case 'b':
            solve_brute_force(data.graph);
            break;
        case 'd':
            solve_dynamic_programming(data.graph);
            break;
        case 'g':
            solve_greedy(data.graph);
            break;
        default:
            std::cout << "Estratégia inválida!\n";
    }
    
    // Libera a memória
    delete data.graph;
    
    return 0;
}
