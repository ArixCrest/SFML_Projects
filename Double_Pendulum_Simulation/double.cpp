#include <cmath>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

int main(){
    sf::Clock clock;
    const unsigned int W = 1400;
    const unsigned int H = 1400;
    const double pi = 3.14159265359;
    
    sf::RenderWindow window(sf::VideoMode(W,H), "Pendulum", sf::Style::Default);
    
    window.setFramerateLimit(120);
    
    sf::View view;
    view.setSize(sf::Vector2f(200.f,200.f));
    view.setCenter(sf::Vector2f(0.f,50.f));
    window.setView(view);
    double m1 = 5,m2 =5, l = 35, q1 = 120, q2 = 90,g = 9.81;
    double w1 = 0, w2 = 0, a1 = 0, a2 = 0;


    sf::CircleShape ball1(m1);
    ball1.setPointCount(100);
    ball1.setFillColor(sf::Color::Red);

    sf::CircleShape ball2(m2);
    ball2.setPointCount(100);
    ball2.setFillColor(sf::Color::Red);

    double r1 = (q1 / 180.f)*pi, r2 = (q2 / 180.f)*pi;

    sf::Vector2f pos1,pos2;
    const double dt = 0.06;
    std::vector<sf::Vector2f> path(1000);
    for(auto x : path) x.x = 0,x.y = 0;
    int i = 0;
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        double num = -g*(2*m1+m2)*std::sin(r1)-m2*g*std::sin(r1-2*r2) - 2*std::sin(r1-r2)*m2*(w2*w2*l+w1*w1*l*std::cos(r1-r2));
        double deno = l*(2*m1+m2-m2*std::cos(2*r1-2*r2));
        //if(deno<1e-5) deno = 1e-5;
        a1 = num/deno;
        num =  2*std::sin(r1-r2)*(w1*w1*l*(m1+m2)+g*(m1+m2)*std::cos(r1)+w2*w2*l*m2*std::cos(r1-r2));
        a2 = num/deno;
        w1 += a1*dt;
        w2 += a2*dt;
        r1 += w1*dt;
        r2 += w2*dt;
        pos1.x = l*std::sin(r1);
        pos1.y = l*std::cos(r1);
        pos2.x = pos1.x + l*std::sin(r2);
        pos2.y = pos1.y + l*std::cos(r2);
        ball1.setPosition(pos1 - sf::Vector2f(m1,m1));
        ball2.setPosition(pos2 - sf::Vector2f(m2,m2));
        window.clear();
        path[i%1000].x = pos2.x;
        path[i%1000].y = pos2.y;
        sf::Vertex line1[] = {
            sf::Vertex(sf::Vector2f(0.f,0.f)),
            sf::Vertex(pos1)
        };
        line1->color = sf::Color::White;
        window.draw(line1, 2,sf::Lines);
        sf::Vertex line2[] = {
            sf::Vertex(pos1),
            sf::Vertex(pos2)
        };
        line1->color = sf::Color::White;
        window.draw(line2, 2,sf::Lines);
        for(int j = 1;j<1000;j++){
            if(path[(i+j)%1000].x==0 && path[(i+j)%1000].y==0) break;
            sf::Vertex p[] = {
                sf::Vertex(path[(i+j)%1000],sf::Color::Red),
                sf::Vertex(path[(i+j+1)%1000],sf::Color::Red)
            };
            window.draw(p,2,sf::Lines);
        }
        window.draw(ball1);
        window.draw(ball2);
        window.display();
        i++;

    }
} 