#include "../../headers/util/Illumination.h"

const GLfloat Illumination::NO_MATERIAL[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat Illumination::MATERIAL_AMBIENT_COLOR[] = { 0.8f, 0.8f, 0.2f, 1.0f };
const GLfloat Illumination::MATERIAL_SPECULAR[] = { 1.0f, 1.0f, 1.0f, 1.0f };

const GLfloat Illumination::NO_SHININESS[] = { 0.0f };
const GLfloat Illumination::LOW_SHININESS[] = { 5.0f };
const GLfloat Illumination::HIGH_SHININESS[] = { 100.0f };

const GLfloat Illumination::MATERIAL_EMISSION[] = { 0.3f, 0.2f, 0.2f, 0.0f };