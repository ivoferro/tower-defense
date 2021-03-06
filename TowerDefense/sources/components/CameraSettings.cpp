#include "../../headers/components/CameraSettings.h"

CameraSettings::CameraSettings()
{
	cameraType = CameraType::PERSPECTIVE;

	fieldOfView = 60;

	verticalInclination = 1;
	minVerticalInclination = 0.5;
	maxVerticalInclination = 10;

	distanceFromTarget = 10;
	minDistanceFromTarget = 5.0;
	maxDistanceFromTarget = 15.0;
}

CameraSettings::~CameraSettings()
{
}
