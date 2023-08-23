#include "kruskal.h"
#include "queue.h"

// Конструктор пустого ребра
Edge::Edge() {
    vert_1 = NULL;
    vert_2 = NULL;
    weight = NULL;
}

// Конструктор заполненного ребра
Edge::Edge(const int vertex_1, const int vertex_2, int w) {
    vert_1 = vertex_1;
    vert_2 = vertex_2;
    weight = w;
}

// Деструктор
Edge::~Edge() {
}

// Перегруженный оператор присвоения для взаимодействия с ребрами Edge
Edge& Edge::operator=(const Edge& edge) {
    vert_1 = edge.vert_1;
    vert_2 = edge.vert_2;
    weight = edge.weight;
    
    return *this;
}

// Взаимодействие с матрицей и графом
void Task::workWithMatrix() {
    int option;
    // Обработка ввода
    do {
        cout << "What do you want to do?" << endl;
        cout << "1 - Read text file" << endl;
        cout << "2 - Print the matrix" << endl;
        cout << "3 - Run Kruskal algorithm" << endl;
        cout << "4 - DFS Search" << endl;
        cout << "5 - BFS Search" << endl;
        cout << "0 - Exit program" << endl;
        
        cout << ">> ";
        cin >> option;

        switch (option) {
            case 0:
                break;
            case 1:
                readMatrix();
                break;
            case 2:
                printMatrix();
                break;
            case 3:
                runKruskalAlgorithm();
                break;
            case 4:
                dfsAlgorithm();
                break;
            case 5:
                bfsAlgorithm();
                break;
            default:
                cout << "Error. Unknown command." << endl;
                break;
        }
    } while (option != 0);
    
    memoryFreing();
    
    cout << "Thank you for using the program." << endl;
}

// Освобождение выделенной динамической памяти
void Task::memoryFreing() {
    for (int i = 0; i < matrixSize; i++) {
        delete [] matrix[i];
    }
    delete [] matrix;
    
    delete [] edges;
    
    delete [] route;
    
    delete [] vertexNames;
    
    delete [] parents;

    delete [] visited;
}

// Добавление ребра к массиву рёбер
void Task::addEdgeToArr(const int vertex_1, const int vertex_2, const int weight) {
    Edge edge(vertex_1, vertex_2, weight);
    Edge* tempEdges = new Edge[edgesCount + 1];
    for (int i = 0; i < edgesCount; i++) {
        tempEdges[i] = edges[i];
    }
    tempEdges[edgesCount] = edge;
    delete [] edges;
    edges = tempEdges;
    edgesCount++;
}

// Добавление имени вершины к массиву имён вершин
void Task::addVertexNameToArr(const string value) {
    string* tempVertexNames = new string[matrixSize + 1];
    for (int i = 0; i < matrixSize; i++) {
        tempVertexNames[i] = vertexNames[i];
    }
    tempVertexNames[matrixSize] = value;
    delete [] vertexNames;
    vertexNames = tempVertexNames;
    matrixSize++;
}

// Чтение матрицы из файла
void Task::readMatrix() {
    if (!matrix) {
        fstream fin;
        fin.open("file.txt");
        
        if (!fin.is_open()) {
            cout << "File has not been opened.\n";
            return;
        }
     
        string s = "";
        string value = "";
        
        // Чтение первой строки файла, содержащей названия вершин
        getline (fin, s);
        // Пока не конец строки, считываем элементы, которые могут составлять слово
        for (int i = 0; i < s.length(); ) {
            value = "";
            while ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122) ||
                   (s[i] >= 48 && s[i] <= 57) || (s[i] == 95)) {
                value += s[i];
                i++;
            }
            addVertexNameToArr(value);
            while (!((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122) ||
                   (s[i] >= 48 && s[i] <= 57) || (s[i] == 95))) {
                i++;
            }
        }
        
        // Инициализация матрицы
        matrix = new int* [matrixSize];
        for (int i = 0; i < matrixSize; i++) {
            matrix[i] = new int [matrixSize];
        }
        
        // Номер, в который будет преобразовано строковое значение
        int num;
        // Текущая строка и текущий столбец
        int curRow = 0, curCol;

        // Чтение следующих строк файла
        while (getline(fin, s)) {
            curCol = 0;
            // Пока не конец строки, считываем элементы до пробела
            for (int i = 0; i < s.length(); ) {
                while ((!(s[i] >= 48 && s[i] <= 57)) && i < s.length()) {
                    i++;
                }
                if ((s[i] >= 48 && s[i] <= 57)) {
                    num = 0;
                    while ((s[i] >= 48 && s[i] <= 57)) {
                        num *= 10;
                        num += (s[i] - '0');
                        i++;
                    }
                    if (num != 0 && curCol > curRow) {
                        addEdgeToArr(curRow, curCol, num);
                    }
                    
                    matrix[curRow][curCol] = num;
                    curCol++;
                }
            }
            curRow++;
        }
        fin.close();
        cout << "The file has been read successfully." << endl << endl;
    } else {
        cout << "The matrix is already filled in." << endl << endl;
    }
}

// Печать матрицы смежности
void Task::printMatrix() {
    if (matrix) {
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                cout << matrix[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    } else {
        cout << "Error. The matrix is empty." << endl << endl;
    }
}

// Нахождение начала поддерева
int Task::findUnion(int value) {
    if (value == parents[value]) {
        return value;
    }
    return findUnion(parents[value]);
}

// Проверка на то, что при добавлении ребра может получаться цикл
bool Task::isInRoute(const int vertex_1, const int vertex_2) {
    int a = findUnion(vertex_1);
    int b = findUnion(vertex_2);
    if (a != b) {
        parents[b] = a;
        return false;
    }
    return true;
}

// Добавление в массив остовного пути
void Task::addToRoute(Edge edge) {
    Edge* tempRoute = new Edge[routeSize + 1];
    for (int i = 0; i < routeSize; i++) {
        tempRoute[i] = route[i];
    }
    tempRoute[routeSize] = edge;
    delete [] route;
    route = tempRoute;
    routeSize++;
}

// Сортировка вставками на массиве рёбер edges
void Task::insertionSorting(Edge* edges, const int size) {
    for (int j = 1; j < size; j++) {
        Edge tempEdge = edges[j];
        for (int i = j - 1; i >= 0 && tempEdge.weight < edges[i].weight; i--) {
            edges[i + 1] = edges[i];
            edges[i] = tempEdge;
        }
    }
}

// Алгоритм Крускала
void Task::runKruskalAlgorithm() {
    routeWeight = 0;
    if (matrix) {
        insertionSorting(edges, edgesCount);
        
        parents = new int[matrixSize];
        for (int i = 0; i < matrixSize; i++) {
            parents[i] = i;
        }
        for (int i = 0; i < edgesCount; i++) {
            if (!isInRoute(edges[i].vert_1, edges[i].vert_2)) {
                addToRoute(edges[i]);
                routeWeight += edges[i].weight;
            }
        }
        for (int i = 0; i < routeSize; i++) {
            cout << vertexNames[route[i].vert_1] << " - " << vertexNames[route[i].vert_2] << "\t" << route[i].weight << endl;
        }
        cout << endl << routeWeight << " - minimum spanning forest weight." << endl;
    } else {
        cout << "Error. The matrix is empty." << endl << endl;
    }
}

// Обход в глубину: depth-first search
void Task::dfsAlgorithm() {
    if (matrix) {
        visited = new int[matrixSize];

        for (int i = 0; i < matrixSize; i++) {
            visited[i] = 0;
        }
        
        cout << "DFS Route is: ";
        dfsSearch(0);
        cout << endl << endl;
    } else {
        cout << "Error. The matrix is empty." << endl << endl;
    }
}
void Task::dfsSearch(const int value) {
    visited[value] = 1;
    cout << vertexNames[value] << " ";
    
    for (int j = 0; j < matrixSize; j++) {
        if ((matrix[value][j] > 0) && (!visited[j])) {
            dfsSearch(j);
        }
    }
}

// Обход в ширину breadth-first search
void Task::bfsAlgorithm() {
    if (matrix) {
        visited = new int[matrixSize + 1];
        
        // Обнуляем массив, содержащий информацию о посещённых веришнах
        for (int i = 0; i < matrixSize; i++) {
            visited[i] = 0;
        }
        
        cout << "BFS Route is: ";
        bfsSearch(0);
        cout << endl << endl;
    } else {
        cout << "Error. The matrix is empty." << endl << endl;
    }
}

void Task::bfsSearch(const int value) {
    // Очередь пройденных вершин
    Queue* q = new Queue();
    
    // Индекс врешины
    int value_index;
    
    // Сперва посещаем саму вершину
    q->push(value);
    cout << vertexNames[value] << " ";
    visited[value] = 1;
    
    // Пока очередь не пуста, извлекаем вершину из головы очереди
    while (!q->empty()) {
        value_index = q->front();
        q->pop();
        for (int j = 0; j < matrixSize; j++) {
            if ((matrix[value_index][j] > 0) && (!visited[j])) {
                visited[j] = 1;
                q->push(j);
                cout << vertexNames[j] << " ";
            }
        }
    }
}
