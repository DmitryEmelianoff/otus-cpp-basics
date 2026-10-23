#pragma once

#include <iostream>

template<typename T>
class MySequentialContainer {

    public:

        inline MySequentialContainer() {}
        inline ~MySequentialContainer() {
            delete [] m_region; // удаление последней созданной области
        }

        // добавление элемента в конец контейнера
        inline void push_back(T value) {
            T* new_region = new T[m_size + 1]; // новая область памяти
            for (size_t i = 0; i < m_size; ++i) {
                new_region[i] = m_region[i]; // копирование элементов
            }
            new_region[m_size] = value; // добавление нового элемента
            delete [] m_region; // удаление старой области
            m_region = new_region; // сохранение новой в мембер
            ++m_size; // обновление информации о размере
        }
        
        // вставка элемента в произвольную позицию
        inline void insert(T value, int index) {
            if (index < 0 || index > m_size) { // замена несуществующей позиции на минимальную или максимальную
                if(index < 0) {
                    index = 0;
                }
                else {
                    index = m_size;
                }
            }
            T* new_region = new T[m_size + 1]; // новая область памяти
            for (size_t i = 0; i < index; ++i) {
                new_region[i] = m_region[i]; // копирование элементов перед новым элементом
            }
            new_region[index] = value; // добавление нового элемента
            for (size_t i = index; i < m_size; ++i) {
                new_region[i + 1] = m_region[i]; // копирование элементов после нового элемента
            }
            delete [] m_region; // удаление старой области
            m_region = new_region; // сохранение новой в мембер
            ++m_size; // обновление информации о размере
        };

        // удаление элемента из произвольной позиции
        inline void erase(size_t index) {
            if (m_size == 0) { // если контейнер пустой - ничего не делать.
                return;
            }
            if (index < 0 || index > m_size - 1) { // замена несуществующей позиции на минимальную или максимальную
                if (index < 0) {
                    index = 0;
                }
                else {
                    index = m_size - 1;
                }
            }
            T* new_region = new T[m_size - 1]; // новая область памяти
            for (size_t i = 0; i < index; ++i) {
                new_region[i] = m_region[i]; // копирование элементов перед ненужным элементом
            }
            for (size_t i = index; i < m_size - 1; ++i) {
                new_region[i] = m_region[i + 1]; // копирование элементов после ненужного элемента
            }
            delete [] m_region; // удаление старой области
            m_region = new_region; // сохранение новой в мембер
            --m_size; // обновление информации о размере
        };

        // вывод количества элементов контейнера
        inline size_t size() const {
            return m_size;
        };

        // возврат доступа к определенному элементу
        inline T& operator[](int index) {
            return m_region[index];
        };

        // вывод содержимого контейнера
        // дружественная перегрузка operator<<, определённая внутри класса
        friend std::ostream& operator<<(std::ostream& o, const MySequentialContainer& cont) {
            if (cont.m_size > 0) {
                o << cont.m_region[0];
                for (size_t i = 1; i != cont.m_size; ++i) {
                    o << ", " << cont.m_region[i];
                }
            }
            else {
                o << "Контейнер пуст.";
            }
            return o;
        }

    private:

        T* m_region = nullptr;
        size_t m_size = 0;
};

template<typename T>
struct Node {
    Node* next = nullptr; // указатель на следующий элемент Node
    Node* prev = nullptr; // указатель на предыдущий элемент Node
    T data; // пользовательские данные (хранимый объект)
};

template<typename T>
class MyListTypeContainer {

    public:

        inline MyListTypeContainer() {}
        inline ~MyListTypeContainer() {
            if (m_last != nullptr) {
                while (m_last -> prev != nullptr) {
                    m_last = m_last -> prev;
                    delete m_last -> next;
                }
                delete m_last;
            }
        }

        // добавление элемента в конец контейнера
        inline void push_back(T value) {
            Node<T>* new_node = new Node<T>{}; // создание нового узла
            new_node -> prev = m_last; // предыдущим узлом станет последний
            new_node -> next = nullptr; // следующего узла пока нет
            new_node -> data = value; // сохраняем пользовательские данные
            if (m_last != nullptr) {
                m_last -> next = new_node; // добавлем указатель на новый узел для последнего узла
            }
            m_last = new_node; // обновляем указатель на последний
            ++m_size; // обновляем размер
        }
        
        // вставка элемента в произвольную позицию
        inline void insert(T value, int index) {
            if (index < 0 || index > m_size) { // замена несуществующей позиции на минимальную или максимальную
                if(index < 0) {
                    index = 0;
                }
                else {
                    index = m_size;
                }
            }
            if (index == m_size) {
                push_back(value); // если целевой индекс последний - добавление элемента в конец контейнера
                return; // выход из функции
            }
            Node<T>* new_node = new Node<T>{}; // создание нового узла
            new_node -> data = value; // сохраняем пользовательские данные
            new_node -> next = m_last; // следующим узлом после нового предварительно определяем последний
            for (size_t i = 0; i != m_size - index - 1; ++i) {
                new_node -> next = new_node -> next -> prev; // следующим узлом после нового определяем узел, стоящий перед следующим.
            }
            if (index == 0) {
                new_node -> prev = nullptr; // если новый узел самый первый - то предыдущего узла для нового нет
            }
            else { // иначе
                new_node -> prev = new_node -> next -> prev; // предыдущим узлом перед новым определяем узел, стоящий перед следующим.
                new_node -> prev -> next = new_node; // для предыдущего узла переопределяем следующий узел
            }
            new_node -> next -> prev = new_node; // для следующего узла переопределяем предыдущий узел
            ++m_size; // обновляем размер
        };

        // удаление элемента из произвольной позиции
        inline void erase(size_t index) {
            if (m_size == 0) { // если контейнер пустой - ничего не делать.
                return;
            }
            if (index < 0 || index > m_size - 1) { // замена несуществующей позиции на минимальную или максимальную
                if(index < 0) {
                    index = 0;
                }
                else {
                    index = m_size - 1;
                }
            }
            Node<T>* m_current = m_last;
            if (m_size > 1) {
                for (size_t i = 0; i != m_size - index - 1; ++i) {
                    m_current = m_current -> prev;
                }
                if (index > 0 && index < m_size - 1) {
                    m_current -> prev -> next = m_current -> next;
                    m_current -> next -> prev = m_current -> prev;
                }
                else {
                    if (index == 0) {
                        m_current -> next -> prev = nullptr;
                    }
                    else {
                        m_last = m_current -> prev;
                        m_last -> next = nullptr;
                    }
                }
            }
            else {
                m_last = nullptr;
            }
            delete m_current;
            --m_size;
        };

        // вывод количества элементов контейнера
        inline size_t size() const {
            return m_size;
        };

        // возврат доступа к определенному элементу
        inline T& operator[](int index) {
            Node<T>* m_current = m_last;
            for (size_t i = 0; i != m_size - index - 1; ++i) {
                m_current = m_current -> prev;
            }
            return m_current -> data;
        };

        // вывод содержимого контейнера
        // дружественная перегрузка operator<<, определённая внутри класса
        friend std::ostream& operator<<(std::ostream& o, const MyListTypeContainer& cont) {
            if (cont.m_last != nullptr) {
                Node<T>* m_current = cont.m_last;
                while (m_current -> prev != nullptr) {
                    m_current = m_current -> prev;
                }
                o << m_current -> data;
                while (m_current -> next != nullptr) {
                    m_current = m_current -> next;
                    o << ", " << m_current -> data;
                }
            }
            else {
                o << "Контейнер пуст.";
            }
            return o;
        }

    private:

        Node<T>* m_last = nullptr;
        size_t m_size = 0;
};