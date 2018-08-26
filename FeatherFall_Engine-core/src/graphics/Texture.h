#pragma once
#include <string>

namespace core { namespace graphics {

	class Texture {
	private:

		unsigned int textureID;
		std::string filepath;
		unsigned char* pixels;
		int width, height, bpp;

	public:

		Texture(std::string pfilepath);
		~Texture();

		void bind(unsigned int slot = 0) const ;
		void unbind() const ;

		inline const std::string& getFilePath() const { return filepath; }
		inline const unsigned char* const getPixels() const { return pixels; }
		inline int getWidth() const { return width; }
		inline int getHeight() const { return height; }
		inline int getBPP() const { return bpp; }

	private:



	};

} }