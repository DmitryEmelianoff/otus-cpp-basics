#pragma once

#include <iostream>

template<typename T>
class MySequentialContainer {

    public:

        MySequentialContainer() {}
        ~MySequentialContainer() {
            delete [] m_region; // удаление последней созданной области
        }

        // добавление элемента в конец контейнера
        void push_back(T value) {
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
        void insert(T value, size_t index) {
            if (index > m_size) { // замена несуществующей позиции на максимальную
                index = m_size;
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
        void erase(size_t index) {
            if (m_size > 0) { // проводить удаление только если контейнер не пустой.
                if (index >= m_size) { // замена несуществующей позиции на максимальную
                    index = m_size - 1;
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
            }
        };

        // вывод количества элементов контейнера
        size_t size() const {
            return m_size;
        };

        // возврат доступа к определенному элементу
        T& operator[](size_t index) {
            return m_region[index];
        };

        // вывод содержимого контейнера
        // дружественная перегрузка operator<<, определённая внутри класса
        friend std::ostream& operator<<(std::ostream& o, const MySequentialContainer& cont) {
            if (cont.m_size > 0) { // если контейнер не пустой
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

        MyListTypeContainer() {}
        ~MyListTypeContainer() {
            if (m_last != nullptr) {
                while (m_last -> prev != nullptr) {
                    m_last = m_last -> prev;
                    delete m_last -> next;
                }
                delete m_last;
            }
        }

        // добавление элемента в конец контейнера
        void push_back(T value) {
            Node<T>* new_node = new Node<T>{}; // создание нового узла
            new_node -> prev = m_last; // предыдущим узлом станет последний
            new_node -> next = nullptr; // следующего узла пока нет
            new_node -> data = value; // сохраняем пользовательские данные
            if (m_size > 0) {       // если контейнер не пустой
                m_last -> next = new_node; // добавлем указатель на новый узел для последнего узла
            }
            else { // если контейнер пустой
                m_first = new_node; // обновляем указатель на первый
            }
            m_last = new_node; // обновляем указатель на последний
            ++m_size; // обновляем размер
        }

        void push_front(T value) {
            Node<T>* new_node = new Node<T>{}; // создание нового узла
            new_node -> next = m_first; // следующим узлом станет первый
            new_node -> prev = nullptr; // предыдущего узла пока нет
            new_node -> data = value; // сохраняем пользовательские данные
            if (m_size > 0) {       // если контейнер не пустой
                m_first -> prev = new_node; // добавлем указатель на новый узел для первого узла
            }
            else { // если контейнер пустой
                m_last = new_node; // обновляем указатель на последний
            }
            m_first = new_node; // обновляем указатель на первый
            ++m_size; // обновляем размер
        }

        void pop_back() {
            if (m_size > 0) { // проводить удаление только если контейнер не пустой
                Node<T>* m_current = m_last; // определяем рассматриваемый узел
                if (m_size > 1) { // если удаляемый узел не последний
                    m_last = m_last -> prev; // обновляем указатель на последний узел
                    m_last -> next = nullptr; // для нового последнего узла обновляем указатель на следующий узел, который теперь будет nullptr
                }
                else { // если удаляемый узел последний
                    m_last = nullptr; // обновляем указатель на последний узел
                    m_first = nullptr; // обновляем указатель на первый узел
                }
                delete m_current; // удаление рассматриваемого узла
                --m_size; // обновление информации о размере
            }
        }

        void pop_front() {
            if (m_size > 0) { // проводить удаление только если контейнер не пустой
                Node<T>* m_current = m_first; // определяем рассматриваемый узел
                if (m_size > 1) { // если удаляемый узел не первый
                    m_first = m_first -> next; // обновляем указатель на первый узел
                    m_first -> prev = nullptr; // для нового первого узла обновляем указатель на предыдущий узел, который теперь будет nullptr
                }
                else { // если удаляемый узел первый
                    m_last = nullptr; // обновляем указатель на последний узел
                    m_first = nullptr; // обновляем указатель на первый узел
                }
                delete m_current; // удаление рассматриваемого узла
                --m_size; // обновление информации о размере
            }
        }
        
        // вставка элемента в произвольную позицию
        void insert(T value, size_t index) {
            if (index > m_size) { // замена несуществующей позиции на максимальную
                index = m_size;
            }
            if (index == m_size) {
                push_back(value); // если целевой индекс последний - добавление элемента в конец контейнера
                return; // выход из функции
            }
            if (index == 0) {
                push_front(value); // если целевой индекс первый - добавление элемента в начало контейнера
                return; // выход из функции
            }
            Node<T>* new_node = new Node<T>{}; // создание нового узла
            new_node -> data = value; // сохраняем пользовательские данные
            new_node -> next = m_first -> next; // следующим узлом для нового предварительно определяем следующий для первого узла, так как первый удаляться не будет
            for (size_t i = 0; i != index - 1; ++i) { // поиск узла, который будет предыдущим для нового
                new_node -> next = new_node -> next -> next;
            }
            new_node -> prev = new_node -> next -> prev; // предыдущим узлом для нового будет предыдущий для следующего
            new_node -> prev -> next = new_node; // для предыдущего узла обновляем указатель на следующий узел, который теперь будет новым
            new_node -> next -> prev = new_node; // для следующего узла обновляем указатель на предыдущий узел, который теперь будет новым
            ++m_size; // обновляем размер
        };

        // удаление элемента из произвольной позиции
        void erase(size_t index) {
            if (m_size > 0) { // проводить удаление только если контейнер не пустой.
                if (index >= m_size) { // замена несуществующей позиции на максимальную
                    index = m_size - 1;
                }
                if (index == m_size - 1) {
                    pop_back(); // если целевой индекс последний - удаление элемента из конца контейнера
                    return; // выход из функции
                }
                if (index == 0) {
                    pop_front(); // если целевой индекс первый - удаление элемента из начала контейнера
                    return; // выход из функции
                }
                Node<T>* m_current = m_first -> next; // предварительно определяем текущий узел как второй, так как первый удаляться не будет
                for (size_t i = 0; i != index - 1; ++i) { // поиск узла, который будет удаляться
                    m_current = m_current -> next;
                }
                m_current -> prev -> next = m_current -> next; // для предыдущего узла обновляем указатель на следующий узел, который теперь будет следующим для удаляемого
                m_current -> next -> prev = m_current -> prev; // для следующего узла обновляем указатель на предыдущий узел, который теперь будет предыдущим для удаляемого
                delete m_current; // удаление текущего узла
                --m_size; // обновление информации о размере
            }
        };

        // вывод количества элементов контейнера
        size_t size() const {
            return m_size;
        };

        // возврат доступа к определенному элементу
        T& operator[](size_t index) {
            Node<T>* m_current = m_first;
            for (size_t i = 0; i != index; ++i) {
                m_current = m_current -> next;
            }
            return m_current -> data;
        };

        // вывод содержимого контейнера
        // дружественная перегрузка operator<<, определённая внутри класса
        friend std::ostream& operator<<(std::ostream& o, const MyListTypeContainer& cont) {
            if (cont.m_size > 0) { // если контейнер не пустой
                Node<T>* m_current = cont.m_first;
                o << m_current -> data;
                for (size_t i = 1; i != cont.m_size; ++i) {
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

        Node<T>* m_first = nullptr;
        Node<T>* m_last = nullptr;
        size_t m_size = 0;
};