#pragma once
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

class TextureHolder
{
public:
	TextureHolder();
	static sf::Texture& GetTexture(std::string const& filename);

private:
	// A map container from the STL,
	// that holds related pairs of string and texture
	std::map<std::string, sf::Texture> m_Textures;

	// A pointer of type texture
	// and the one and only instance
	static TextureHolder* m_Instance;
};

#endif