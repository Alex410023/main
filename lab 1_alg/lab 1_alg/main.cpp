#include <iostream>
#include <string>

using namespace std;


template<class T>
class Node {
public:
    Node* pNext;
    T data;

    Node(T data = T(), Node* pNext = nullptr) {
        this->data = data;
        this->pNext = pNext;
    }

};

template<class T>
class List {
public:
    List();
    ~List();

    void addToEnd(T data);
    void deleteFromStart();
    void addToStart(T data);
    void deleteFromBack();
    void insert(T value, int index);
    void removeAt(int index);
    void clear();
    int getSize() {
        return size;
    }

    T& operator[](const int index);

    Node<T>* head;

    Node<T>* getHead() {
        return this->head;
    }

    int size;
};

template<class T>
List<T>::List() {
    size = 0;
    head = nullptr;
}

template<class T>
List<T>::~List() {
    clear();
}

template<class T>
inline void List<T>::addToEnd(T value) {
    Node<T>* ptrN = new Node<T>(value);
    if (this->head == NULL) {
        this->head = ptrN;
    } else {
        ptrN->pNext = this->head;
        this->head = ptrN;
    }
}

template<class T>
void List<T>::deleteFromStart() {
    Node<T>* temp = head;
    head = head->pNext;

    delete temp;
    size--;
}

template<class T>
void List<T>::addToStart(T data) {
    head = new Node<T>(data, head);
    size++;
}

template<class T>
inline void List<T>::deleteFromBack() {
    Node<T>* ptrN;
    if (this->head != NULL) {
        ptrN = this->head;
        this->head = ptrN->pNext;
        delete ptrN;
        ptrN = nullptr;
    }
}

template<class T>
void List<T>::insert(T value, int index) {
    if (index == 0) {
        addToStart(value);
    } else {
        Node<T>* previous = this->head;

        for (int i = 0; i < index - 1; i++) {
            previous = previous->pNext;
        }
        
        Node<T>* newNode = new Node<T>(value, previous->pNext);
        previous->pNext = newNode;

        size++;
    }
}

template<class T>
void List<T>::removeAt(int index) {
    if (index == 0) {
        deleteFromStart();
    } else {
        Node<T>* previous = this->head;
        for (int i = 0; i < index - 1; i++) {
            previous = previous->pNext;
        }

        Node<T>* toDelete = previous->pNext;
        previous->pNext = toDelete->pNext;
        delete toDelete;
        size--;
    }
}

template<class T>
void List<T>::clear() {
    while (size) {
        deleteFromStart();
    }
}

template<class T>
T& List<T>::operator[](const int index) {
    int counter = 0;
    Node<T>* current = this->head;

    while (current != nullptr) {
        if (counter == index) {
            return current->data;
        }
        current = current->pNext;
        counter++;
    }
}



template <class T>
class dynamic_array {
private:
    int arraySize;
    
public:
    T* arrayData;
    // создание пустого массива
    dynamic_array() {
        arraySize = 0;
        arrayData = NULL;
    }
    
    // создание массива заданного размера
    dynamic_array(int size) {
        arraySize = size;
        if (arraySize != 0)
            arrayData = new T[arraySize];
        else
            arrayData = 0;
    }
    
    // функция добавления элемента
    void pushLast(T number) {
        T* tempArray;
        tempArray = new T[arraySize + 1];
        for (int i = 0; i < arraySize; i++) {
            tempArray[i] = arrayData[i];
        }
        delete[] arrayData;
        arrayData = tempArray;
        arraySize++;
        arrayData[arraySize - 1] = number;
    }
    
    // функция удаления элемента
    void popFront() {
        T* tempArray;
        tempArray = new T[arraySize - 1];
        for (int i = 0; i < arraySize - 1; i++) {
            tempArray[i] = arrayData[i + 1];
        }
        arraySize--;
        delete[] arrayData;
        arrayData = tempArray;
    }
    
    void popBack() {
        T* tempArray;
        arraySize--;
        tempArray = new T[arraySize];
        for (int i = 0; i < arraySize; i++) {
            tempArray[i] = arrayData[i];
        }
        delete[] arrayData;
        arrayData = tempArray;
    }
    
    void popErase(int position) {
        T* tempArray;
        tempArray = new T[arraySize - 1];
        for (int i = 0; i < position; i++) {
            tempArray[i] = arrayData[i];
        }
        for (int i = position; i < arraySize - 1; i++) {
            tempArray[i] = arrayData[i + 1];
        }
        arraySize--;
        delete[] arrayData;
        arrayData = tempArray;
    }
    T* getData() {
        return arrayData;
    }
    int getSize() {
        return arraySize;
    }
    void printSize() {
        cout << "size\n" << arraySize << endl;
    }

    T& operator[](int i) {
        return arrayData[i];
    }
};

template <class T>
ostream& operator << (ostream& out, dynamic_array<T> arr) {
    for (int i = 0; i < arr.arraySize; ++i)
        out << arr[i] << " ";
    return out;
}


class Operators {
public:
    string oper;
    int priorityOp;
};

int main() {
    Operators oper[7];
    oper[0].oper = "+";
    oper[0].priorityOp = 0;

    oper[1].oper = "-";
    oper[1].priorityOp = 0;

    oper[2].oper = "*";
    oper[2].priorityOp = 1;

    oper[3].oper = "/";
    oper[3].priorityOp = 1;

    oper[4].oper = "^";
    oper[4].priorityOp = 2;

    oper[5].oper = "sin";
    oper[5].priorityOp = 3;

    oper[6].oper = "cos";
    oper[6].priorityOp = 3;

    Operators left_bracket;
    left_bracket.oper = "(";

    Operators right_bracket;
    right_bracket.oper = ")";

    List<Operators> stackOper;
    string  input;

    int position = 0;
    string buff;
    string temp;

    int flag;
    int positionOper;

    dynamic_array<string> yard(0);

    // input example = "7 * 8 - 6 / ( 1 - 5 ) ^ 5";

    cout << "Enter the expression\n";
    getline(cin, input);

    cout << "Array or List? \n 1 - array \n 2 - list \n";

    int a = 0;

    cin >> a;

    switch (a)
    {
    case 1:
        while (input != "") {
            position = input.find(" ");

            if (position == -1) {
                position = 1;
                buff = input.substr(0, position);
                input = "";
            } else {
                buff = input.substr(0, position);
                input = input.substr(position + 1, input.length());
            }

            flag = 0;
            positionOper = 0;

            while ((flag == 0) && (positionOper <= 6)) {
                if (buff == oper[positionOper].oper) {
                    flag = 1;
                } else {
                    positionOper++;
                }
            }

            if (flag == 1) {
                if (stackOper.getHead() == NULL) {
                    stackOper.addToEnd(oper[positionOper]);
                } else {
                    while (stackOper.getHead() != NULL && stackOper.getHead()->data.oper != "(") {
                        if (stackOper.getHead()->data.priorityOp >= oper[positionOper].priorityOp) {
                            cout << stackOper.getHead()->data.oper << " ";
                            stackOper.deleteFromBack();
                        } else {
                            break;
                        }
                    }
                    stackOper.addToEnd(oper[positionOper]);
                }
            } else {
                if (buff == "(") {
                    stackOper.addToEnd(left_bracket);
                } else if (buff == ")") {
                    while (stackOper.getHead()->data.oper != "(") {
                        cout << stackOper.getHead()->data.oper << " ";
                        stackOper.deleteFromBack();
                    }
                    stackOper.deleteFromBack();
                } else {
                    cout << buff << " ";
                }
            }
        }

        while (stackOper.getHead() != NULL) {
            cout << stackOper.getHead()->data.oper << " ";
            stackOper.deleteFromBack();
        }
            
            
        break;
    case 2:
        while (input != "") {
            position = input.find(" ");

            if (position == -1) {
                position = 1;
                buff = input.substr(0, position);
                input = "";
            } else {
                buff = input.substr(0, position);
                input = input.substr(position + 1, input.length());
            }

            flag = 0;
            positionOper = 0;

            while ((flag == 0) && (positionOper <= 6)) {
                if (buff == oper[positionOper].oper) {
                    flag = 1;
                } else {
                    positionOper++;
                }
            }
            if (flag == 1) {
                if (stackOper.getHead() == NULL) {
                    stackOper.addToEnd(oper[positionOper]);
                }
                else {
                    while (stackOper.getHead() != NULL && stackOper.getHead()->data.oper != "(") {
                        if (stackOper.getHead()->data.priorityOp >= oper[positionOper].priorityOp) {
                            temp = stackOper.getHead()->data.oper;
                            yard.pushLast(temp);
                            stackOper.deleteFromBack();
                        } else {
                            break;
                        }
                    }
                    stackOper.addToEnd(oper[positionOper]);
                }
            } else {
                if (buff == "(") {
                    stackOper.addToEnd(left_bracket);
                } else if (buff == ")") {
                    while (stackOper.getHead()->data.oper != "(") {
                        temp = stackOper.getHead()->data.oper;
                        yard.pushLast(temp);
                        stackOper.deleteFromBack();
                    }
                    stackOper.deleteFromBack();
                }
                else {
                    temp = buff;
                    yard.pushLast(temp);
                }
            }
        }
        while (stackOper.getHead() != NULL) {
            temp = stackOper.getHead()->data.oper;
            yard.pushLast(temp);
            stackOper.deleteFromBack();
        }
        for (int i = 0; i < yard.getSize(); i++) {
            cout << yard[i] << " ";
        }
        break;
    default:
        cout << "error\n";
        break;
    }

    return 0;
}
