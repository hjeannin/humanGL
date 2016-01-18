#include <iostream>
#include <string>
#include "Initiator.hpp"

static void
keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	Initiator *init = static_cast<Initiator *>(glfwGetWindowUserPointer(window));

	(void)scancode;
	(void)mods;
	(void)init;
	GLfloat			power = 0.2f;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS))
		init->rotate[1] -= power;
	if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS))
		init->rotate[1] += power;
	if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
		init->rotate[0] += power;
	if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS))
		init->rotate[0] -= power;
	if (key == GLFW_KEY_Q && (action == GLFW_REPEAT || action == GLFW_PRESS))
		init->rotate[2] -= power;
	if (key == GLFW_KEY_E && (action == GLFW_REPEAT || action == GLFW_PRESS))
		init->rotate[2] += power;
	if (key == GLFW_KEY_EQUAL && (action == GLFW_REPEAT || action == GLFW_PRESS))
		init->scale += power;
	if (key == GLFW_KEY_MINUS && (action == GLFW_REPEAT || action == GLFW_PRESS))
		init->scale -= power;
	if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS))
		init->translate[2] -= power;
	if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS))
		init->translate[2] += power;
	if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
		init->translate[0] += power;
	if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
		init->translate[0] -= power;
	if (key == GLFW_KEY_PAGE_UP && (action == GLFW_REPEAT || action == GLFW_PRESS))
		init->translate[1] += power;
	if (key == GLFW_KEY_PAGE_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS))
		init->translate[1] -= power;

	init->setModelMatrix();
	// init->debugMatrix();
}

static void
cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	Initiator *init = static_cast<Initiator *>(glfwGetWindowUserPointer(window));
	
	(void)init;
	(void)xpos;
	(void)ypos;
}

#ifndef __APPLE__
static void
glErrorCallback(GLenum        source,
				GLenum        type,
				GLuint        id,
				GLenum        severity,
				GLsizei       length,
				const GLchar* message,
				GLvoid*       userParam)
{
	(void)userParam;
	(void)length;
	std::cerr << "OpenGL Error:" << std::endl;
	std::cerr << "=============" << std::endl;
	std::cerr << " Object ID: " << id << std::endl;
	std::cerr << " Severity:  " << severity << std::endl;
	std::cerr << " Type:      " << type << std::endl;
	std::cerr << " Source:    " << source << std::endl;
	std::cerr << " Message:   " << message << std::endl;
	glFinish();
}
#endif

static int
initGlfw(Initiator &init)
{
	if (!glfwInit())
		return (0);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	init.window = glfwCreateWindow(init.res_x, init.res_y, "HumanGL", NULL, NULL);
	if (!init.window)
	{
		glfwTerminate();
		return (0);
	}
	glfwSetWindowUserPointer(init.window, &init);
	glfwMakeContextCurrent(init.window); // make the opengl context of the init.window current on the main thread
	glfwSwapInterval(1); // VSYNC 60 fps max
	glfwSetKeyCallback(init.window, keyCallback);
	glfwSetCursorPosCallback(init.window, cursorPosCallback);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
#ifndef __APPLE__
	if (glDebugMessageControlARB != NULL)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
		glDebugMessageCallbackARB((GLDEBUGPROCARB)glErrorCallback, NULL);
	}
#endif
	return (1);
}

int main()
{
	Initiator	init;

	// init glfw
	initGlfw(init);

	init.genMatrices();
	init.genShaders();
	init.getLocations();
	init.createCB2Image();
	// init.createCBImage();
	// init.createImage();

	// loop

	double		lastTime, currentTime;
	double		frames;

	frames = 0.0;
	lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(init.window))
	{
		currentTime = glfwGetTime();
		frames += 1.0;
		init.drawImage();
		glfwSwapBuffers(init.window);
		glfwPollEvents();
		if (currentTime - lastTime >= 1.0)
		{
			glfwSetWindowTitle(init.window, std::to_string(1000.0 / frames).c_str());
			frames = 0.0;
			lastTime += 1.0;
		}
	}

    return 0;
}
