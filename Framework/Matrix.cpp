#include <iostream>
#include <iomanip>      // to get std::setprecision (for output precision)
#include "Matrix.h"
#include "Vector.h"

using namespace Vector;
using namespace MATRIX;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~    Matrix4 methods  ~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

/// Creates the identity matrix
void Matrix4::loadIdentity() {
	m[0] = 1.0f;   m[4] = 0.0f;   m[8] = 0.0f;   m[12] = 0.0f;
	m[1] = 0.0f;   m[5] = 1.0f;   m[9] = 0.0f;   m[13] = 0.0f;
	m[2] = 0.0f;   m[6] = 0.0f;   m[10] = 1.0f;   m[14] = 0.0f;
	m[3] = 0.0f;   m[7] = 0.0f;   m[11] = 0.0f;   m[15] = 1.0f;
}

/////////////////////////////////////////////////////////
////////////////   A Set of Constructors   /////////////
////////////////////////////////////////////////////////

/// Constructor with one float value or no value
Matrix4::Matrix4(const float d) {
	if (d == 1.0f) {
		loadIdentity();
	}
	else {
		for (int i = 0; i < 16; i++) {
			m[i] = d;
		}
	}
}

/// Constructor with 16 float values
Matrix4::Matrix4(
	float x0, float x1, float x2, float x3,
	float y0, float y1, float y2, float y3,
	float z0, float z1, float z2, float z3,
	float w0, float w1, float w2, float w3) {
	m[0] = x0;   m[4] = y0;   m[8] = z0; m[12] = w0;
	m[1] = x1;   m[5] = y1;   m[9] = z1; m[13] = w1;
	m[2] = x2;   m[6] = y2;   m[10] = z2; m[14] = w2;
	m[3] = x3;   m[7] = y3;   m[11] = z3; m[15] = w3;
}

////////////////////////////////////////////////////////
////////////////// Operator overloads //////////////////
////// (see note 1 at the bottom of the cpp file) //////
////////////////////////////////////////////////////////

/// An assignment operator   
Matrix4& Matrix4::operator = (const Matrix4& m_) {

	for (int i = 0; i < 16; i++) {
		this->m[i] = m_[i];
	}
	return *this;
}

/// Multiply two 4x4 matricies. 
const Matrix4 Matrix4::operator*(const Matrix4& n) const {
	Matrix4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result[i * 4 + j] = (m[0 * 4 + j] * n[i * 4 + 0]) +
				(m[1 * 4 + j] * n[i * 4 + 1]) +
				(m[2 * 4 + j] * n[i * 4 + 2]) +
				(m[3 * 4 + j] * n[i * 4 + 3]);
		}
	}
	return result;
}

/// Multiply this 4x4 matrix by a another 4x4 matrix and reassign it to itself
Matrix4& Matrix4::operator*=(const Matrix4& n) {
	*this = *this * n;
	return *this;
}

/// Multiply a Vec4 by this matrix and return the resulting vector
Vec4 Matrix4::operator* (const Vec4& v) const {
	float x = v.x * m[0] + v.y * m[4] + v.z * m[8] + v.w * m[12];
	float y = v.x * m[1] + v.y * m[5] + v.z * m[9] + v.w * m[13];
	float z = v.x * m[2] + v.y * m[6] + v.z * m[10] + v.w * m[14];
	float w = v.x * m[3] + v.y * m[7] + v.z * m[11] + v.w * m[15];
	return Vec4(x, y, z, w);
}

/// Multiply a 4x4 matrix by a Vec3
Vec3 Matrix4::operator* (const Vec3& v) const {
	float x = v.x * m[0] + v.y * m[4] + v.z * m[8] + 1.0f * m[12];
	float y = v.x * m[1] + v.y * m[5] + v.z * m[9] + 1.0f * m[13];
	float z = v.x * m[2] + v.y * m[6] + v.z * m[10] + 1.0f * m[14];
	float w = v.x * m[3] + v.y * m[7] + v.z * m[11] + 1.0f * m[15];
	return Vec3(x, y, z);
}


/// Using the 4x4 matrix as an array. We will need two overloads:
/// 1. This is for reading the 4x4 matrix as if where an array
const float Matrix4::operator [] (int index) const {
	return *(m + index);
}

/// 2. This is for writing to the 4x4 as if where an array.  
float& Matrix4::operator [] (int index) {
	return *(m + index);
}

/// Print out the values of this matrix in column form (right-hand rule)
void Matrix4::print() const {

	std::cout << std::setprecision(8);
	for (int i = 0; i < 16; i++) {
		std::cout << m[i] << " ";
	}

	std::cout << std::endl;

}

/////////////////////////////////////////////////////////
//////////////   Type conversion operators   ///////////
////////////////////////////////////////////////////////

/// These allows the conversion from type Matrix to const float * without issues
Matrix4::operator float* () {
	return static_cast<float*>(&m[0]);
}

Matrix4::operator const float* () const {
	return static_cast<const float*>(&m[0]);
}


/// These are a few esoteric funtions 
/// Defines functions to access rows and columns of a Matrix4.
Vec4 Matrix4::getColumn(int index) {
	return Vec4(m[4 * index + 0], m[4 * index + 1],
		m[4 * index + 2], m[4 * index + 3]);
}
Vec4 Matrix4::getRow(int index) {
	return Vec4(m[0 + index], m[4 + index], m[8 + index], m[12 + index]);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~    Matrix3 methods  ~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

/// Creates the identity matrix
void Matrix3::loadIdentity() {
	m[0] = 1.0f;   m[3] = 0.0f;   m[6] = 0.0f;
	m[1] = 0.0f;   m[4] = 1.0f;   m[7] = 0.0f;
	m[2] = 0.0f;   m[5] = 0.0f;   m[8] = 1.0f;

}

/////////////////////////////////////////////////////////
////////////////   A Set of Constructors   /////////////
////////////////////////////////////////////////////////

/// Constructor with one float value or no value 
Matrix3::Matrix3(const float d) {
	if (d == 1.0f) {
		loadIdentity();
	}
	else {
		for (int i = 0; i < 9; i++) {
			m[i] = d;
		}
	}
}

/// Constructor with 9 float values
Matrix3::Matrix3(float xx, float yx, float zx,
	float xy, float yy, float zy,
	float xz, float yz, float zz) {
	m[0] = xx;   m[3] = xy;   m[6] = xz;
	m[1] = yx;   m[4] = yy;   m[7] = yz;
	m[2] = zx;   m[5] = zy;   m[8] = zz;

}

////////////////////////////////////////////////////////
///// Operator overloads (see note 1 at the bottom /////
////////////////////////////////////////////////////////

/// An assignment operator   
Matrix3& Matrix3::operator = (const Matrix3& m_) {
	for (int i = 0; i < 9; i++) {
		this->m[i] = m_[i];
	}
	return *this;
}

/// Multiply two 3x3 matricies. 
const Matrix3 Matrix3::operator*(const Matrix3& n) const {
	Matrix3 result;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			result[i * 3 + j] = (m[0 * 3 + j] * n[i * 3 + 0]) +
				(m[1 * 3 + j] * n[i * 3 + 1]) +
				(m[2 * 3 + j] * n[i * 3 + 2]);
		}
	}
	return result;
}

/// Multiply this 3x3 matrix by a another 3x3 matrix and reassign it to itself
Matrix3& Matrix3::operator*=(const Matrix3& n) {
	*this = *this * n;
	return *this;
}

/// Using the Vec3 as an array. We will need two overloads:
/// 1. This is for reading the Vec3 as if where an array
const float Matrix3::operator [] (int index) const {
	return *(m + index);
}

/// 2. This is for writing to the Vec3 as if where an array.
float& Matrix3::operator [] (int index) {
	return *(m + index);
}

/// Extracts the inner 3x3 from a 4x4 matrix
/// using the assignment operator
Matrix3& Matrix3::operator = (const Matrix4& m_) {
	this->m[0] = m_[0]; this->m[1] = m_[1]; this->m[2] = m_[2];
	this->m[3] = m_[4]; this->m[4] = m_[5]; this->m[5] = m_[6];
	this->m[6] = m_[8]; this->m[7] = m_[9]; this->m[8] = m_[10];
	return *this;
}

/// Extracts the inner 3x3 from a 4x4 matrix
/// using the constructor
Matrix3::Matrix3(const Matrix4& m_) {
	this->m[0] = m_[0]; this->m[1] = m_[1]; this->m[2] = m_[2];
	this->m[3] = m_[4]; this->m[4] = m_[5]; this->m[5] = m_[6];
	this->m[6] = m_[8]; this->m[7] = m_[9]; this->m[8] = m_[10];
}

/// Print out the values of this matrix in column form (right-hand rule)
void Matrix3::print() const {
	std::cout << std::setprecision(8);
	for (int i = 0; i < 8; i++) {
		std::cout << m[i] << " ";
	}

	std::cout << std::endl;
}

/////////////////////////////////////////////////////////
//////////////   Type conversion operators   ///////////
////////////////////////////////////////////////////////

/// These allows the conversion from type Matrix to const float * without issues
Matrix3::operator float* () {
	return static_cast<float*>(&m[0]);
}

Matrix3::operator const float* () const {
	return static_cast<const float*>(&m[0]);
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
