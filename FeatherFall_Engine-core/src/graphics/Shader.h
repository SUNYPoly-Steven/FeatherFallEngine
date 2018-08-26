#pragma once
#include <iostream>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/matrix.hpp>


namespace core { namespace graphics {

	class Shader {
	private:

		unsigned int shaderID;

	public:

		Shader(const std::string& filepath);
		~Shader();

		void bind() const ;
		void unbind() const ;

		int getUniformLocation(const char* identifier);

		void setUniform1i(const char* location, int data);
		void setUniform1f(const char* location, float data);
		void setUniformVec2(const char* location, const glm::vec2& data);
		void setUniformVec3(const char* location, const glm::vec3& data);
		void setUniformVec4(const char* location, const glm::vec4& data);
		void setUniformMat4(const char* location, const glm::mat4& data);


	private:



	};


} }