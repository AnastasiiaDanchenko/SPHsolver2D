#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <string>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

const int GRID_SIZE = 40;

const float SPACING = 2.0f / GRID_SIZE;
const float SUPPORT = 2.1f * SPACING;

const float REST_DENSITY = 900.f;
const float MASS = REST_DENSITY * pow(SPACING, 2);

const float GRAVITY[2] = { 0.0f, -9.8f };

const float VISCOSITY = 0.5f; //10^-6 m^2/s
const float STIFFNESS = 2000.0f; //acts in normal direction at the surface of the fluid element
const float TIMESTEP = 0.0005f;

class Particle {
public:
    float pos[2] = { 0.0f, 0.0f };
    float vel[2] = { 0.0f, 0.0f };
    float acc[2] = { 0.0f, 0.0f };

    float density = REST_DENSITY;
    float pressure = 0.0f;

    bool isFluid = true;

    std::vector<Particle*> neighbors;

    Particle() {}
};

std::vector<Particle> particles;

void NeighborSearch() {
    for (int i = 0; i < particles.size(); i++) {
        if (particles[i].isFluid == false) {
            continue;
        }
        Particle pi = particles[i];
        for (int j = 0; j < particles.size(); j++) {
			Particle pj = particles[j];
			float r = sqrt(pow(pj.pos[0] - pi.pos[0], 2) + pow(pj.pos[1] - pi.pos[1], 2));
            if (r < SUPPORT) {
                particles[i].neighbors.push_back(&particles[j]);
			}
		}
    }
}

float Kernel(float distance) {
    const float alpha = 5 / (14 * M_PI * pow(SPACING, 2));
    float q = distance / SPACING;
    float W = 0.0f;
    
    if (q < 1) {
        W = alpha * (pow((2 - q), 3) - 4 * pow((1 - q), 3));
	}
    else if (q < 2) {
        W = alpha * pow((2 - q), 3);
	}
    return W;
}

float KernelGradient(float dx, float distance) {
    const float alpha = 5 / (14 * M_PI * pow(SPACING, 2));
    float q = distance / SPACING;
    float W = 0.0f;
    float dq = dx / (distance * SPACING);

    if (q < 1) {
        W = alpha * dq * (-3 * pow((2 - q), 2) + 12 * pow((1 - q), 2));
    }
    else if (q < 2) {
        W = alpha * dq * -3 * pow((2 - q), 2);
    }
    return W;
}

void ComputeDensityPressure() {
    for (int i = 0; i < particles.size(); i++) {
        if (particles[i].isFluid == false) {
            continue;
        }

        float density = 0.0f;
        Particle pi = particles[i];

        for (int j = 0; j < pi.neighbors.size(); j++) {
            Particle pj = *pi.neighbors[j];
			float dx = sqrt(pow((pj.pos[0] - pi.pos[0]), 2) + pow((pj.pos[1] - pi.pos[1]), 2));
			density += MASS * Kernel(dx);
		}

        particles[i].density = density;
        particles[i].pressure = std::max(STIFFNESS * (density / REST_DENSITY - 1), 0.0f);
    }
}

void ComputeAcceleration() {
    for (int i = 0; i < particles.size(); i++) {
        if (particles[i].isFluid == false) {
            continue;
        }

        float accPressure[2] = { 0.0f, 0.0f };
        float accViscosity[2] = { 0.0f, 0.0f };
        Particle pi = particles[i];

        for (int j = 0; j < pi.neighbors.size(); j++) {
            Particle pj = *pi.neighbors[j];
            float dx = pj.pos[0] - pi.pos[0];
            float dy = pj.pos[1] - pi.pos[1];
            float distance = sqrt(pow(dx, 2) + pow(dy, 2));
            float dvx = pj.vel[0] - pi.vel[0];
            float dvy = pj.vel[1] - pi.vel[1];
            float xKernel = KernelGradient(dx, distance);
            float yKernel = KernelGradient(dy, distance);

            accViscosity[0] += dvx * dx / (pj.density * (pow(dx, 2) + 0.01 * pow(SPACING, 2))) * xKernel;
            accViscosity[1] += dvy * dy / (pj.density * (pow(dy, 2) + 0.01 * pow(SPACING, 2))) * yKernel;
        }
        accViscosity[0] *= 2 * VISCOSITY * MASS;
        accViscosity[1] *= 2 * VISCOSITY * MASS;
        accPressure[0] *= MASS;
        accPressure[1] *= MASS;

        particles[i].acc[0] = accViscosity[0] + accPressure[0] + GRAVITY[0];
        particles[i].acc[1] = accViscosity[1] + accPressure[1] + GRAVITY[1];
    }
}

void Integrate() {
}

void Simulation() {

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
