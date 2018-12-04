#pragma once
#include <GL\glew.h>
#include "Camera.h"
#include <GLFW\glfw3.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#define MAX_KEYS    1024
#define MAX_BUTTONS 32

namespace core { namespace graphics {

	class Window {
	private:

		glm::vec2 windowSize;
		glm::vec2 mousePos = glm::vec2(0, 0);
		const char* title;

		static bool keys[MAX_KEYS];
		static bool buttons[MAX_BUTTONS];

		static glm::vec2 mousePos_s;
		static glm::vec2 winSize_s;

	public:
		GLFWwindow* window;//NOTE: please move this back into private when ImGui is fully implemented
		Camera* camera; //TODO: there MUST be a better way
						//to handle the camera movement in
						//3D take this out of window.

		Window(const int& pwidth, const int& pheight, const char* ptitle, bool fullScreen, bool vSync);
		~Window();

		bool windowShouldClose() const ;

		const glm::vec2& getWindowSize() const ;
		const glm::vec2& getMousePos() const ;

		static const glm::vec2& getMousePos_s();
		static const glm::vec2& getWindowSize_s();

		void update() const ;
		void clear() const ;
		void setClearColor(const glm::vec4& color) const ;

		static bool isKeyPressed(unsigned int keycode);
		static bool isButtonPressed(unsigned int button);


	private:

		friend static void error_callback(int err_code, const char* description);
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend static void window_size_callback(GLFWwindow* window, int width, int height);




	};

} }