#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

class Particle {
public:
    float x;
    float y;

    Particle(float x, float y) : x(x), y(y) {}
};

// Particle container
std::vector<Particle> particles;

// Spatial partitioning
std::vector<std::vector<std::vector<Particle*>>> grid;

const int GRID_SIZE = 10;

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

void UpdateGrid() {
    // Clear grid
    for (auto& row : grid) {
        for (auto& col : row) {
            col.clear();
        }
    }
    // Add particles to grid
    for (int i = 0; i < particles.size(); i++) {
        int x = (particles[i].x + 1.0f) / 2.0f * GRID_SIZE;
        int y = (particles[i].y + 1.0f) / 2.0f * GRID_SIZE;

        if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE) {
            continue;
        }
        grid[x][y].push_back(&particles[i]);
    }
}

void InitParticles() {
    particles.clear();

    int numParticlesX = 20;
    int numParticlesY = 20;

    float spacingX = 2.0f / numParticlesX;
    float spacingY = 2.0f / numParticlesY;

    // Loop over particles and set their positions on a regular grid
    for (int i = 0; i < numParticlesX; i++) {
        for (int j = 0; j < numParticlesY; j++) {
            float posX = -1.0f + i * spacingX + spacingX / 2.0f;
            float posY = -1.0f + j * spacingY + spacingY / 2.0f;
            particles.push_back(Particle(posX, posY));
        }
    }
}


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

    // Add particles
    /*for (int i = 0; i < 1000; i++) {
        float x = (float)rand() / rand_max * 2.0f - 1.0f;
        float y = (float)rand() / rand_max * 2.0f - 1.0f;
        particles.emplace_back(x, y);
    }*/
    InitParticles();

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        UpdateGrid();
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

    glfwTerminate();

    return 0;
}
