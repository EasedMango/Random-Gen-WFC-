#include <string>
#include "VectorMath.h"

using namespace MATH;

/// Calculate the dot product between two Vec3s 
float VMath::dot(const Vec3& a, const Vec3& b) {
	return(a.x * b.x + a.y * b.y + a.z * b.z);
}

/// Calulate the cross product between two Vec3s 
const Vec3 VMath::cross(const Vec3& a, const Vec3& b) {
	return Vec3(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
}

/// Calulate the magnitude between two Vec3s 
float VMath::mag(const Vec3& a) {
	return(sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

/// Calulate the Angle-Axis rotation between two Vec3s and with an angle 
Vec3 VMath::rotate(const Vec3& n, float theta, const Vec3& v) {
	return v * cos(theta) + VMath::dot(v, n) * 
		n * (1.0f - cos(theta)) + VMath::cross(n, v) * sin(theta);
}

/////////////////////////////////////////////////////////
//// These are more complex so no need to them ///
////////////////////////////////////////////////////////

/// Return a normalized Vec3
Vec3 VMath::normalize(const Vec3& a) {
	float magnitude;
	Vec3 result;
	magnitude = float(sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
	// If in debug mode let's worry about divide by zero or nearly zero!!! 
#ifdef _DEBUG  
	if (magnitude < VERY_SMALL) {
		std::string errorMsg("Divide by nearly zero! ");
		throw errorMsg;
	}
#endif

	result.x = a.x / magnitude;
	result.y = a.y / magnitude;
	result.z = a.z / magnitude;
	return result;
}

/// Reflect off a normal  
Vec3 VMath::reflect(const Vec3& v, const Vec3& n) {
	Vec3 result;
	float scalar = 2.0f * dot(v, n);
	Vec3 temp = n * scalar;
	result = temp - v;
	return result;
}

/// Get the distance between two Vec3s 
float VMath::distance(const Vec3& a, const Vec3& b) {
	Vec3 r = a - b;
	return(mag(r));
}

/// This is a basic Linear Interpolation function.  It takes a Vec3 v1 and 
/// moves it to Vec3 v2 in a linear fashion based on the value of t which 
/// goes from 0.0 - 1.0.  This is a simple example of a parametric equation. 
/// The parameter t can mean time but does not need be
Vec3 VMath::lerp(const Vec3& v1, const Vec3& v2, float t) {
	return (v1 + t * (v2 - v1));
}

