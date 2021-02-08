#pragma once

#include <unordered_map>
namespace vn
{
	template<typename T>
	class Registry
	{
	public:
		Registry() = default;

		void addToRegistry(T res, const int& id)
		{
			m_registry.insert({ id, res });
		}

		T& getAsset(const int& id)
		{
			return m_registry.find(id)->second;
		}

		~Registry() = default;
	private:
		std::unordered_map<int, T> m_registry;
	};
}

#include <SFML/Graphics.hpp>
#include "../Util/Loaders.h"

class TextureManager
{
public:
	TextureManager();

	void addImg(sf::Image img, const std::string& texName);

	sf::Image& getSheet();
	std::array<float, 8> getTexCoords(const std::string& texName);

	~TextureManager();
private:
	void buildTextureSheet();

	std::unordered_map<std::string, std::array<float, 8>> m_blockTexCoordsMap;
	std::vector<std::pair<sf::Image, std::string>> imgs;
	sf::Image sheet;
};

#ifndef _res
#define _res
namespace resources
{
	extern TextureManager TexManager;
	//extern BlockManager BlockDatabase;
}
#endif