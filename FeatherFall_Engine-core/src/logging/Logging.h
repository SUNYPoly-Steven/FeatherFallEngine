#pragma once
#include <iostream>
#include <windows.h>

namespace core {

	#define ERROR_COLOR   12
	#define WARNING_COLOR 14
	#define NOMINAL_COLOR 15

	class Log {
	private:

		static HANDLE console;
		static int colorAttrib;

		Log();

	public:

		static void init();

		static void testColors(int num);
		static void printError(const char* text);
		static void printWarning(const char* text);
		static void printText(const char* text);

		static void pause();

	
	private:

		static void resetColor();


	};

}