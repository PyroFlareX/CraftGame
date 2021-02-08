#include "ResourceManager.h"

TextureManager::TextureManager()
{
	/*sf::Image filler;
	filler.create(16, 16, sf::Color::Green);
	for (int x = 4; x <= 12; x++)
	{
		for (int y = 4; y <= 12; y++)
		{
			filler.setPixel(x, y, sf::Color::Blue);
		}
	}
	addImg(filler, "filler");
	*/
	sf::Image img;
	img.loadFromFile("res/Textures/dirt.png");
	addImg(img, "dirt");
	img.loadFromFile("res/Textures/grass_side.png");
	addImg(img, "grass_side");
	img.loadFromFile("res/Textures/grass_top.png");
	addImg(img, "grass_top");
	img.loadFromFile("res/Textures/sand.png");
	addImg(img, "sand");
	img.loadFromFile("res/Textures/stone.png");
	addImg(img, "stone");
}

void TextureManager::addImg(sf::Image img, const std::string& texName)
{
	img.flipVertically();
	imgs.push_back({ img, texName });
}

void TextureManager::buildTextureSheet()
{
	unsigned int x = 0, y = 0;
	sheet.create(256, 256/*16 * ((imgs.size() / 16) + 1)*/);

	sf::Vector2f offsetXY = sf::Vector2f(0.0625f, 0.0625f);

	for (auto& image : imgs)
	{
		sheet.copy(image.first, x * 16, y);

		std::array<float, 8> texCoords;
		texCoords[0] = (float)(offsetXY.x * x);
		texCoords[1] = (float)(offsetXY.y * y);	//1
		texCoords[2] = (float)(offsetXY.x + offsetXY.x * x);
		texCoords[3] = (float)(offsetXY.y * y);	//2
		texCoords[4] = (float)(offsetXY.x + offsetXY.x * x);
		texCoords[5] = (float)(offsetXY.y + offsetXY.y * y);	//3
		texCoords[6] = (float)(offsetXY.x * x);
		texCoords[7] = (float)(offsetXY.y + offsetXY.y * y);	//4

		m_blockTexCoordsMap.insert({ image.second, texCoords });

		++x;
		if (x >= 16)
		{
			x = 0;
			y += 16;
		}
	}
}

sf::Image& TextureManager::getSheet()
{
	buildTextureSheet();
	return sheet;
}

std::array<float, 8> TextureManager::getTexCoords(const std::string& texName)
{
	std::unordered_map<std::string, std::array<float, 8>>::const_iterator iter = m_blockTexCoordsMap.find(texName);
	return iter->second;
}

TextureManager::~TextureManager()
{
	imgs.clear();
}


/*
BlockManager::BlockManager()
{
	Block block(BlockId::DIRT, "dirt");
	addBlock(block, "dirt");
	Block block(BlockId::GRASS, "grass");
	addBlock(block, "grass");
	Block block(BlockId::STONE, "stone");
	addBlock(block, "stone");
}

void BlockManager::addBlock(Block& block, const std::string& blockName)
{
	m_blockMap.insert({ blockName, block });
}

Block& BlockManager::getBlock(const std::string& blockName)
{
	return m_blockMap.find(blockName)->second;
}

BlockManager::~BlockManager()
{

}*/

namespace resources
{
	TextureManager TexManager;
	//BlockManager BlockDatabase;
}
