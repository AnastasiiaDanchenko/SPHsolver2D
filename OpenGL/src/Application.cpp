#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "CompileShaders.h"
#include "NeighbourSearch.h"
#include "CubicSplineKernel.h"

#include <string>

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

const int GRID_SIZE = 10;
const float SPACING = 2.0f / GRID_SIZE;
const float SUPPORT = 2.1 * SPACING;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "SPH solver in 2D", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, keyCallback);

    // Initialize grid
    grid.resize(GRID_SIZE, std::vector<std::vector<Particle*>>(GRID_SIZE));

    InitParticles(GRID_SIZE, SPACING);

    UpdateGrid(GRID_SIZE);
    RotateGrid(45.0f);
    TranslateGrid(0.5f, 0.5f);

    NeighbourSearch(SUPPORT);

    KernelTest(SPACING, GRID_SIZE);

    ShaderProgramSource source = ParseShader("res/shaders/Particle.shader");

    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource, source.GeometrySource);
    glUseProgram(shader);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        UpdateGrid(GRID_SIZE);

        glClear(GL_COLOR_BUFFER_BIT);

        // Render particles
        glPointSize(5.0);
        glBegin(GL_POINTS);
        for (const Particle& p : particles) {
            glVertex2f(p.x, p.y);
        }
        glEnd();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();

    return 0;
}
