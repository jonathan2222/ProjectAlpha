#ifndef AP_DISPLAY_H
#define AP_DISPLAY_H

#include <string>
#include <SFML/Graphics.hpp>

// ---------- TEST ----------
#include <SFML/OpenGL.hpp>

class Display
{
public:
    Display(unsigned int width, unsigned int height, const std::string& title);

    bool isOpen();

    void close();

    void swapBuffers();

    sf::RenderWindow& getWindow();
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    std::string getTitle() const;

private:
    sf::RenderWindow window;
    unsigned int width, height;
    std::string title;
};

#endif