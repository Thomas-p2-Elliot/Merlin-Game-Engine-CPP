/*                                                                                           */
/*                                           Header Files                                    */
/*																							 */

//Standard Libraries (iostream, std, etc)
#include "StandardIncludes.h"

//Graphics Libraries (OpenGL, GLFW, etc)
#include "glew.h"
#include "glfw3.h"
	
//Engine Settings & Info
#include "Engine.h"

//Graphics Class
#include "Graphics.h"

//Physics Class
#include "Physics.h"

//Level Class
#include "Level.h"

/*																							 */
/*                                           Global Vars									 */
/*																							 */
Merlin::Level *level;

/*																							 */
/*                                           Program										 */
/*																							 */
using namespace Merlin;


/*                                           Misc                                            */
/*                                                                                           */
void About(){
	printf("Version:	%g \n", MerlinVersion);
	printf("Author:		%s \n", Author);
	printf("StudentID:	%d \n", StudentID);
}

/*                                           GLEW		                                     */
/*                                                                                           */
//Initialise GLEW
void InitialiseGLEW() {
	if (glewInit() != GLEW_OK) {
		printf("FAILED... Unable to initialise GLEW. \n");
	} else {
		printf("PASS... GLEW Initialised. \n");
	}
}

/*                                           GLFW		                                     */
/*                                                                                           */
//Initialise GLFW
void InitialiseGLFW(){
	if (glfwInit() == GL_TRUE){
		printf("PASS... GLFW Initialised, Version: %s. \n", glfwGetVersionString());
	}	else {
		printf("FAILED.. GLFW Initialisation failed. \n");
		exit(EXIT_FAILURE);
	}
}


//Called on GLFW Error
void OnError(int error, const char* description){ fputs(description, stderr); }

//Sets Error callback Function
void SetGLFWErrorCallback(){ glfwSetErrorCallback(OnError); }

//Creates a GLFW Window
GLFWwindow* CreateGLFWwindow(){
	GLFWwindow* window = glfwCreateWindow(Graphics::DEFAULT_WINDOW_WIDTH, Graphics::DEFAULT_WINDOW_HEIGHT, "Merlin Engine", NULL, NULL);
	if (!window) { glfwTerminate(); exit(EXIT_FAILURE); }
	return window;
}


/*                                           Engine                                          */
/*                                                                                           */

//Sets up GLEW, OpenGL, creates & initialises level
void Initialise(){


	//Init glew
	InitialiseGLEW();

	//Set openGL flags
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_LIGHTING);

	//Enable antialiasing
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Create the level
	level = new Merlin::Level("Demo Scene");
	// Load the assets
	level->Initialise();
}


void DoRender(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	level->Update();
}

void DoPhysics(double deltaTime){
		
}


//Main Game Loop
void GameLoop(GLFWwindow* window){
		
	double dt = Physics::stepTime; //Physics updates per second
	double previous = glfwGetTime(); //Records time of last render
	double lag = 0.0; //Time since last physics update


	//Loops & Checks if Close flag is Set (ALT-F4, Close Btn, etc. can Set this)
	while (!glfwWindowShouldClose(window)) {

		//Gets Frame Buffer Size
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		//Sets Viewport Size
		glViewport(0, 0, width, height);

		//Get current time & time since last render & time since last physics update
		double current = glfwGetTime();			           
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;

		//Run physics calculations until lag is less than step time
		while (lag >= dt){ DoPhysics(dt); lag -= dt; }

		//Process events via polling
		glfwPollEvents();

		//Render to the buffer
		DoRender();

		//Swap opengl buffers (double buffering)
		glfwSwapBuffers(window);
	}
}


/*                                           Main                                            */
/*                                                                                           */
int main() {
	//Show Info on Launch
	About();

	//	GLFW Setup
	SetGLFWErrorCallback();
	InitialiseGLFW();

	//Create window
	GLFWwindow* window = CreateGLFWwindow();

	// Get the resolution of the primary monitor
	const GLFWvidmode * vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	//Center the window
	glfwSetWindowPos(
		window,
		(vidmode->width - Graphics::DEFAULT_WINDOW_WIDTH) / 2, (vidmode->height - Graphics::DEFAULT_WINDOW_HEIGHT) / 2
	);

	//Set OpenGL Context to created window
	glfwMakeContextCurrent(window);

	//Set VSYNC
	glfwSwapInterval(VSYNC);

	//Intialise Engine & OpenGL & GLEW & Level
	Initialise();

	//Start Game-Loop
	GameLoop(window);

	//	Close Program
	//Destroy the window
	glfwDestroyWindow(window);
	//Terminate GLFW
	glfwTerminate();
	//Exit via STD lib
	exit(EXIT_SUCCESS);
}
