#include <GL\glew.h>
#include "Shader.h"
#include "glm/gtc/type_ptr.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include "..\debuging.h"
#include "..\logging\Logging.h"

//TODO: once logging system is more fleshed out,
//      move the std::cout lines to the new logging
//      system

namespace core { namespace graphics {

	struct ShaderProgramSource {
		std::string VertexSource;
		std::string FragmentSource;
		std::string GeometrySource;
		std::string ComputeSource;
	};

	static ShaderProgramSource parseShader(const std::string& filepath) {
		std::ifstream stream(filepath);

		enum class ShaderType {
			NONE = -1,
			VERTEX,
			FRAGMENT, 
			GEOMETRY, 
			COMPUTE, 
			MAX_SHADER_TYPES //not a vaild shader type,
							 //but used to deduce max number of possible types
		};

		std::string line;
		std::stringstream ss[(int)ShaderType::MAX_SHADER_TYPES];
		ShaderType type = ShaderType::NONE;

		while (getline(stream, line)) {
			if (line.find("#shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
				else if (line.find("geometry") != std::string::npos)
					type = ShaderType::GEOMETRY;
				else if (line.find("compute") != std::string::npos)
					type = ShaderType::COMPUTE;
			}
			else {
				FF_ASSERT(type > ShaderType::NONE); //make sure you wont write to -1 index
				ss[(int)type] << line << "\n";
			}
		}

		return { ss[0].str(), ss[1].str(), ss[2].str(), ss[3].str() };
	}

	static unsigned int compileShader(unsigned int type, const std::string& source) {

		//std::cout << "DUMPING SHADER SOURCE: \n" << source << std::endl;


		if (source.empty()) {
			return 0;
		}

		GLCall(unsigned int id = glCreateShader(type));
		const char* src = source.c_str();
		GLCall(glShaderSource(id, 1, &src, nullptr));
		GLCall(glCompileShader(id));

		int result;
		GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE) {
			int length;
			GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
			char* message = (char*)alloca(length * sizeof(char));
			GLCall(glGetShaderInfoLog(id, length, &length, message));
			std::cout << "FAILED TO COMPILE ";
			switch (type) {
			case GL_VERTEX_SHADER:
				std::cout << "VERTEX ";
				break;
			case GL_FRAGMENT_SHADER:
				std::cout << "FRAGMENT ";
				break;
			case GL_GEOMETRY_SHADER:
				std::cout << "GEOMETRY ";
				break;
			case GL_COMPUTE_SHADER:
				std::cout << "COMPUTE ";
				break;
			default:
				std::cout << "UNKNOWN ";
			}
			std::cout << "SHADER" << std::endl;
			std::cout << message << std::endl;
			GLCall(glDeleteShader(id));
			FF_ASSERT(false);
			return 0;
		}

		return id;

	}

	static unsigned int createShader(ShaderProgramSource src) {

		GLCall(unsigned int program = glCreateProgram());
		unsigned int vertShader = compileShader(GL_VERTEX_SHADER, src.VertexSource);
		unsigned int fragShader = compileShader(GL_FRAGMENT_SHADER, src.FragmentSource);
		unsigned int geomShader = compileShader(GL_GEOMETRY_SHADER, src.GeometrySource);
		unsigned int compShader = compileShader(GL_COMPUTE_SHADER, src.ComputeSource);

		if (vertShader) {
			GLCall(glAttachShader(program, vertShader));
		}

		if (fragShader) {
			GLCall(glAttachShader(program, fragShader));
		}

		if (geomShader) {
			GLCall(glAttachShader(program, geomShader));
		}

		if (compShader) {
			GLCall(glAttachShader(program, compShader));
		}

		GLCall(glLinkProgram(program));

		int result;
		GLCall(glGetProgramiv(program, GL_LINK_STATUS, &result));
		if (result == GL_FALSE) {
			int length;
			GLCall(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));
			char* message = (char*)alloca(length * sizeof(char));
			GLCall(glGetProgramInfoLog(program, length, &length, message));
			std::cout << "FAILED TO LINK PROGRAM: \n";
			std::cout << message << std::endl;
			GLCall(glDeleteProgram(program));
			FF_ASSERT(false);
		}

		GLCall(glValidateProgram(program));

		GLCall(glDeleteShader(vertShader));
		GLCall(glDeleteShader(fragShader));
		GLCall(glDeleteShader(geomShader));
		GLCall(glDeleteShader(compShader));

		return program;

	}
	
	Shader::Shader(const std::string& filepath) {
		ShaderProgramSource src = parseShader(filepath);
		shaderID = createShader(src);
		if (shaderID == 0) {
			Log::printError("Failed to create shader!");
		}
	}

	Shader::~Shader() {

		GLCall(glDeleteProgram(shaderID));

	}

	void Shader::bind() const {
		GLCall(glUseProgram(shaderID));
	}

	void Shader::unbind() const {
		GLCall(glUseProgram(0));
	}

	int Shader::getUniformLocation(const char* identifier) {
		int out;
		GLCall(out = glGetUniformLocation(shaderID, identifier));
		return out;
	}

	void Shader::setUniform1i(const char* location, int data) {
		GLCall(glUniform1i(getUniformLocation(location), data));
	}

	void Shader::setUniform1f(const char* location, float data) {
		GLCall(glUniform1f(getUniformLocation(location), data));
	}

	void Shader::setUniformVec2(const char* location, const glm::vec2& data) {
		GLCall(glUniform2fv(getUniformLocation(location), 1, glm::value_ptr(data)));
	}

	void Shader::setUniformVec3(const char* location, const glm::vec3& data) {
		GLCall(glUniform3fv(getUniformLocation(location), 1, glm::value_ptr(data)));
	}

	void Shader::setUniformVec4(const char* location, const glm::vec4& data) {
		GLCall(glUniform4fv(getUniformLocation(location), 1, glm::value_ptr(data)));
	}

	void Shader::setUniformMat4(const char* location, const glm::mat4& data) {
		GLCall(glUniformMatrix4fv(getUniformLocation(location), 1, GL_FALSE, glm::value_ptr(data)));
	}

} }