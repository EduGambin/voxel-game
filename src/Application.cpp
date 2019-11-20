#include "Application.hpp"

void Application::error_callback(int error, const char* description)
{
	std::cerr << "Error (" << error << "): " << description << std::endl;
}

int Application::init()
{
	// Initializing the variables.
	this->window = nullptr;
	this->delta_time = 0.016f;

	// Initializing GLFW.
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return APP_FAILURE;
	}

	// Setting the error callback function.
	glfwSetErrorCallback(this->error_callback);

	// Setting the OpenGL version.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Setting the window options.
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	// Creating the window.
	this->window = glfwCreateWindow(APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT, APP_NAME, NULL, NULL);
	if (!this->window)
	{
		std::cerr << "Failed to create the GLFW window" << std::endl;
		return APP_FAILURE;
	}
	// Making current context.
	glfwMakeContextCurrent(window);

	// Initializing GLAD.
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return APP_FAILURE;
	}

	// Setting the key-pressed callback function.
	glfwSetKeyCallback(this->window, this->ih.key_callback);
	// Setting the mouse callback function.
	glfwSetCursorPosCallback(this->window, this->ih.cursor_position_callback);
	// Setting the mouse-butons callback function.
	glfwSetMouseButtonCallback(this->window, this->ih.mouse_button_callback);

	// Initializing the camera.
	this->camera.init();

	// Setting the cursor mode.
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Initializing the input handler.
	if (this->ih.init(&camera, &this->delta_time))
	{
		std::cerr << this->gh.get_error_info() << std::endl;
		std::cerr << "Failed to initialize the input handler" << std::endl;
		return APP_FAILURE;
	}

	// Initializing the engine handler.
	if (this->eh.init(&camera, &this->delta_time))
	{
		std::cerr << this->eh.get_error_info() << std::endl;
		std::cerr << "Failed to initialize the engine handler" << std::endl;
		return APP_FAILURE;
	}

	// Initializing the graphic handler.
	if (this->gh.init(&camera, &this->delta_time))
	{
		std::cerr << this->gh.get_error_info() << std::endl;
		std::cerr << "Failed to initialize the graphic handler" << std::endl;
		return APP_FAILURE;
	}

	return APP_SUCCESS;
}

void Application::destroy()
{
	this->eh.destroy();
	this->gh.destroy();
	glfwDestroyWindow(this->window);
	glfwTerminate();
}

void Application::run()
{
	this->delta_time = 0.0f;
	float last_frame = 0.0f;
	while (!glfwWindowShouldClose(this->window))
	{
		// Updating the delta time.
		float current_frame = glfwGetTime();
		this->delta_time = current_frame - last_frame;
		last_frame = current_frame;

		// Updating everything else.
		glfwPollEvents();
		this->ih.update();
		this->eh.update();
		this->gh.update();
		glfwSwapBuffers(this->window);
	}
}