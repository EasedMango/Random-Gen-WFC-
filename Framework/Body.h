#pragma once
#include "Vector.h"
using namespace Vector;

class Body {
	// Private attributes
	Vec3 pos; 
	Vec3 vel;
	Vec3 accel;
	float mass;
	const char* textureFile;

public:

	/// <summary>
	/// Constructor. Assign attributes' values. 
	/// If no parameter is given, a default value is set.
	/// </summary>
	/// <param name="pos_">position</param>
	/// <param name="vel_">velocity</param>
	/// <param name="accel_">acceleration</param>
	/// <param name="mass_">mass</param>
	/// <param name="textureFile_">object texture file</param>
	Body(Vec3 pos_ = Vec3(), Vec3 vel_ = Vec3(), Vec3 accel_ = Vec3(), 
		float mass_ = 0.0f, const char* textureFile_ = "");

	/// <summary>
	/// Update the location of this body based on the given detla time
	/// </summary>
	/// <param name="deltaTime">the difference in time</param>
	void Update(float deltaTime);

	/// <returns>The current position of this body</returns>
	Vec3 getPos();

	/// <returns>The texture of this body</returns>
	const char* GetTextureFile();

	/// <summary>
	/// Destructor. Delete all pointer attributes in this class 
	/// then delete this object.
	/// </summary>
	~Body();

};
