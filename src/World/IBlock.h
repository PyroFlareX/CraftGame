#pragma once

#include "Block.h"



class IBlock
{
public:
	IBlock() = default;

	static const std::string getTextureSideBlock(const Block& block, const directionType& dir)
	{
		switch (block.id)
		{
		case 1:
			if (dir == directionType::top) { return "grass_top"; }
			else if ((dir == directionType::left) || (dir == directionType::right) || (dir == directionType::front) || (dir == directionType::back)) { return "grass_side"; }
		case 2:
			return "dirt";
		case 3:
			return "sand";
		case 4:
			return "stone";
		default:
			return "dirt";
		}
	}
	
	bool isTransparent = false;
	//bool is

private:

};