#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"

using namespace std;

struct Edge {
    int vert_1;
    int vert_2;
    int weight;
    
    // Конструкторы для создания рёбер
    Edge();
    Edge(int vertex_1, int vertex_2, int w);
    // Деструктор
    ~Edge();
    
    // Перегрузка оператора присвоения
    Edge& operator=(const Edge&);
};

class Task {
public:
    void workWithMatrix();
private:
    // Названия вершин
    string* vertexNames = nullptr;
    
    // Исходная матрица
    int** matrix = nullptr;
    // Размер симметричной матрицы
    int matrixSize = 0;
    
    // Массив рёбер
    Edge* edges = nullptr;
    // Количество рёбер
    int edgesCount = 0;
    
    // Массив рёбер остовного дерева
    Edge* route = nullptr;
    // Длина остовного дерева
    int routeSize = 0;
    // Минимальный вес остовного дерева
    int routeWeight = 0;
    
    // Массив связанных вершин
    int* parents = nullptr;
    
    // Массив посещённых вершин
    int* visited = nullptr;
        
    // Освобождение выделенной динамической памяти
    void memoryFreing();
    
    // Сортировка вставками на массиве рёбер edges
    void insertionSorting(Edge* input, const int size);
    
    // Операции с матрицей
    void readMatrix();
    void printMatrix();
    
    // Алгоритм Крускала
    void runKruskalAlgorithm();
        
    // Добавление имени вершины к массиву имён вершин
    void addVertexNameToArr(const string value);
    
    // Добавление ребра к массиву рёбер
    void addEdgeToArr(const int vertex_1, const int vertex_2, const int weight);
    
    // Операции с массивом рёбер
    void addToRoute(const Edge edge);
    bool isInRoute(const int vertex_1, const int vertex_2);
    
    // Нахождение начала поддерева
    int findUnion(int value);

    // Обход в глубину
    void dfsAlgorithm();
    void dfsSearch(const int value);

    // Обход в ширину
    void bfsAlgorithm();
    void bfsSearch(const int value);
};
