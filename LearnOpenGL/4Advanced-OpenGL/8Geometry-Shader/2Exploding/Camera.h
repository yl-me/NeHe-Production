#pragma once

#include <vector>

#include <gl\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

// �ƶ�����
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Ĭ��ֵ
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera {
public:
	// ����
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// ŷ����
	GLfloat Yaw;
	GLfloat Pitch;
	
	GLfloat MovementSpeed;
	GLfloat MouseSensitivity;
	GLfloat Zoom;

	// ��������
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		GLfloat yaw = YAW, GLfloat pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
		MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		this->Position = position;
		this->WorldUp = up;
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->updateCameraVectors();
	}

	// ֵ����
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw,
		GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
		MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		this->Position = glm::vec3(posX, posY, posZ);
		this->WorldUp = glm::vec3(upX, upY, upZ);
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->updateCameraVectors();
	}

	// ������˺�ת��
	glm::mat4x4 myLookAt(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up);

	// ������ͼ����(ʹ��ŷ���Ǻ�lookAt����)
	glm::mat4 GetViewMatrix();
	

	// ����ƶ����仯������
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);

	// ���
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= this->MouseSensitivity;
		yoffset *= this->MouseSensitivity;

		this->Pitch += yoffset;
		this->Yaw += xoffset;

		if (constrainPitch) {
			if (this->Pitch < -89.0f) {
				this->Pitch = -89.0f;
			}
			if (this->Pitch > 89.0f) {
				this->Pitch = 89.0f;
			}
		}
		this->updateCameraVectors();
	}

	// ����
	void ProcessMouseScroll(GLfloat yoffset);

private: 
	// ŷ����
	void updateCameraVectors();
};