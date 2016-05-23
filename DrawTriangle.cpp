//draw a trangle

#define GLEW_STATIC

#include <glew.h>
#include <glfw3.h>
#include <iostream>

using std::cout;
using std::endl;

//Keyboard Event
void keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mode);
//window's width and height
const GLuint winWidth = 800, winHeight = 600;

const GLchar *vertexShaderSource = "#version 330 core\n"
"layout (location=0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position=vec4(position.x,position.y,position.z,1.0);\n"
"}\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color=vec4(1.0f,0.5f,0.2f,1.0f);\n"
"}\n\0";

int main()
{
	//init glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//use glfwCreateWindow function create window object
	GLFWwindow *window = glfwCreateWindow(winWidth, winHeight, "TriangleWindow", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyCallBack);

	glewExperimental = GL_TRUE;

	glewInit();
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	//build and compile our shader program
	//Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	//check compile time error
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	//fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	//check compile time error
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	//link shader
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//check link error
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << endl;
	}
	//delete shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//set up vertex data and attribute pointer
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,//Left point
		0.5f,-0.5f,0.0f,//Right point
		0.0f,0.5f,0.0f //top point
	};
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//Bind the vertex Array Object first,then bind and set vertex buffer (0)and attribute pointer
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);//unbind VBO
	glBindVertexArray(0);//unbind VAO

	//game loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		//Render
		//clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw a triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		//swap the screen buffer
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	//claer all gl data
	glfwTerminate();
	return 0;
}

void keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE&&action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
