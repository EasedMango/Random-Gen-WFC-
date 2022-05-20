#pragma once
//#include <cmath>
#include <iostream>
#include <iomanip>      // to get std::setprecision (for output precision)
#include <string>		// Used for passing exceptions 
#include "Vector.h"

using namespace Vector;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~    Vec2 methods   ~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

/// Constructor
Vec2::Vec2(float s) {
	x = s; y = s;
}

/// Destructor. Delete this object. 
Vec2::~Vec2() {

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~    Vec3 methods   ~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void Vec3::set(float x_, float y_, float z_) {
	x = x_; y = y_; z = z_;
}

/////////////////////////////////////////////////////////
////////////////   A Set of Constructors   /////////////
////////////////////////////////////////////////////////

/// Constructor with one float value or no value
Vec3::Vec3(float s) {
	set(s, s, s);
}

/// Constructor with 3 float values
Vec3::Vec3(float x, float y, float z) {
	set(x, y, z);
}

/// Constructor with one Vec3 value
Vec3::Vec3(const Vec3& v) {
	set(v.x, v.y, v.z);
}


////////////////////////////////////////////////////////
////////////////// Operator overloads //////////////////
////// (see note 1 at the bottom of the cpp file) //////
////////////////////////////////////////////////////////

/// An assignment operator   
Vec3& Vec3::operator = (const Vec3& v) {
	set(v.x, v.y, v.z);
	return *this;
}

/// Add two Vec3s
const Vec3 Vec3::operator + (const Vec3& v) const {
	return Vec3(x + v.x, y + v.y, z + v.z);
}

/// Add a Vec3 to itself and reassign it to itself
Vec3& Vec3::operator += (const Vec3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

/// Take the negative of a Vec3
const Vec3 Vec3::operator - () const {
	return Vec3(-x, -y, -z);
}

/// Subtract two Vec3s
const Vec3 Vec3::operator - (const Vec3& v) const {
	return Vec3(x - v.x, y - v.y, z - v.z);
}

/// Subtract a Vec3 from itself and reassign it to itself
Vec3& Vec3::operator -= (const Vec3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

/// Multiply a Vec3 by a scalar
const Vec3 Vec3::operator * (const float s) const {
	return Vec3(s * x, s * y, s * z);
}

/// Multiply this Vec3 by a scalar and reassign it to itself
Vec3& Vec3::operator *= (const float s) {
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

/// Multiply a scaler by a Vec3. It's the scalar first then the Vec3
/// Overloaded and a friend, ouch! It's the only way to make it work with 
/// a scalar first. Friends are tricky, look them up. 
Vec3 Vector::operator * (const float s, const Vec3& v) {
	return v * s;
}

/// Divide by a scalar. We must watch for divide by zero issues
const Vec3 Vec3::operator / (const float s) const {
	// If in debug mode let's worry about divide by zero or nearly zero!!! 
#ifdef _DEBUG  
	if (fabs(s) < VERY_SMALL) {
		std::string errorMsg("Divide by nearly zero! ");
		throw errorMsg;
	}
#endif
	float r = 1.0f / s;
	return *this * r;
}

/// Divide this Vec3 by a scalar and reassign it to itself.
/// We must Watch for divide by zero issues
Vec3& Vec3::operator /= (const float s) {
	// If in debug mode let's worry about divide by zero or nearly zero!!! 
#ifdef _DEBUG  
	if (std::fabs(s) < VERY_SMALL) {
		std::string errorMsg("Divide by nearly zero! ");
		throw errorMsg;
	}
#endif // DEBUG
	float r = 1.0f / s;
	*this *= r;
	return *this;
}

/// Using the Vec3 as an array. We will need two overloads:
/// 1. This is for reading the Vec3 as if where an array
const float Vec3::operator [] (int index) const {
	return *(&x + index);
}

/// 2. This is for writing to the Vec3 as if where an array.  
float& Vec3::operator [] (int index) {
	return *(&x + index);
	/// See note 2 at the end of this file about lvalues and rvalues
}

/// Print out the values of this vector
void Vec3::print() {
	std::cout << std::setprecision(8) << "x: " << x;
	std::cout << ", y: " << y << ", z: " << z << std::endl;
}

/////////////////////////////////////////////////////////
//////////////   Type conversion operators   ///////////
////////////////////////////////////////////////////////

/// These allows the conversion from type Vec3 to const float * without issues
Vec3::operator const float* () const {
	return static_cast<const float*>(&x);
}

Vec3::operator float* () {
	return static_cast<float*>(&x);
}

/// Destructor. Delete this object. 
Vec3::~Vec3() {

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~    Vec4 methods   ~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


/////////////////////////////////////////////////////////
////////////////   A Set of Constructors   /////////////
////////////////////////////////////////////////////////

/// Constructor with 1 float value
Vec4::Vec4(float s) {
	x = s; y = s; z = s; w = s;
}

/// Constructor with 4 float values
Vec4::Vec4(float _x, float _y, float _z, float _w) {
	x = _x; y = _y; z = _z; w = _w;
}

/// Constructor with one Vec4 value
Vec4::Vec4(const Vec4& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}

/// Constructor with one Vec3 value
Vec4::Vec4(const Vec3& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	w = 1.0f;
}

////////////////////////////////////////////////////////
///// Operator overloads (see note 1 at the bottom /////
////////////////////////////////////////////////////////

/// An assignment operator   
Vec4& Vec4::operator = (const Vec4& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}

/// Add two Vec4s
Vec4 Vec4::operator + (const Vec4& v) const {
	return Vec4(x + v.x, y + v.y, z + v.z, w + v.w);
}

/// Add a Vec4 to itself and reassign it to itself
Vec4& Vec4::operator += (const Vec4& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

/// Take the negative of a Vec4 
Vec4 Vec4::operator - () const {
	return Vec4(-x, -y, -z, -w);
}

/// Subtract two Vec4s 
Vec4 Vec4::operator - (const Vec4& v) const {
	return Vec4(x - v.x, y - v.y, z - v.z, v.w - w);
}

/// Subtract a Vec4 from itself and reassign it to itself 
Vec4& Vec4::operator -= (const Vec4& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

/// Multiply a Vec4 by a scalar
Vec4 Vec4::operator * (const float s) const {
	return Vec4(s * x, s * y, s * z, s * w);
}

/// Multiply this Vec4 by a scalar and reassign it to itself
Vec4& Vec4::operator *= (const float s) {
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this;
}

/// Multiply a scaler by a Vec4. It's the scalar first then the Vec4
/// Overloaded and a friend, ouch! It's the only way to make it work 
/// with a scalar first. Friends are tricky, look them up. 
Vec4 Vector::operator * (const float s, const Vec4& v) {
	return v * s;
}

/// Divide by a scalar - Watch for divide by zero issues
Vec4 Vec4::operator / (const float s) const {
	// If in debug mode let's worry about divide by zero or nearly zero!!! 
#ifdef DEBUG  
	if (std::fabs(s) < VERY_SMALL) {
		std::string errorMsg("Divide by nearly zero! ");
		throw errorMsg;
	}
#endif

	float r = 1.0f / s;
	return *this * r;
}

/// Divide this Vec4 by a scalar and reassign it to itself.
/// We must Watch for divide by zero issues
Vec4& Vec4::operator /= (const float s) {
	/// If in debug mode let's worry about divide by zero or nearly zero!!! 
#ifdef _DEBUG  
	if (std::fabs(s) < VERY_SMALL) {
		std::string errorMsg("Divide by nearly zero! ");
		throw errorMsg;
	}
#endif // DEBUG

	float r = 1.0f / s;
	*this *= r;
	return *this;
}

/// Using the Vec4 as an array. We will need two overloads:
/// 1. This is for reading the Vec4 as if where an array
float& Vec4::operator [] (int index) {
	return *(&x + index);
}

/// 2. This is for writing to the Vec4 as if where an array.  
const float Vec4::operator [] (int i) const {
	return *(&x + i);
}

// Print out the values of this vector
void Vec4::print() {
	std::cout << std::setprecision(8) << "x: " << x;
	std::cout << ", y: " << y << ", z: " << z;
	std::cout << ", w: " << w << std::endl;
}

/////////////////////////////////////////////////////////
//////////////   Type conversion operators   ///////////
////////////////////////////////////////////////////////

/// These allows the conversion from type Vec4 to const float * without issues
Vec4::operator const float* () const {
	return static_cast<const float*>(&x);
}

Vec4::operator float* () {
	return static_cast<float*>(&x);
}

/// Destructor. Delete this object. 
Vec4::~Vec4() {

}



/*** Note 1.
I know, I hate operator overloading as a general rule but a few make sense!! Just be careful and
consistent. In the following code, I will overload many operators. I don't believe in
overloading when the operator is less than obvious.
For example, in this class, the relational operators (== != < > <= >=) might mean "in relation
to their magnitude or direction" I'm just not sure. Just write a function to do that and don't make
me guess what the operator might mean. Use the idea of "Least Astonishment" don't surprise me,
or shock me or anything else that will piss me or others off-SSF
***/

/*** Note 2.
In straight C programming, lvalues and rvalues literially means left and right assignments.  For example,
int x = 5; x is the lvalue and 5 is the rvalue. Easy. In C++ it get a bit more tricky. The modern idea is
rvalues are temporary vaules residing in the registers of the CPU. lvalues are actual memory locations.
In the code:
	float& operator [] ( int index ) {
		return *(&x + index);
	}
To read this precicely, &x is the address of the x variable (the first in the list of x,y,z) add to that
address the index as if it were an array. Then *(&x + index) dereferences that address back into the
object, the float& reference returns it as an address and thus an lvalue.
***/

/*** Note 3.
The issue here is that I need to use functions in Vector from VMath which require Vector but VMath
also requires Vector - this is a classic circular dependency problem or sometimes known as mutual recursion.
To solve this it requires a forward declaration.  A "forward declaration" is the declaration of a class for which
the you have not yet given a complete definition of (whateverClass.h). To do this all you need is the statement:
"class VMath;"  This warns the compiler that I will be using VMath in Vector; HOWEVER, in this case, it won't work because
I'm using the vector.h as a totally inlined set of functions - sometimes you're just screwed
***/