#include "Window.h"
#include <stb_image.h>
#include <iostream>
#include "../logging/Logging.h"
#include "../debuging.h"

#define MOUSE_ROTATE_SPEED 120


namespace core { namespace graphics {

	bool Window::keys[MAX_KEYS];
	bool Window::buttons[MAX_BUTTONS];
	glm::vec2 Window::mousePos_s;
	glm::vec2 Window::winSize_s;

	Window::Window(const int& pwidth, const int& pheight, const char* ptitle, bool fullScreen, bool vSync) 
		: windowSize(pwidth, pheight), mousePos(0, 0), title(ptitle)
	{

		Log::init(); //probably should not do this here...

		glfwSetErrorCallback(error_callback);

		//Init GLFW
		if (!glfwInit()) { //LOG THIS
			Log::printError("GLFW failed to Initialize!");
			exit(EXIT_FAILURE);
		}

		//Set OpenGL type
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//sample amount
		glfwWindowHint(GLFW_SAMPLES, 8);

		//Create Window
		window = glfwCreateWindow((int)windowSize.x, (int)windowSize.y, title, (fullScreen) ? glfwGetPrimaryMonitor() : NULL , NULL);
		
		//Make sure window exists
		if (!window) {//LOG THIS
			Log::printError("Window was not created!");
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		//Set Window Icon
		GLFWimage image;
		int w, h, bpp;
		unsigned char* rgb = stbi_load("res/icons/colored.png", &w, &h, &bpp, 4);
		if (!rgb) {
			Log::printWarning("Could not load resource: Window Icon");
		}
		else {
			image.width = w;
			image.height = h;
			image.pixels = rgb;
			glfwSetWindowIcon(window, 1, &image);
			stbi_image_free(rgb);
		}
		//Make OpenGL context Current
		glfwMakeContextCurrent(window);

		//Init GLEW
		if (glewInit() != GLEW_OK) {//LOG THIS
			Log::printError("GLEW Failed to Initialize!");
		}

		//Print OpenGL version
		Log::printText((const char*)glGetString(GL_VERSION));

		//set the windowUserPointer so that this object can be referenced in the callbacks
		glfwSetWindowUserPointer(window, (void*)this); 

		//turns vSync on if told to do so
		if (vSync) {
			glfwSwapInterval(1);
		}

		//Set Callbacks
		glfwSetKeyCallback(window, key_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetWindowSizeCallback(window, window_size_callback);

		//Set all keys to default
		for (int i = 0; i < MAX_KEYS; ++i) {
			keys[i] = false;
		}

		//Set all buttons to default
		for (int i = 0; i < MAX_BUTTONS; ++i) {
			buttons[i] = false;
		}

		//enables alpha blending
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		//enable use of depth buffer
		GLCall(glEnable(GL_DEPTH_TEST));

		//enable multi sampling
		GLCall(glEnable(GL_MULTISAMPLE));

		//GLCall(glDisable(GL_CULL_FACE));

	}

	Window::~Window() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	bool Window::windowShouldClose() const  {
		return glfwWindowShouldClose(window);
	}

	const glm::vec2& Window::getWindowSize() const {
		return windowSize;
	}

	const glm::vec2& Window::getMousePos() const {
		return mousePos;
	}

	const glm::vec2& Window::getMousePos_s() {
		return Window::mousePos_s;
	}

	const glm::vec2& Window::getWindowSize_s()
	{
		return winSize_s;
	}

	void Window::update() const {
		glfwSwapBuffers(window);
		glfwPollEvents();
		if (isKeyPressed(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window, true);
	}

	void Window::clear() const {
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void Window::setClearColor(const glm::vec4& color) const {
		GLCall(glClearColor(color.x, color.y, color.z, color.w));
	}

	bool Window::isKeyPressed(unsigned int keycode) {
		if (keycode >= MAX_KEYS)
			return false;
		return Window::keys[keycode];
	}

	bool Window::isButtonPressed(unsigned int button) {
		if (button >= MAX_BUTTONS)
			return false;
		return Window::buttons[button];
	}

	void error_callback(int err_code, const char* description) {
		std::cout << "GLFW ERROR (" << err_code << "): " << description << std::endl;
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->keys[key] = (action != GLFW_RELEASE);
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->buttons[button] = (action != GLFW_RELEASE);
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {

		static bool firstMouseMove = true;
		Window* win = (Window*)glfwGetWindowUserPointer(window);

		Window::mousePos_s.x = (float)xpos;
		Window::mousePos_s.y = (float)ypos;

		if (win->isButtonPressed(GLFW_MOUSE_BUTTON_1)) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			if (firstMouseMove) {
				win->mousePos.x = (float)xpos;
				win->mousePos.y = (float)ypos;
				firstMouseMove = false;
			}

			double xDiff = xpos - win->mousePos.x;
			double yDiff = ypos - win->mousePos.y;

			xDiff /= win->windowSize.x;
			yDiff /= win->windowSize.y;

			win->camera->rotateRight((float)glm::radians(-xDiff * MOUSE_ROTATE_SPEED));
			win->camera->rotateUp((float)glm::radians(-yDiff * MOUSE_ROTATE_SPEED));

			win->mousePos.x = (float)xpos;
			win->mousePos.y = (float)ypos;


		}
		else {

			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			win->mousePos.x = (float)xpos;
			win->mousePos.y = (float)ypos;

		}

			

	}

	void window_size_callback(GLFWwindow* window, int width, int height) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->windowSize.x = (float)width;
		win->windowSize.y = (float)height;
		GLCall(glViewport(0, 0, width, height));
	}


} }