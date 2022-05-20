#pragma once
#include <cmath>
#include "Vector.h"

using namespace Vector;

/// <summary>
/// A class devoted to vector related Math
/// </summary>
namespace MATH {

	class VMath {

	public:
		/// Calculate the dot product between two Vec3s 
		static float dot(const Vec3& a, const Vec3& b);

		/// Calulate the cross product between two Vec3s 
		static const Vec3 cross(const Vec3& a, const Vec3& b);

		/// Calulate the magnitude between two Vec3s 
		static float mag(const Vec3& a);

		/// Calulate the Angle-Axis rotation between two Vec3s and with an angle 
		static Vec3 rotate(const Vec3& n, float theta, const Vec3& v);

		/////////////////////////////////////////////////////////
		/////////////// These are more complex  ////////////////
		////////////////////////////////////////////////////////

		/// Return a normalized Vec3
		static Vec3 normalize(const Vec3& a);

		/// Reflect off a normal  
		static Vec3 reflect(const Vec3& v, const Vec3& n);

		/// Get the distance between two Vec3s 
		static float distance(const Vec3& a, const Vec3& b);

		/// This is a basic Linear Interpolation function.  It takes a Vec3 v1 and 
		/// moves it to Vec3 v2 in a linear fashion based on the value of t which 
		/// goes from 0.0 - 1.0.  This is a simple example of a parametric equation. 
		/// The parameter t can mean time but does not need be
		static Vec3 lerp(const Vec3& v1, const Vec3& v2, float t);
	};

}

