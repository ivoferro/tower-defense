#pragma once

// deprecated, now GameObject has a draw() method
// which does nothing by default.
class Drawable
{

public:
	virtual void draw() = 0;

};