#ifndef ENGINE_HANDLER
#define ENGINE_HANDLER

#include <string>
#include <array>
#include <list>
#include "Global.hpp"
#include "Camera.hpp"
#include "engine/Chunk.hpp"

#define EH_MAX_LOADED_CHUNKS 2

class Engine_handler
{
	private:
		// Holds the error info.
		std::string error_info;
		// Camera with the player's current view.
		// Link between handlers.
		Camera* camera;
		// Delta time shared among all handlers.
		float* delta_time;

		// Loaded chunks.
		std::array<Chunk*, EH_MAX_LOADED_CHUNKS> chunks;
		// Vertices that will be drawn.
		std::list<float> mesh;

	public:
		// Initializes everything, should be called before anything else.
		// Returns APP_SUCCESS on success and APP_FAILURE otherwise.
		int init(Camera* camera, float* delta_time);

		// Updates everything related to the engine.
		void update();

		// Destroys every object and cleans everything.
		// Should be called at the end of the program.
		void destroy();

		// Getters and setters.
		std::string get_error_info() const;
};

#endif