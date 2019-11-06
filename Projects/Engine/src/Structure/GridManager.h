#ifndef PA_GRID_MANAGER
#define PA_GRID_MANAGER

#include <vector>
#include <SFML/Graphics.hpp>

namespace pa {
	class Chunk;

	class GridManager
	{
	public:
		GridManager(int rows, int cols);
		GridManager() = delete;
		~GridManager();

		std::vector<Chunk*>& getChunks();

		void updateUVCoords(const sf::Vector2u chunkIndex);
		void draw(sf::RenderWindow& win, const sf::RenderStates& state);
		void repositionQuadColumn(bool east);
	private:
		void generateQuads();
		void generateDebugLines(const sf::Color& color);

		bool showChunkGrid;

		int rows;
		int cols;
		std::vector<Chunk*> chunks;

		sf::VertexArray quads;
		sf::VertexArray* debugLines;
	};
}

#endif