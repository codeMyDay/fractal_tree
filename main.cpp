#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <time.h>
#include <unistd.h>
#include <cmath>

void lineTo(float x, float y, float len, float angle)
{
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x+len*cos(angle), y+len*sin(angle));
    glEnd();
}

void tree(float x, float y, float len, float angle, float len_div, float angle_dif, int depth)
{
    lineTo(x, y, len, angle);
    if(depth == 0) return;

    // left
    tree(x+len*cos(angle), y+len*sin(angle), len*len_div, angle-angle_dif, len_div, angle_dif, depth-1);

    // right
    tree(x+len*cos(angle), y+len*sin(angle), len*len_div, angle+angle_dif, len_div, angle_dif, depth-1);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(700, 700), "Fractal tree");
    window.setFramerateLimit(30);
    glOrtho(0.0, window.getSize().x, window.getSize().y, 0.0, 1.0, -1.0);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
        }
        window.clear();

        tree(350.0, 650.0, 100.0, -M_PI/2.0, 0.8, M_PI/12.0, 12);

        window.display();
        usleep(100000);
    }
    return 0;
}