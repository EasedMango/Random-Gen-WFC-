#include "Body.h"


Body::Body(Vec3 pos_, Vec3 vel_, Vec3 accel_,
	float mass_, const char* textureFile_) {
	pos = pos_; 
	vel = vel_; 
	accel = accel_;
	mass = mass_; 
	textureFile = textureFile_;
}

Body::~Body() {
}

void Body::Update(float deltaTime) {
}

Vec3 Body::getPos() {
	return pos;
}

const char* Body::GetTextureFile() {
	return textureFile;
}

