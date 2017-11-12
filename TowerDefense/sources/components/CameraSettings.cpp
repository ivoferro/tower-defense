#include "../../headers/components/CameraSettings.h"

CameraSettings::CameraSettings()
{
	cameraType = CameraType::PERSPECTIVE;

	fieldOfView = 60;

	distanceFromTarget = 10;
	minDistanceFromTarget = 5.0;
	maxDistanceFromTarget = 15.0;
}

CameraSettings::~CameraSettings()
{
}
