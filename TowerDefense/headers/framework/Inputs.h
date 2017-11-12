#pragma once

#include <stdlib.h>
#include <GL/glut.h>

class Inputs
{

public:
	GLboolean move_player_front = false;
	GLboolean move_player_back = false;
	GLboolean move_player_left = false;
	GLboolean move_player_right = false;

	GLboolean move_camera_up = false;
	GLboolean move_camera_down = false;
	GLboolean move_camera_left = false;
	GLboolean move_camera_right = false;

};

