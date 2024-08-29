#include "TextureHolder.h"
#include <assert.h>

TextureHolder* TextureHolder::m_Instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(m_Instance == nullptr);
	m_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(std::string const& filename)
{
	// Get a reference to m_Textures using m_Instance
	auto& m = m_Instance->m_Textures;
	// auto is the equivalent of map<string, texture>

	// Create an iteraltor to hold a key-value-pair
	// an search for the required kvp
	// using the passed in file name
	auto keyValuePair = m.find(filename);
	// auto is equivelent to ap<string, texture>::iterator

	// Was a match found
	if (keyValuePair != m.end())
	{
		// Yes, return the texture.
		return keyValuePair->second;
	}
	else
	{
		// File not found
		// Create a new pait using filename
		auto& texture = m[filename];
		// Load texture
		texture.loadFromFile(filename);
		return texture;
	}
}
