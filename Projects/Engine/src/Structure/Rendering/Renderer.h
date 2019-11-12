#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/System/Vector2.hpp>


namespace pa {
	class World;
	class Camera;

	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void renderWorld(World& world, Camera& cam);

	private:


	};
};
#endif