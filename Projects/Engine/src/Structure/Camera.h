#ifndef CAMERA_H
#define CAMERA_H
#include "SFML/Graphics.hpp"

namespace pa {

	class Camera
	{
	public:
		Camera(float moveSpeed, float zoomSpeed, sf::Vector2f centre, sf::Vector2f size = sf::Vector2f(640.f, 480.f));
		~Camera();

		sf::View& getView();

		void update();
		// Update gets called if freemove is used, otherwise only call update
		void freeMove(const float& dt);

		void moveOrigin(const sf::Vector2f& offset);
		void setOrigin(const sf::Vector2f& pos);

		void setZoom(const float& zoom);
		void scrollZoom(const float& delta);

		float getZoom() const;
		sf::Vector2f getOriginPos() const;

	private:
		sf::View view;

		sf::Vector2f centre;

		float zoom;
		float zoomSpeed;
		float moveSpeed;
	};
}
#endif