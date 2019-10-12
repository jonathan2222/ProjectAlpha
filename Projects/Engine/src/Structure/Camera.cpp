#include "Camera.h"

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

	if (input.isKey(pa::Input::Pressed, pa::Input::Key::A))
		this->moveOrigin(sf::Vector2f(-moveSpeed * dt, 0.f));
	if (input.isKey(pa::Input::Pressed, pa::Input::Key::D))
		this->moveOrigin(sf::Vector2f(moveSpeed * dt, 0.f));
	if (input.isKey(pa::Input::Pressed, pa::Input::Key::W))
		this->moveOrigin(sf::Vector2f(0.f, -moveSpeed * dt));
	if (input.isKey(pa::Input::Pressed, pa::Input::Key::S))
		this->moveOrigin(sf::Vector2f(0.f, moveSpeed * dt));

	int delta = input.getMouseWheelDelta();
	if (delta)
		this->scrollZoom(delta);

	update();
}


void Camera::moveOrigin(const sf::Vector2f & offset)
{
	this->centre += offset;
}

void Camera::setOrigin(const sf::Vector2f & pos)
{
	this->centre = pos;
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

sf::Vector2f pa::Camera::getOriginPos() const
{
	return this->centre;
}

