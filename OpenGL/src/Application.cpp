#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "CompileShaders.h"
#include "SimulationFalling.h"

#include <string>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

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

    Setup();

    //NeighbourSearch(SUPPORT);
    KernelTest(SPACING, GRID_SIZE);

    ShaderProgramSource source = ParseShader("res/shaders/Particle.shader");

    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource, source.GeometrySource);
    //glUseProgram(shader);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        FallingSimulation();

        glClear(GL_COLOR_BUFFER_BIT);

        // Render particles
        for (const Particle& p : particles) {
            glLoadIdentity();
            glTranslatef(p.x, p.y, 0.0f);

            if (p.isFluid) {
                glColor3f(0.0f, 0.0f, 1.0f);
            }
            else {
                glColor3f(0.6f, 0.3f, 0.0f);
            }

            const float radius = 0.02f;
            const int numSegments = 10;
            const float angleIncrement = 2 * M_PI / numSegments;

            // Render filled circle
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(0.0f, 0.0f);  // Center of the circle
            for (int i = 0; i <= numSegments; ++i) {
                const float angle = i * angleIncrement;
                const float x = radius * cos(angle);
                const float y = radius * sin(angle);
                glVertex2f(x, y);
            }
            glEnd();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();

    return 0;
}
