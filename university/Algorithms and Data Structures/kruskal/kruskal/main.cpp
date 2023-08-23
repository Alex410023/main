/*
 Задача:
 Реализовать алгоритм поиска минимального остова на основе алгоритма Краскала(Крускала).
 
 Входные данные:
 Любой текстовый файл, содержащий матрицу смежности неориентированного графа
 
 В результате выводятся отсортированные по имени пары, входящие в остовное дерево, и суммарный вес это дерева
 */

#include "kruskal.h"

int main(int argc, const char * argv[]) {
    // Основной класс программы
    Task task;
    task.workWithMatrix();
    return 0;
}