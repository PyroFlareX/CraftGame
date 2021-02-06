#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"

namespace vn
{
	Image::Image()	:	m_size(0, 0)
	{

	}

	Image::~Image()
	{

	}

	void Image::copy(const Image& src, vec2 dest)
	{

	}

	void Image::create(unsigned int x, unsigned int y, const u8vec4& color)
	{
		m_size = vec2(x, y);
		std::vector<unsigned char> newImage(x * y * 4);

		unsigned char* ptr = &newImage[0];
		unsigned char* end = ptr + newImage.size();
		while (ptr < end)
		{
			*ptr++ = color.r;
			*ptr++ = color.g;
			*ptr++ = color.b;
			*ptr++ = color.a;
		}
		m_pixels.swap(newImage);
	}

	void Image::create(unsigned int x, unsigned int y, const uint8_t* pixels)
	{
		m_size = vec2(x, y);

		std::vector<unsigned char> newPixels(pixels, pixels + x * y * 4);
		m_pixels.swap(newPixels);
	}

	bool Image::loadFromFile(const std::string& filename)
	{
		int width, height, channels;
		unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);
		//Channels should be 4, R G B and A. If three channels, then :P probably a seg fault
		m_size = vec2(width, height);
		m_pixels.resize(width * height * 4);

#ifdef NO_C_HEAP
		for (auto i = 0; i < width * height * 4; ++i)
		{
			m_pixels[i] = data[i];
		}
		stbi_image_free(data);
#else
		m_pixels.resize(width * height * 4);
		memcpy(&m_pixels[0], data, m_pixels.size());
#endif // NO_C_HEAP


		return false;
	}

	bool Image::loadFromMemory(const void* data, std::size_t size)
	{
		// Load the image and get a pointer to the pixels in memory
		int width = 0;
		int height = 0;
		int channels = 0;
		const unsigned char* buffer = static_cast<const unsigned char*>(data);
		unsigned char* ptr = stbi_load_from_memory(buffer, static_cast<int>(size), &width, &height, &channels, STBI_rgb_alpha);

		if (ptr)
		{
			// Assign the image properties
			m_size.x = width;
			m_size.y = height;

			if (width && height)
			{
				// Copy the loaded pixels to the pixel buffer
				m_pixels.resize(width * height * 4);
				memcpy(&m_pixels[0], ptr, m_pixels.size());
			}

			// Free the loaded pixels (they are now in our own pixel buffer)
			stbi_image_free(ptr);

			return true;
		}
		else
		{
			// Error, failed to load the image
			//std::cerr << "Failed to load image from memory. Reason: " << stbi_failure_reason() << std::endl;

			return false;
		}
	}

	bool Image::saveToFile(const std::string& filename)
	{
		//	@TODO	Use stb_image to save image
		/*if(stbi_write_png(filename.c_str(), m_size.x, m_size.y, , m_pixels.data(), 4 * sizeof(unsigned char)))
		{
			return true;
		}
		else*/
		{
		return false;
		}
	}

	vec2 Image::getSize() const
	{
		return m_size;
	}

	const unsigned char* Image::getPixelsPtr() const
	{
		return m_pixels.data();
	}

	void Image::setPixel(unsigned int x, unsigned int y, const u8vec4& color)
	{
		unsigned char* pixel = &m_pixels[toIndex(x, y) * 4];
		*pixel++ = color.r;
		*pixel++ = color.g;
		*pixel++ = color.b;
		*pixel++ = color.a;
	}

	u8vec4 Image::getPixel(unsigned int x, unsigned int y) const
	{
		const unsigned char* pixel = &m_pixels[toIndex(x, y) * 4];
		return u8vec4(pixel[0], pixel[1], pixel[2], pixel[3]);
	}

	void Image::flipVertically()
	{
		
	}

	void Image::flipHorizontally()
	{

	}

	const int Image::toIndex(const unsigned int x, const unsigned int y) const
	{
		int index = 0;

		index = m_size.x * x + y;
		if (index >= (m_size.x * m_size.y))
		{
			return -1;
		}
		return index;
	}

}