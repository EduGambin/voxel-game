#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Global.hpp"

#define CAMERA_DEFAULT_YAW			-90.0f
#define CAMERA_DEFAULT_PITCH		  0.0f
#define CAMERA_DEFAULT_SPEED		  5.0f
#define CAMERA_DEFAULT_SENSITIVITY	  0.1f

#define CAMERA_DIR_FORWARD	0
#define CAMERA_DIR_BACKWARD	1
#define CAMERA_DIR_LEFT		2
#define CAMERA_DIR_RIGHT	3

#define CAMERA_CONSTRAIN_PITCH 89.0f

class Camera
{
	private:
		// Current camera position in world space.
		glm::vec3 position;

		// Camera's view direction.
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;

		// Euler angles.
		float yaw;
		float pitch;

		// Calculates the front vector from the Camera's (updated) Euler angles
		void update_camera_vectors();

	public:
		void init();

		// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
		glm::mat4 get_view_matrix();

		// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
		void move(int direction, float delta_time);

		// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
		void turn(float xoffset, float yoffset);
};
#endif