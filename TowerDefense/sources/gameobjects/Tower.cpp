#include "../../headers/gameobjects/Tower.h"
#include "../../headers/components/Transform.h"
#include "../../headers/gameobjects/LifeBar.h"
#include "../../headers/objloader/glm.h"

GLMmodel* towerModel = NULL;

Tower::Tower()
{
	addComponent("transform", new Transform());
}

Tower::~Tower()
{
}

void Tower::initModel()
{
	// Load the model only if it hasn't been loaded before
	// If it's been loaded then pmodel1 should be a pointer to the model geometry data...otherwise it's null
	if (!towerModel)
	{
		// this is the call that actualy reads the OBJ and creates the model object
		towerModel = glmReadOBJ("resources/tower/Tower_obj.obj", "resources/tower/Texture_.tga");
		if (!towerModel) exit(0);
		// This will rescale the object to fit into the unity matrix
		// Depending on your project you might want to keep the original size and positions you had in 3DS Max or GMAX so you may have to comment this.
		glmUnitize(towerModel);
		// These 2 functions calculate triangle and vertex normals from the geometry data.
		// To be honest I had some problem with very complex models that didn't look to good because of how vertex normals were calculated
		// So if you can export these directly from you modeling tool do it and comment these line
		// 3DS Max can calculate these for you and GLM is perfectly capable of loading them
		glmFacetNormals(towerModel);
		glmVertexNormals(towerModel, 90.0);
	}

	// This is the call that will actualy draw the model
	// Don't forget to tell it if you want textures or not :))
	glmDraw(towerModel, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
}

void Tower::draw()
{
	Transform * t = (Transform*)getComponentById("transform");

	glPushMatrix();
		glTranslatef(t->position->x, t->position->y, t->position->z);
		glRotatef(t->rotation->x, 1, 0, 0);
		glRotatef(t->rotation->y, 0, 1, 0);
		glRotatef(t->rotation->z, 0, 0, 1);
		glScalef(t->scale->x, t->scale->y, t->scale->z);
		glTranslatef(0,0,3);
		glScalef(3, 3, 3);
		initModel();
		//drawTower();
	glPopMatrix();

	// ****** LIFEBAR ******
	LifeBar *lifebar = new LifeBar();
	Transform * lt = (Transform*)lifebar->getComponentById("transformLifeBar");
	//Transform * e1t_lifebar = (Transform*)e1->getComponentById("transformLifeBar");
	lt->position->x = t->position->x;
	lt->position->y = t->position->y;
	lt->position->z = (t->position->z + 6.2); // ... + val -> above the object

	// change scale->x between 0 and 1 scale->x when lifebar need to be reduced
	lt->scale->x = 0.2;
	lt->scale->y = 0.1;
	lt->scale->z = 0.1;

	glPushMatrix();
	lifebar->draw();
	glPopMatrix();
}

void Tower::drawTower()
{
	glBegin(GL_TRIANGLES);

	GLfloat color1[3] = { 0.3f, 0.3f, 0.3f };
	GLfloat color2[3] = { 0.5f, 0.5f, 0.5f };
	GLfloat color3[3] = { 0.7f, 0.7f, 0.7f };
	GLfloat color4[3] = { 0.9f, 0.9f, 0.9f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, color1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color1);
	glNormal3f(0.5, 0, 0); // FIXME
	glVertex3f(0, 0, 2);
	glVertex3f(0, -0.5, 1);
	glVertex3f(0.5, 0, 1);

	glMaterialfv(GL_FRONT, GL_AMBIENT, color2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color2);
	glNormal3f(0.5, 0, 0); // FIXME
	glVertex3f(0, 0, 2);
	glVertex3f(0.5, 0, 1);
	glVertex3f(0, 0.5, 1);

	glMaterialfv(GL_FRONT, GL_AMBIENT, color3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color3);
	glNormal3f(-0.5, 0, 0); // FIXME
	glVertex3f(0, 0, 2);
	glVertex3f(0, 0.5, 1);
	glVertex3f(-0.5, 0, 1);

	glMaterialfv(GL_FRONT, GL_AMBIENT, color4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color4);
	glNormal3f(-0.5, 0, 0); // FIXME
	glVertex3f(0, 0, 2);
	glVertex3f(-0.5, 0, 1);
	glVertex3f(0, -0.5, 1);

	glMaterialfv(GL_FRONT, GL_AMBIENT, color1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color1);
	glNormal3f(0.5, 0, 0); // FIXME
	glVertex3f(0, 0, 0);
	glVertex3f(0, -0.5, 1);
	glVertex3f(0.5, 0, 1);

	glMaterialfv(GL_FRONT, GL_AMBIENT, color2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color2);
	glNormal3f(0.5, 0, 0); // FIXME
	glVertex3f(0, 0, 0);
	glVertex3f(0.5, 0, 1);
	glVertex3f(0, 0.5, 1);

	glMaterialfv(GL_FRONT, GL_AMBIENT, color3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color3);
	glNormal3f(-0.5, 0, 0); // FIXME
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.5, 1);
	glVertex3f(-0.5, 0, 1);

	glMaterialfv(GL_FRONT, GL_AMBIENT, color4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color4);
	glNormal3f(-0.5, 0, 0); // FIXME
	glVertex3f(0, 0, 0);
	glVertex3f(-0.5, 0, 1);
	glVertex3f(0, -0.5, 1);

	glEnd();
}

