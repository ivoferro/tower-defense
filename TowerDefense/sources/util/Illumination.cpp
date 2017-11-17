#include "../../headers/util/Illumination.h"

const GLfloat Illumination::NO_MATERIAL[] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat Illumination::MATERIAL_AMBIENT_COLOR[] = { 0.8, 0.8, 0.2, 1.0 };
const GLfloat Illumination::MATERIAL_SPECULAR[] = { 1.0, 1.0, 1.0, 1.0 };

const GLfloat Illumination::NO_SHININESS[] = { 0.0 };
const GLfloat Illumination::LOW_SHININESS[] = { 5.0 };
const GLfloat Illumination::HIGH_SHININESS[] = { 100.0 };

const GLfloat Illumination::MATERIAL_EMISSION[] = { 0.3, 0.2, 0.2, 0.0 };