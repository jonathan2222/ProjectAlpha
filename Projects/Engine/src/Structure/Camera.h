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

		void moveCentre(const sf::Vector2f& offset);
		void setCentre(const sf::Vector2f& pos);
		sf::Vector2f getCentre() const;

		sf::Vector2f getGlobalMousePos() const;
		sf::Vector2f getWorldPos() const;

		void setZoom(const float& zoom);
		void scrollZoom(const float& delta);

		float getZoom() const;

	private:
		sf::View view;

		sf::Vector2f centre;
		sf::Vector2f worldPos;

		float zoom;
		float zoomSpeed;
		float moveSpeed;

	};
}
#endif