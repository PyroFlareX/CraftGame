#pragma once

#include <vector>
#include <string>
#include "../Types/Types.h"

namespace vn
{
	class Image
	{
	public:
		Image();

		~Image();

		void copy(const Image& src, vec2 dest);

		void create(unsigned int x, unsigned int y, const u8vec4& color);
		void create(unsigned int x, unsigned int y, const uint8_t* pixels);

		bool loadFromFile(const std::string& filename);
		bool loadFromMemory(const void* data, std::size_t size);

		bool saveToFile(const std::string& filename);

		vec2 getSize() const;
		const unsigned char* getPixelsPtr() const;

		void setPixel(unsigned int x, unsigned int y, const u8vec4& color);
		u8vec4 getPixel(unsigned int x, unsigned int y) const;

		void flipVertically();
		void flipHorizontally();

	private:
		vec2i m_size;
		std::vector<unsigned char> m_pixels;

		const int toIndex(const unsigned int x, const unsigned int y) const;
	};

}