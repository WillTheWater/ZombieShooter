#pragma once
#include "Zombie.h"
#include "SFML/Graphics.hpp"

int CreateBackground(sf::VertexArray& rVA, sf::IntRect arena);
Zombie* createHorde(int numZombies, sf::IntRect arena);