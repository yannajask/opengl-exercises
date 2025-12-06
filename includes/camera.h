#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0;

class Camera {
    public:
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;

        float Yaw;
        float Pitch;

        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;

        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
               glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
               float yaw = YAW,
               float pitch = PITCH) :
            Position(position), 
            Front(glm::vec3(0.0f, 0.0f, -1.0f)), 
            WorldUp(up),
            Yaw(yaw), 
            Pitch(pitch),
            MovementSpeed(SPEED), 
            MouseSensitivity(SENSITIVITY), 
            Zoom(ZOOM) 
        {
            updateCameraVectors();
        }

        Camera(float posX, float posY, float posZ, float upX, 
               float upY, float upZ, 
               float yaw, float pitch) :
            Camera(glm::vec3(posX, posY, posZ), glm::vec3(upX, upY, upZ), yaw, pitch) {}
        
        glm::mat4 GetViewMatrix() { return glm::lookAt(Position, Position + Front, Up); }

        void ProcessKeyboard(Camera_Movement direction, float deltaTime) {
            float velocity = MovementSpeed * deltaTime;

            switch(direction) {
                case FORWARD:
                    Position += Front * velocity;
                    break;
                case BACKWARD:
                    Position -= Front * velocity;
                    break;
                case LEFT:
                    Position -= Right * velocity;
                    break;
                case RIGHT:
                    Position += Right * velocity;
                    break;   
            }
        }

        void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true) {
            xOffset *= MouseSensitivity;
            yOffset *= MouseSensitivity;
            Yaw += xOffset;
            Pitch += yOffset;

            if (constrainPitch) {
                if (Pitch > 89.0f) {
                    Pitch = 89.0f;
                } else if (Pitch < -89.0f) {
                    Pitch = -89.0f;
                }
            }

            updateCameraVectors();
        }

        void ProcessMouseScroll(float yOffset) {
            Zoom -= float(yOffset);
            if (Zoom <  1.0f) {
                Zoom = 1.0f;
            } else if (Zoom > 45.0f) {
                Zoom = 45.0f;
            }
        }

    private:
        void updateCameraVectors() {
            glm::vec3 front;

            front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            front.y = sin(glm::radians(Pitch));
            front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

            Front = glm::normalize(front);
            Right = glm::normalize(glm::cross(Front, WorldUp));
            Up = glm::normalize(glm::cross(Right, Front));
        }
};