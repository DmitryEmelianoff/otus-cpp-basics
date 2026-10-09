#define _USE_MATH_DEFINES
#include "Ball.hpp"
#include <cmath>

    Ball::Ball(const Point& ce, const Velocity& v, const Color& co, double r, bool iscol)
    : center{ce}, velocity{v}, color{co}, radius{r}, isCollidable(iscol) {}


/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    // TODO: место для доработки
    this -> velocity = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    // TODO: место для доработки
    return this -> velocity;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    // TODO: место для доработки
    painter.draw(center, radius, color);
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    // TODO: место для доработки
    this -> center = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    // TODO: место для доработки
    return this -> center;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    // TODO: место для доработки
    return radius;
}

/**
 * @brief Возвращает значение параметра, отвечающего за то, будет ли сталкиваться шар с другими шарами
 * @details если true - шар будет участвовать в столкновениях.
 * если false - шар будет пролетать другие шары насквозь.
 */
bool Ball::ballIsCollidable() const {
    return isCollidable;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    // TODO: место для доработки
    return M_PI * pow(radius, 3) * 4 / 3;
}
