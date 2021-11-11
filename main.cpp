#include <SFML/Graphics.hpp>

using namespace sf;
int main()
{
    // Создание окна
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    // Начальные координаты фигур
    int y1 = 500, x1 = 300;
    int y2 = 500, x2 = 150;
    int y3 = 500, x3 = 450;
    // Определение фигур и их размеров
    RectangleShape rectangle1(Vector2f(100.f, 70.f));
    RectangleShape rectangle2(Vector2f(130.f, 90.f));
    RectangleShape rectangle3(Vector2f(80.f, 90.f));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //  Цвет окна
        window.clear(Color(100, 100, 100, 0));
        
        // Условие остановки фигур
        if ( y1 >= 0)
        {
            y1 -= 1;
        }
        if (y2 >= 0)
        {
            y2 -= 2;
        }
        if (y3 >= 0)
        {
            y3 -= 3;
        }

        rectangle1.setPosition(x1, y1);
        rectangle2.setPosition(x2, y2);
        rectangle3.setPosition(x3, y3);

        
        rectangle1.setFillColor(Color(200, 10, 50));
        rectangle2.setFillColor(Color(200, 70, 100));
        rectangle3.setFillColor(Color(150, 150, 50));

        window.draw(rectangle1);
        window.draw(rectangle2);
        window.draw(rectangle3);

        window.display();
    }

    return 0;
}