#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <config.h>

#ifdef USE_ADDER
    #include <adder.h>
#endif

int main(int argc, char *argv[])
{

#ifdef USE_ADDER
    printf("Using Adder Lib: 42.5 + 8.1 = %f\n", add(42.5f, 8.1f));
#else
    printf("Not Using Adder Lib: 42.5 + 8.1 = %f\n", 42.5f + 8.1f);
#endif

    printf("%s VERSION: %i.%i\n", argv[0], ModernCmake_VERSION_MAJOR, ModernCmake_VERSION_MINOR);

	GLFWwindow* window;
    int width, height;

    if( !glfwInit() )
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow( 300, 300, "Gears", NULL, NULL );
    if (!window)
    {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Main loop
    while( !glfwWindowShouldClose(window) )
    {
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    // Exit program
    exit( EXIT_SUCCESS );
}
