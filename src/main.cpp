#include <iostream>
#include <adder.h>
#include <GLFW/glfw3.h>
#include <HelloConfig.h>

int main(int argc, char* argv[])
{
  std::cout << "Hello World (from C++)" << std::endl;
  std::cout << "sum = " << add(72.1, 73.8) << std::endl;
  std::cout << argv[0] << " Version " << HELLO_VERSION_MAJOR << "." << HELLO_VERSION_MINOR << std::endl;

  if (!glfwInit())
  {
    fprintf(stderr, "Failed to initialize GLFW\n");
    exit(EXIT_FAILURE);
  }
  GLFWwindow *window;
  window = glfwCreateWindow(300, 300, "Gears", NULL, NULL);
  if (!window)
  {
    fprintf(stderr, "Failed to open GLFW window\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  // Main loop
  while (!glfwWindowShouldClose(window))
  {
    // Draw gears
    // draw();

    // Update animation
    // animate();

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Terminate GLFW
  glfwTerminate();

  // Exit program
  exit(EXIT_SUCCESS);
}
