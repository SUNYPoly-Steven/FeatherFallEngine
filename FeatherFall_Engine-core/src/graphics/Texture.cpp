#include "Texture.h"
#include <GL/glew.h>
#include <stb_image.h>
#include "../debuging.h"
#include "../logging/Logging.h"

namespace core { namespace graphics {

	Texture::Texture(std::string pfilepath)
		: textureID(0), filepath(pfilepath), pixels(nullptr), width(0), height(0), bpp(0)
	{
		stbi_set_flip_vertically_on_load(1); //OpenGL expects the image to start @ bottom left
		pixels = stbi_load(filepath.c_str(), &width, &height, &bpp, 4);

		GLCall(glGenTextures(1, &textureID));
		GLCall(glBindTexture(GL_TEXTURE_2D, textureID));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*)pixels));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		if (!pixels) {
			//improve logging to show filepath too!
			Log::printWarning("Failed to load texture!");
			Log::printWarning(filepath.c_str());
		}

	}

	Texture::~Texture() {
		/* 
		 * this could be deleted in ctor,
		 * however in the name of "future proofing"
		 * I am deleting it here in case I should
		 * want to do any CPU side calculations with
		 * the texture
		 */
		SAFE_DELETE(pixels); 
		GLCall(glDeleteTextures(1, &textureID));
	}

	void Texture::bind(unsigned int slot /* = 0 */) const {

		if (slot >= 32) {
			Log::printError("Texture slot can only be values 0 - 31!");
			FF_ASSERT(false);
		}

		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, textureID));
	}

	void Texture::unbind() const {
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

} }