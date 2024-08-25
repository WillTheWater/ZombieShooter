#include "ZombieArena.h"

int CreateBackground(sf::VertexArray& rVA, sf::IntRect arena)
{
	// Anything we do to rVA we are actually doing
	// to background in the main function

	const int				TILE_SIZE = 50;
	const int				TILE_TYPES = 3;
	const int				VERT_IN_QUAD = 4;

	int						worldWidth = arena.width / TILE_SIZE;
	int						worldHeight = arena.height / TILE_SIZE;

	// What type of primative are we using
	rVA.setPrimitiveType(sf::Quads);

	// Set the size of the vertex array
	rVA.resize(worldWidth * worldHeight * VERT_IN_QUAD);

	// Start at the beginning of the vertex array
	int						currentVertex = 0;

	for (int w = 0; w < worldWidth; w++)
	{
		for (int h = 0; h < worldHeight; h++)
		{
			// Position each vertext in the curent quad
			rVA[currentVertex + 0].position = sf::Vector2f(w * TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 1].position = sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 2].position = sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);
			rVA[currentVertex + 3].position = sf::Vector2f(w * TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);

			// Define the position in the texture for current quad
			// Either grass, stone, bush or wall
			if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1)
			{
				// Use wall texture
				rVA[currentVertex + 0].texCoords = sf::Vector2f(0, TILE_TYPES * TILE_SIZE);
				rVA[currentVertex + 1].texCoords = sf::Vector2f(TILE_SIZE, TILE_TYPES * TILE_SIZE);
				rVA[currentVertex + 2].texCoords = sf::Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPES * TILE_SIZE);
				rVA[currentVertex + 3].texCoords = sf::Vector2f(0, TILE_SIZE + TILE_TYPES * TILE_SIZE);
			}
			else
			{
				// Use random floor tile
				srand((int)time(0) + h * w - h);
				int mOrg = (rand() % TILE_TYPES);
				int verticalOffset = mOrg * TILE_SIZE;
				rVA[currentVertex + 0].texCoords = sf::Vector2f(0, verticalOffset);
				rVA[currentVertex + 1].texCoords = sf::Vector2f(TILE_SIZE, verticalOffset);
				rVA[currentVertex + 2].texCoords = sf::Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
				rVA[currentVertex + 3].texCoords = sf::Vector2f(0, TILE_SIZE + verticalOffset);
			}
			// Position ready for the next four vertices
			currentVertex += VERT_IN_QUAD;
		}
	}

	return TILE_SIZE;
}