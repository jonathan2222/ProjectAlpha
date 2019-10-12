#include "Display.h"

 Display::Display(unsigned int width, unsigned int height, const std::string& title) : width(width), height(height), title(title)
 {
     this->window.create(sf::VideoMode(this->width, this->height), this->title);
 }

bool Display::isOpen()
{
    return this->window.isOpen();
}

void Display::close()
{
	this->window.close();
}

void Display::swapBuffers()
{
    this->window.display();
}

sf::RenderWindow& Display::getWindow()
{
    return this->window;
}

unsigned int Display::getWidth() const
{
    return this->width;
}

unsigned int Display::getHeight() const
{
    return this->height;
}

std::string Display::getTitle() const
{
    return this->title;
}