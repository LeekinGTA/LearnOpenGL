//create a window

#define GLEW_STATIC
#include <glew.h>
// GLFW
#include <glfw3.h>
#include <iostream>
using std::cout;
using std::endl;
const static int height = 600;
const static int width = 800;

int main()
{
	glfwInit();//init glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glViewport(200,300, 800, 600);
	GLFWwindow  *window = glfwCreateWindow(width, height, "myFirstwindows", nullptr, nullptr);
	if (window)
	{
		std::cout << "create windows is failed" << endl;
		glfwTerminate();
		system("PAUSE");
		return -1;
	}
	glfwMakeContextCurrent(window);
	//game loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		//set window color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	glfwTerminate();//clear glfw use space
	return 0;
}
