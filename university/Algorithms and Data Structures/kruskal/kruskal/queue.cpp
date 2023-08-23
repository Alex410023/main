#include "queue.h"

// Конструктор
Queue::Queue() {
    count = 0;
    data = NULL;
}

// Деструктор
Queue::~Queue() {
    delete [] data;
}

// Если в очереди нет элементов
bool Queue::empty() {
    return (count == 0);
}

// Размер очереди
int Queue::size() {
    return count;
}

// Возвращает первый элемент, добавленный в очередь
int Queue::front() {
    if (count > 0) {
        return (data[0]);
    } else {
        return -1;
    }
}

// Добавление элемента в конец очереди
void Queue::push(const int& val) {
    int* newData = new int[count + 1];
    
    for (int i = 0; i < count; i++) {
        newData[i] = data[i];
    }
    newData[count] = val;
    delete [] data;
    data = newData;
    count++;
}

// Удаление элемента из конца очереди
void Queue::pop() {
    int* newData = new int[count - 1];
    if (count > 1) {
        for (int i = 0; i < count - 1; i++) {
            newData[i] = data[i + 1];
        }
    }
    delete [] data;
    data = newData;
    count--;
}

// Печать очереди на экран
void Queue::print() {
    for (int i = 0; i < count; i++) {
        cout << data[i];
    }
    cout << endl;
}

