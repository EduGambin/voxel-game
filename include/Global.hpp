#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <glm/vec3.hpp>

#define APP_SCREEN_WIDTH 1280
#define APP_SCREEN_HEIGHT 720
#define APP_FOV 70.0f
#define APP_ASPCET_RATIO 1.77778f
#define APP_NAME "Minecraft"

#define APP_SUCCESS 0
#define APP_FAILURE -1

#define DEBUG std::cout << "He pasado" << std::endl

const glm::vec3 APP_SPAWN_POS(0.0f, 0.0f, 10.0f);
const glm::vec3 APP_UP_DIR(0.0f, 1.0f, 0.0f);

#endif