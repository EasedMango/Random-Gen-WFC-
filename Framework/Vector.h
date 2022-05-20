#pragma once
#include <iostream>
#include <iomanip>      // to get std::setprecision (for output precision)

/// <summary>
/// A collection of 2D, 3D, and 4D vector classes definitions
/// </summary>
namespace  Vector {

	/// The following 3 values are called  Macros. A Macro is a constant which
	/// is similar to a global variable but cannot be modified.
	/// These macros are used in normalizing vectors. Dividing by zero is a well 
	/// known problem but dividing by nearly zero is also a problem. 1.0x10-7 
	/// is very small in "float" percision. 

	#ifndef VERY_SMALL
	#define VERY_SMALL 1.0e-7f
	#endif

	#ifndef M_PI
	#define M_PI 3.14159265358979323846f
	#endif

	#ifndef DEGREES_TO_RADIANS
	#define DEGREES_TO_RADIANS (M_PI / 180.0f)
	#endif	

	struct Vec2 {
		float  x, y;

		/// Constructor
		explicit Vec2(float s = float(0.0));

		/// Destructor. Delete this object. 
		~Vec2();
	};


	struct Vec3 {
		float  x, y, z;	///  Structures are default public

		/// Setting the values of the attributes
		void set(float x_, float y_, float z_);

		/////////////////////////////////////////////////////////
		////////////////   A Set of Constructors   /////////////
		////////////////////////////////////////////////////////

		/// Constructor with one float value or no value
		explicit Vec3(float s = float(0.0));

		/// Constructor with 3 float values
		Vec3(float x, float y, float z);

		/// Constructor with one Vec3 value
		Vec3(const Vec3& v);

		////////////////////////////////////////////////////////
		///// Operator overloads (see note 1 at the bottom) ////
		////////////////////////////////////////////////////////

		/// An assignment operator   
		Vec3& operator = (const Vec3& v);

		/// Add two Vec3s
		const Vec3 operator + (const Vec3& v) const;

		/// Add a Vec3 to itself and reassign it to itself
		Vec3& operator += (const Vec3& v);

		/// Take the negative of a Vec3
		const Vec3 operator - () const;

		/// Subtract two Vec3s
		const Vec3 operator - (const Vec3& v) const;

		/// Subtract a Vec3 from itself and reassign it to itself
		Vec3& operator -= (const Vec3& v);

		/// Multiply a Vec3 by a scalar
		const Vec3  operator * (const float s) const;

		/// Multiply this Vec3 by a scalar and reassign it to itself
		Vec3& operator *= (const float s);

		/// Multiply a scaler by a Vec3. It's the scalar first then the Vec3
		/// Overloaded and a friend, ouch! It's the only way to make it work with 
		/// a scalar first. Friends are tricky, look them up. 
		friend Vec3 operator * (const float s, const Vec3& v);

		/// Divide by a scalar. We must watch for divide by zero issues
		const Vec3 operator / (const float s) const;

		/// Divide this Vec3 by a scalar and reassign it to itself.
		/// We must Watch for divide by zero issues
		Vec3& operator /= (const float s);

		/// Using the Vec3 as an array. We will need two overloads:
		/// 1. This is for reading the Vec3 as if where an array
		const float operator [] (int index) const;

		/// 2. This is for writing to the Vec3 as if where an array.  
		float& operator [] (int index);

		/// Print out the values of this vector
		void print();

		/////////////////////////////////////////////////////////
		//////////////   Type conversion operators   ///////////
		////////////////////////////////////////////////////////

		/// These allows the conversion from type Vec3 to const float * without issues
		operator const float* () const;

		operator float* ();

		/// Destructor. Delete this object. 
		~Vec3();
	};


	/// Vec4 definition
	/// I am intentionally creating a Vec4 from a Vec3 so I can pass a Vec4 into 
	/// a Subroutine that wants a Vec3. In many cases this will be mathamatically 
	/// OK, just be careful Vec4's are not quaterinians
	struct Vec4 : public Vec3 {
		///float  x;	///
		///float  y;	///  
		///float  z;	/// From Vec3
		float  w;

		/////////////////////////////////////////////////////////
		////////////////   A Set of Constructors   /////////////
		////////////////////////////////////////////////////////

		/// Constructor with 1 float value
		explicit Vec4(float s = float(0.0));

		/// Constructor with 4 float values
		Vec4(float _x, float _y, float _z, float _w);

		/// Constructor with one Vec4 value
		Vec4(const Vec4& v);

		/// Constructor with one Vec3 value
		Vec4(const Vec3& v);

		////////////////////////////////////////////////////////
		////////////////// Operator overloads //////////////////
		////// (see note 1 at the bottom of the cpp file) //////
		////////////////////////////////////////////////////////

		/// An assignment operator   
		Vec4& operator = (const Vec4& v);

		/// Add two Vec4s
		Vec4 operator + (const Vec4& v) const;

		/// Add a Vec4 to itself and reassign it to itself
		Vec4& operator += (const Vec4& v);

		/// Take the negative of a Vec4 
		Vec4 operator - () const;

		/// Subtract two Vec4s 
		Vec4 operator - (const Vec4& v) const;

		/// Subtract a Vec4 from itself and reassign it to itself 
		Vec4& operator -= (const Vec4& v);

		/// Multiply a Vec4 by a scalar
		Vec4 operator * (const float s) const;

		/// Multiply a Vec4 by a scalar and reassign it to itself
		Vec4& operator *= (const float s);

		/// Multiply a scaler by a Vec4. It's the scalar first then the Vec4
		/// Overloaded and a friend, ouch! It's the only way to make it work
		/// with a scalar first. Friends are tricky, look them up.
		friend Vec4 operator * (const float s, const Vec4& v);

		/// Divide by a scalar - Watch for divide by zero issues
		Vec4 operator / (const float s) const;

		/// Divide this Vec4 by a scalar and reassign it to itself.
		/// We must Watch for divide by zero issues
		Vec4& operator /= (const float s);

		/// Using the Vec4 as an array. We will need two overloads:
		/// 1. This is for reading the Vec4 as if where an array
		float& operator [] (int index);

		/// 2. This is for writing to the Vec4 as if where an array.  
		const float operator [] (int i) const;

		// Print out the values of this vector
		void print();

		/////////////////////////////////////////////////////////
		//////////////   Type conversion operators   ///////////
		////////////////////////////////////////////////////////

		/// These allows the conversion from type Vec4 to const float * without issues
		operator const float* () const;

		operator float* ();

		/// Destructor. Delete this object. 
		~Vec4();

	};
}

