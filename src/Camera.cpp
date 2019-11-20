#include "Camera.hpp"

void Camera::update_camera_vectors()
{
	// Calculate the new front vector
	glm::vec3 temp_front;
	temp_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	temp_front.y = sin(glm::radians(pitch));
	temp_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->front = glm::normalize(temp_front);

	// Also re-calculate the right and up vector
	this->right = glm::normalize(glm::cross(this->front, APP_UP_DIR));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}

void Camera::init()
{
	this->position = APP_SPAWN_POS;
	this->yaw = CAMERA_DEFAULT_YAW;
	this->pitch = CAMERA_DEFAULT_PITCH;
	this->update_camera_vectors();

	this->is_data_modified = false;
}

glm::mat4 Camera::get_view_matrix()
{
	return glm::lookAt(this->position, this->position + this->front, this->up);
}

void Camera::move(int direction, float delta_time)
{
	float velocity = CAMERA_DEFAULT_SPEED * delta_time;
	switch (direction)
	{
		case CAMERA_DIR_FORWARD:
			this->position += this->front * velocity;
			break;
		case CAMERA_DIR_BACKWARD:
			this->position -= this->front * velocity;
			break;
		case CAMERA_DIR_LEFT:
			this->position -= this->right * velocity;
			break;
		case CAMERA_DIR_RIGHT:
			this->position += this->right * velocity;
			break;
		case CAMERA_DIR_UP:
			this->position += this->up * velocity;
			break;
		case CAMERA_DIR_DOWN:
			this->position -= this->up * velocity;
			break;
		default:
			break;
	}
}

void Camera::turn(float xoffset, float yoffset)
{
	xoffset *= CAMERA_DEFAULT_SENSITIVITY;
	yoffset *= CAMERA_DEFAULT_SENSITIVITY;

	this->yaw += xoffset;
	this->pitch += yoffset;

	if (this->pitch > CAMERA_CONSTRAIN_PITCH) this->pitch = CAMERA_CONSTRAIN_PITCH;
	if (this->pitch < -CAMERA_CONSTRAIN_PITCH) this->pitch = -CAMERA_CONSTRAIN_PITCH;

	update_camera_vectors();
}