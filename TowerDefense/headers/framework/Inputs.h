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

	GLboolean playerShooting = false;

	GLboolean zoom_in = false;
	GLboolean zoom_out = false;

	GLboolean activate_wave = false;
	GLboolean kill_all_enemies = false;

	GLboolean kill_player = false;

};

