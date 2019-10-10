#include "Input.h"

#include <SFML/Graphics.hpp>
#include "../Display.h"

pa::Input& pa::Input::get()
{
	static Input input;
	return input;
}

void pa::Input::init(Display& display)
{
	this->display = &display;
	resetVars();
}

void pa::Input::update()
{
	resetVars();

	sf::Event e;
	sf::RenderWindow& window = this->display->getWindow();
	while (window.pollEvent(e))
	{
		updateWindow(e);
		
		updateKeys(e);

		updateMouse(e);
	}
}

bool pa::Input::isKey(const State& state, const Key& key) const
{
	auto it = keyboardMap.find(key);
	if(it != keyboardMap.end())
		return state == it->second;
	return false;
}

bool pa::Input::isMB(const State& state, const MB& button) const
{
	auto it = mouseMap.find(button);
	if (it != mouseMap.end())
		return state == it->second;
	return false;
}

float pa::Input::getMouseWheelDelta() const
{
	return this->mouseWheelDelta;
}

bool pa::Input::hasMouseMoved() const
{
	return this->mouseMoved;
}

sf::Vector2i pa::Input::getMousePosition() const
{
	return this->mousePos;
}

void pa::Input::resetVars()
{
	this->mouseWheelDelta = 0.0f;
	this->mouseMoved = false;
}

void pa::Input::updateWindow(const sf::Event& e)
{
	// Close window if someone requested it to close.
	if (e.type == sf::Event::Closed)
		this->display->close();
}

void pa::Input::updateKeys(const sf::Event& e)
{
	// Check if a key was pressed or not.
	if (e.type == sf::Event::KeyPressed)
		keyboardMap[e.key.code] = State::Pressed;
	else if (e.type == sf::Event::KeyReleased)
		keyboardMap[e.key.code] = State::Released;
}

void pa::Input::updateMouse(const sf::Event& e)
{
	// Check if mouse button was pressed or not.
	if (e.type == sf::Event::MouseButtonPressed)
		mouseMap[e.mouseButton.button] = State::Pressed;
	else if (e.type == sf::Event::MouseButtonReleased)
		mouseMap[e.mouseButton.button] = State::Released;

	// Get the mouse wheel scroll delta if changed.
	if (e.type == sf::Event::MouseWheelScrolled)
	{
		if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
			this->mouseWheelDelta = e.mouseWheelScroll.delta;
	}

	// Get mouse position if changed.
	if (e.type == sf::Event::MouseMoved)
	{
		this->mouseMoved = true;
		this->mousePos.x = e.mouseMove.x;
		this->mousePos.y = e.mouseMove.y;
	}
}
