#include <iostream>
#include <string>
#include "Initiator.hpp"

static void
keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	Initiator 		*init = static_cast<Initiator *>(glfwGetWindowUserPointer(window));

	(void)scancode;
	(void)mods;
	(void)init;
		
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		init->printArray(init->faces_array, init->faces_num_elem);
	std::cerr << init->isSet << std::endl;
}

static void
cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	Initiator	*init = static_cast<Initiator *>(glfwGetWindowUserPointer(window));

	// std::cout << "x: " << xpos << std::endl;
	// std::cout << "y: " << ypos << std::endl;
	// lock mouse so it can set it a the center after X11 ready
	if (xpos <= 300 && ypos <= 300)
	{
		glfwSetCursorPos(init->window, init->res_x / 2, init->res_y / 2);
	}
	else
	{
		init->camera.vangle -= ((ypos - init->res_y / 2) * init->camera.speed);
		if (init->camera.vangle > 89)
			init->camera.vangle = 89;
		if (init->camera.vangle < -89)
			init->camera.vangle = -89;
		init->camera.hangle += ((xpos - init->res_x / 2) * init->camera.speed);
		init->camera.hangle = fmod(init->camera.hangle, 360);
		glfwSetCursorPos(init->window, init->res_x / 2, init->res_y / 2);
	}
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
	init.isSet = 0;
	glfwSetWindowUserPointer(init.window, &init);
	glfwMakeContextCurrent(init.window); // make the opengl context of the init.window current on the main thread
	glfwSwapInterval(1); // VSYNC 60 fps max
	glfwSetKeyCallback(init.window, keyCallback);
	glfwSetCursorPosCallback(init.window, cursorPosCallback);
	glfwSetInputMode(init.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //hide cursor
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

void
updateCamera(Initiator &init)
{
	init.camera.rotate();
	if (glfwGetKey(init.window, GLFW_KEY_W) == GLFW_PRESS)
		init.camera.moveForward();
	if (glfwGetKey(init.window, GLFW_KEY_S) == GLFW_PRESS)
		init.camera.moveBackward();
	if (glfwGetKey(init.window, GLFW_KEY_A) == GLFW_PRESS)
		init.camera.strafeLeft();
	if (glfwGetKey(init.window, GLFW_KEY_D) == GLFW_PRESS)
		init.camera.strafeRight();
}

int main()
{
	Initiator	init;

	// init glfw
	initGlfw(init);

//	glEnable(GL_CULL_FACE);

	// default is GL_CCW
//	glFrontFace(GL_CW);
	
	init.genMatrices();
	init.genShaders();
	init.createImage();

	// loop
	double		lastTime, currentTime;
	double		frames;

	frames = 0.0;
	lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(init.window))
	{
		currentTime = glfwGetTime();
		frames += 1.0;
		updateCamera(init);
		init.drawModel(init.mod->part, init.mod->getPartCount());
		glfwSwapBuffers(init.window);
		glfwPollEvents();
		if (currentTime - lastTime >= 1.0)
		{
			glfwSetWindowTitle(init.window, std::to_string(1000.0 / frames).c_str());
			frames = 0.0;
			lastTime += 1.0;
		}
		init.isSet++;
	}

	return 0;
}
