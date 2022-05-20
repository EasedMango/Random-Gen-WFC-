#pragma once
#include "Vector.h"

using namespace Vector;

/// <summary>
///  A collection of 4x4 and 3x3 matrix classes definitions
/// </summary>
namespace  MATRIX {
	/// These are the default vectors of the eye (camera) according to OpenGL and the right hand rule
	///								+Y   -Z
	///	                             |  /
	///   origin(0.0f,0.0f,0.0f);    | /
	///   up(0.0f,1.0f,0.0f);        |/_____+X
	///   forward(0.0f,0.0f,-1.0f);  /
	///                             /
	///                           +Z
	///
	class Matrix4 {

		/// Let's just make sure that all is clear about how this matrix is layed out. 

		/// How a matrix is really layed out is pretty much abitrary but we need to 
		/// agree and the world has agreed (except for Microsoft) on the right-hand rule. 
		/// First, the 4x4 matrix is really just an array of 16 numbers.  
		/// We need to think of the array as a matrix in the following way
		/// 4x4 matrix - COLUMN MAJOR - The OpenGL, science, physics, mathematics and 
		/// engineering way. 
		///	0  4  8  12        [0][0]  [1][0]  [2][0]  [3][0]   
		///	1  5  9  13  (or)  [0][1]  [1][1]  [2][1]  [3][1]
		///	2  6  10 14        [0][2]  [1][2]  [2][2]  [3][2]
		///	3  7  11 15        [0][3]  [1][3]  [2][3]  [3][3]

	private:
		float  m[16];

	public:

		/// Creates the identity matrix
		void loadIdentity();

		/////////////////////////////////////////////////////////
		////////////////   A Set of Constructors   /////////////
		////////////////////////////////////////////////////////

		/// Constructor with one float value or no value
		explicit Matrix4(const float d = 1.0f);

		/// Constructor with 16 float values
		explicit Matrix4(
			float x0, float x1, float x2, float x3,
			float y0, float y1, float y2, float y3,
			float z0, float z1, float z2, float z3,
			float w0, float w1, float w2, float w3);

		////////////////////////////////////////////////////////
		///// Operator overloads (see note 1 at the bottom /////
		////////////////////////////////////////////////////////

		/// An assignment operator   
		Matrix4& operator = (const Matrix4& m_);

		/// Multiply two 4x4 matricies. 
		const Matrix4 operator*(const Matrix4& n) const;


		/// Multiply this 4x4 matrix by a another 4x4 matrix and reassign it 
		/// to itself
		Matrix4& operator*=(const Matrix4& n);

		/// Multiply a Vec4 by this matrix and return the resulting vector
		Vec4 operator* (const Vec4& v) const;

		/// Multiply a 4x4 matrix by a Vec3
		Vec3 operator* (const Vec3& v) const;


		/// Using the 4x4 matrix as an array. We will need two overloads:
		/// 1. This is for reading the 4x4 matrix as if where an array
		const float operator [] (int index) const;

		/// 2. This is for writing to the 4x4 as if where an array.  
		float& operator [] (int index);

		/// Print out the values of this matrix in column form (right-hand rule)
		void print() const;

		/////////////////////////////////////////////////////////
		//////////////   Type conversion operators   ///////////
		////////////////////////////////////////////////////////

		/// These allows the conversion from type Matrix to const 
		/// float * without issues
		operator float* ();

		operator const float* () const;

		/// These are a few esoteric funtions 
		/// Defines functions to access rows and columns of a Matrix4.
		Vec4 getColumn(int index);

		Vec4 getRow(int index);
	};


	class Matrix3 {
		/// 3x3 matrix - COLUMN MAJOR 
		///	0	3	6			
		///	1	4	7	 
		///	2	5	8			
		float  m[9];

	public:

		/// Creates the identity matrix
		void loadIdentity();

		/////////////////////////////////////////////////////////
		////////////////   A Set of Constructors   /////////////
		////////////////////////////////////////////////////////

		/// Constructor with one float value or no value 
		explicit Matrix3(const float d = 1.0f);

		/// Constructor with 9 float values
		Matrix3(float xx, float yx, float zx,
			float xy, float yy, float zy,
			float xz, float yz, float zz);

		////////////////////////////////////////////////////////
		////////////////// Operator overloads //////////////////
		////// (see note 1 at the bottom of the cpp file) //////
		////////////////////////////////////////////////////////

		/// An assignment operator   
		Matrix3& operator = (const Matrix3& m_);

		/// Multiply two 3x3 matricies. 
		const Matrix3 operator*(const Matrix3& n) const;

		/// Multiply this 3x3 matrix by a another 3x3 matrix and reassign it
		/// to itself
		Matrix3& operator*=(const Matrix3& n);

		/// Using the Vec3 as an array. We will need two overloads:
		/// 1. This is for reading the Vec3 as if where an array
		const float operator [] (int index) const;

		/// 2. This is for writing to the Vec3 as if where an array.
		float& operator [] (int index);


		/// Extracts the inner 3x3 from a 4x4 matrix
		/// using the assignment operator
		Matrix3& operator = (const Matrix4& m_);

		/// Extracts the inner 3x3 from a 4x4 matrix
		/// using the constructor
		Matrix3(const Matrix4& m_);

		/// Print out the values of this matrix in column form (right-hand rule)
		void print() const;

		/////////////////////////////////////////////////////////
		//////////////   Type conversion operators   ///////////
		////////////////////////////////////////////////////////

		/// These allows the conversion from type Matrix to const 
		// float * without issues
		operator float* ();

		operator const float* () const;

	};

}


