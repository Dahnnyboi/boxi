#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"


void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

float vertices[] = {
    // positions                     // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f,1.0f,0.0f,   // bottom left
    0.0f, 0.5f,0.0f, 0.0f,0.0f,1.0f    // top 
};  

// unsigned int indices[] = { 
//     0, 1, 3,   // first triangle
//     1, 2, 3    // second triangle
// };

int main() {
    if (!glfwInit()) {
        std::cout << "Failed to init GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "boxi", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Stores the vertices to GPU Memory
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // first parameter from this comes from vertex.glsl (location = 0)
    glEnableVertexAttribArray(0); // first parameter from this comes from vertex.glsl (location = 0)

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // first parameter from this comes from vertex.glsl (location = 1) 
    glEnableVertexAttribArray(1); // first parameter from this comes from vertex.glsl (location = 1)

    // unsigned int EBO;
    // glGenBuffers(1, &EBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.useProgram();

        // float timeValue = glfwGetTime();
        // float redValue = (sin(timeValue) / 2.0f) + 0.5f;
        // float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        
        // glUniform4f(vertexColorLocation, redValue, greenValue, 0.5f, 1.0f);

        glBindVertexArray(VAO);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    shader.deleteProgram();

    glfwTerminate();
    return 0;
}