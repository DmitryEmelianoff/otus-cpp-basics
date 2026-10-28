// добавление файла .h с контейнерами
#include "MyContainers.h"

int main() {

    // 1. создание объекта контейнера для хранения объектов типа int
    MySequentialContainer<int> values1;
    MyListTypeContainer<int> values2;

    // 2. добавление в контейнер десяти элементов (0, 1 … 9)
    for(size_t i = 0; i != 10; ++i) {
        values1.push_back(i);
        values2.push_back(i);
    }

    // 3. вывод содержимого контейнера на экран
    std::cout << values1 << std::endl;
    std::cout << values2 << std::endl << std::endl;
    
    // 4. вывод размера контейнера на экран
    std::cout << values1.size() << std::endl;
    std::cout << values2.size() << std::endl << std::endl;

    // 5. удаление третьего (по счёту), пятого и седьмого элементов
    values1.erase(6);
    values1.erase(4);
    values1.erase(2);
    values2.erase(6);
    values2.erase(4);
    values2.erase(2);

    // 6. вывод содержимого контейнера на экран
    std::cout << values1 << std::endl;
    std::cout << values2 << std::endl << std::endl;

    // 7. добавление элемента 10 в начало контейнера
    values1.insert(10, 0);
    values2.insert(10, 0);

    // 8. вывод содержимого контейнера на экран
    std::cout << values1 << std::endl;
    std::cout << values2 << std::endl << std::endl;

    // 9. добавление элемента 20 в середину контейнера
    values1.insert(20, values1.size() / 2);
    values2.insert(20, values2.size() / 2);

    // 10. вывод содержимого контейнера на экран
    std::cout << values1 << std::endl;
    std::cout << values2 << std::endl << std::endl;

    // 11. добавление элемента 30 в конец контейнера
    values1.insert(30, values1.size());
    values2.insert(30, values2.size());

    // 12. вывод содержимого контейнера на экран
    std::cout << values1 << std::endl;
    std::cout << values2 << std::endl;

    return 0;
}