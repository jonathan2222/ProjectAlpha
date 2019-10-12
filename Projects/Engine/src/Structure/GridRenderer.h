#ifndef PA_GRID_RENDERER
#define PA_GRID_RENDERER

#include <vector>
#include <SFML/Graphics.hpp>


namespace pa {
	class Chunk;

	class GridRenderer
	{
	public:
		GridRenderer(const std::vector<Chunk*>* chunks);
		GridRenderer() = delete;
		~GridRenderer();

		void draw(sf::RenderWindow& win, const sf::RenderStates& state);
	private:
		void generateQuads();
		void generateDebugLines(const sf::Color& color);

		bool showChunkGrid;

		const std::vector<Chunk*>* chunks;
		sf::VertexArray quads;
		sf::VertexArray* debugLines;
	};
}

#endif