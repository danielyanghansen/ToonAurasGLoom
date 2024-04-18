#pragma once

#include "config.hpp"

class Camera {
public:
    glm::vec3 position;
    glm::mat4 projection;

    float yaw = -90.0f; // Initial yaw pointing to -Z
    float pitch = 0.0f;
    float mouseSensitivity = 0.1f;
    //Consider implementing targeting

    Camera(glm::vec3 position, glm::mat4 projection) : position(position), projection(projection) {}

    glm::mat4 getViewMatrix() {
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        return 
            glm::lookAt(position, position + glm::normalize(direction), glm::vec3(0.0f, 1.0f, 0.0f))
            * glm::translate(glm::mat4(1.0f), -position)
            * projection
            ;
    }

    void processMouseMovement(float xoffset, float yoffset) {
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        yaw += xoffset;
        pitch -= yoffset;

        // Constrain the pitch
        pitch = glm::clamp(pitch, -89.0f, 89.0f);
    }

};

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    static float lastX = 400, lastY = 300;
    static bool firstMouse = true;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    Camera* cam = reinterpret_cast<Camera*>(glfwGetWindowUserPointer(window));
    cam->processMouseMovement(xoffset, yoffset);
}

