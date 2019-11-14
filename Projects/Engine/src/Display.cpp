#include "Display.h"

Display& Display::get()
{
	static Display display;
	return display;
}

void Display::init(unsigned int width, unsigned int height, const std::string& title)
 {
	this->width = width;
	this->height = height;
	this->title = title;
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
	this->window.clear();
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