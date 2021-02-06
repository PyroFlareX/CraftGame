#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

#include "../Types/GameObject.h"
#include "../Resources/Mesh.h"
#include "../nlohmann/json.h"

namespace vn
{
	inline std::string getFileString(const std::string& filePath)
	{
		std::ifstream inFile(filePath);
		if (!inFile.is_open())
		{
			throw std::runtime_error("Unable to open file: " + filePath);
		}

		std::stringstream stream;

		stream << inFile.rdbuf();
		inFile.close();
		return stream.str();
	}

	Mesh loadMeshFromObj(const std::string& filepath);
	
	void loadStateFromFile(const std::string& filepath, std::vector<GameObject>& gameObjects);
	void saveStateToFile(const std::string& filepath, std::vector<GameObject>& gameObjects);
}