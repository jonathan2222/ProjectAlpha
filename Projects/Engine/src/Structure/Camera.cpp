#include "Camera.h"

#include "Chunk.h"

#include "../Display.h"
#include "../IO/Input.h"
#include <iostream>

using namespace pa;

Camera::Camera(float moveSpeed, float zoomSpeed, sf::Vector2f centre, sf::Vector2f size)
	: centre(centre),
		zoom(1.0f),
		zoomSpeed(zoomSpeed),
		moveSpeed(moveSpeed),
		view(centre, size)
{
}

Camera::~Camera()
{
}

sf::View & pa::Camera::getView()
{
	return this->view;
}

void pa::Camera::update()
{
	this->view.setCenter(this->centre);
}

void pa::Camera::freeMove(const float& dt)
{
	pa::Input& input = pa::Input::get();

	float shiftSpeed = 1.0f;
	if (input.isKey(pa::Input::Pressed, pa::Input::Key::LShift))
		shiftSpeed = 5.0f;

	if (input.isKey(pa::Input::Pressed, pa::Input::Key::A))
		this->moveCentre(sf::Vector2f(-shiftSpeed *moveSpeed * dt, 0.f));
	if (input.isKey(pa::Input::Pressed, pa::Input::Key::D))
		this->moveCentre(sf::Vector2f(shiftSpeed * moveSpeed * dt, 0.f));
	if (input.isKey(pa::Input::Pressed, pa::Input::Key::W))
		this->moveCentre(sf::Vector2f(0.f, -shiftSpeed * moveSpeed * dt));
	if (input.isKey(pa::Input::Pressed, pa::Input::Key::S))
		this->moveCentre(sf::Vector2f(0.f, shiftSpeed * moveSpeed * dt));

	int delta = input.getMouseWheelDelta();
	if (delta)
		this->scrollZoom(delta);

	update();
}


void Camera::moveCentre(const sf::Vector2f & offset)
{
	this->centre += offset;
	this->worldPos += offset;
}

void Camera::setCentre(const sf::Vector2f & pos)
{
	this->centre = pos;
}

sf::Vector2f Camera::getCentre() const
{
	return this->centre;
}

sf::Vector2f pa::Camera::getMouseGlobalPos() const
{
	const sf::Vector2i mpIntegers = Input::get().getMousePosition();
	sf::Vector2f mousePos(mpIntegers.x, mpIntegers.y);

	// Recentre origo for mouse position to upp
	mousePos.x -= Display::get().getWidth() * 0.5f;
	mousePos.y -= Display::get().getHeight() * 0.5f;

	// Take camera zoom into account
	float zoomMagnitude = this->zoom;
	mousePos *= zoomMagnitude;

	// Move mouse pos into world coordinates
	mousePos.x += this->worldPos.x;
	mousePos.y += this->worldPos.y;

	// Offset to upperleft corner of chunk
	const int halfChunkPixelLength = CHUNK_SIZE * CELL_SIZE * 0.5;
	mousePos.x += halfChunkPixelLength;
	mousePos.y += halfChunkPixelLength;

	// invert to postive Y upwards
	mousePos.y *= -1.0f;

	return mousePos;
}

sf::Vector2f pa::Camera::getWorldPos() const
{
	return this->worldPos;
}

void Camera::setZoom(const float & zoom)
{
	this->zoom = zoom;
	this->view.zoom(this->zoom);
}

void pa::Camera::scrollZoom(const float & delta)
{
	this->zoom += delta * -this->zoomSpeed;
	this->view.zoom(1.0f + delta * -this->zoomSpeed);
}

float pa::Camera::getZoom() const
{
	return this->zoom;
}


