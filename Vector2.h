#ifndef __ARK_VECTOR2_H__
#define __ARK_VECTOR2_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 14.04.2004
Last Revised:	14.04.2004

Implementation File: None

Notes:

*/

/*
2D Vector class
*/

#include "Arkanoid.h"
#include "Math.h"

namespace ARK{
	//=============================================
	//Vector2 class
	//=============================================
	class Vector2{
	public:

	/*
	This one is a nice trick to access variables;
	either by vector.x vector.y or pointer to
	float v[2] structure
	*/

		union{
			struct{
				float x;
				float y;
			};
			float v[2];
		};

	public:

	//constructors

		inline Vector2(){}		//empty constructor
		inline Vector2(const float xx,const float yy) : x(xx),y(yy){}	//standart one (from component)
		inline Vector2(const float *arr)	//from array of floats
		{
			x=arr[0];
			y=arr[1];
		}

		inline Vector2(const Vector2 & vec) : x(vec.x),y(vec.y){}	//create from vector

		//basic math operations
		inline Vector2 operator+() const;	//positive
		inline Vector2 operator-() const;	//negative

		inline Vector2 &operator=(const Vector2 & vec);	//equals
		inline Vector2 &operator+=(const Vector2 & vec);//add
		inline Vector2 &operator-=(const Vector2 & vec);//substract

		inline Vector2 & operator*=(float scalar);	//scale by float
		inline Vector2 & operator/=(float scalar);	//scale by 1/float

		inline friend const Vector2 operator+(const Vector2 &v1, const Vector2 v2);	//add
		inline friend const Vector2 operator-(const Vector2 &v1, const Vector2 v2);	//substract
		inline friend const Vector2 operator*(const Vector2 &vec, const float scalar);	//multiply by scalar
		inline friend const Vector2 operator/(const Vector2 &vec, const float scalar);	//divide by scalar

//		inline friend const Vector2 operator^(const Vector2 &v1, const Vector2 &v2);	//cross product
		inline friend const float operator%(const Vector2 &v1, const Vector2 &v2);	//dot product

	//	inline friend const Vector2 operator|(Vector2 &vec, const float lenght);	//sets lenght
	//	inline Vector2& operator|=(const float lenght);

		//basic comparision oprators
		inline friend bool operator==(const Vector2 &v1, const Vector2 &v2);	//is vector equal?
		inline friend bool operator!=(const Vector2 &v1, const Vector2 &v2);	//is vector not equal?
		inline friend bool operator>(const Vector2 &v1, const Vector2 &v2);		//is vector greater?
		inline friend bool operator<(const Vector2 &v1, const Vector2 &v2);		//is vector lesser?

		inline const bool IsZero() const;	//is vector zero?

		//various

		inline void Set(float xx, float yy);	//set by components
		inline void Set(float *components);	//set by pointer to components
		inline void Set(const Vector2 &vec);	//set by vector

		inline void Abs();	//set components to absolute

		inline void Zero();		//set all components to zero

		inline void NormalizeFast();	//reduce to unit-lenght
		inline void Normalize();	//reduce to unit-lenght (exact)

		//	inline void Reflect(const Vector2 &normal);	//reflects vector

		inline float Lenght() const;	//returns lenght of vector
		inline float LenghtSqr() const;

		//more various

		inline std::string ToString();	//string representation of vector

	};	//end of class CVector2

	////////////////////////////////////////////////////
	//operator + - return positive
	////////////////////////////////////////////////////
	inline Vector2 Vector2::operator+() const
	{
		return *this;
	}

	////////////////////////////////////////////////////
	//operator - - return negative
	////////////////////////////////////////////////////
	inline Vector2 Vector2::operator-() const
	{
		return Vector2(-x,-y);
	}

	////////////////////////////////////////////////////
	//operator =
	////////////////////////////////////////////////////
	inline Vector2 & Vector2::operator=(const Vector2 &vec)
	{
		x=vec.x;
		y=vec.y;
		return *this;
	}

	////////////////////////////////////////////////////
	//operator +=
	////////////////////////////////////////////////////
	inline Vector2 & Vector2::operator+=(const Vector2 &vec)
	{
		x+=vec.x;
		y+=vec.y;
		return *this;
	}

	////////////////////////////////////////////////////
	//operator -=
	////////////////////////////////////////////////////
	inline Vector2 & Vector2::operator-=(const Vector2 &vec)
	{
		x-=vec.x;
		y-=vec.y;
		return *this;
	}

	////////////////////////////////////////////////////
	//operator *= - scale by scalar
	////////////////////////////////////////////////////
	inline Vector2 & Vector2::operator*=(const float scalar)
	{
		x*=scalar;
		y*=scalar;
		return *this;
	}	

	////////////////////////////////////////////////////
	//operator /= - scale by 1/scalar
	////////////////////////////////////////////////////
	inline Vector2 & Vector2::operator/=(const float scalar)
	{
		float sc = 1.0f/scalar;

		x*=sc;
		y*=sc;
		return *this;
	}

	////////////////////////////////////////////////////
	//operator +
	////////////////////////////////////////////////////
	inline const Vector2 operator+(const Vector2 &v1, const Vector2 v2)
	{
		return Vector2(v1.x + v2.x , v1.y + v2.y);
	}

	////////////////////////////////////////////////////
	//operator -
	////////////////////////////////////////////////////
	inline const Vector2 operator-(const Vector2 &v1, const Vector2 v2)
	{
		return Vector2(v1.x - v2.x , v1.y - v2.y);
	}

	////////////////////////////////////////////////////
	//operator *
	////////////////////////////////////////////////////
	inline const Vector2 operator*(const Vector2 &vec, const float scalar)
	{
		return Vector2(vec.x * scalar , vec.y * scalar);
	}

	////////////////////////////////////////////////////
	//operator /
	////////////////////////////////////////////////////
	inline const Vector2 operator/(const Vector2 &vec, const float scalar)
	{
		float sc = 1.0f/scalar;
		return Vector2(vec.x * sc , vec.y * sc);
	}

	////////////////////////////////////////////////////
	//operator ^ - cross product
	////////////////////////////////////////////////////
//	inline const Vector2 operator^(const Vector2 &v1,const Vector2 &v2)
//	{
//		Vector2 tmp;
//		tmp.x =	v1.y * v2.z - v1.z * v2.y;
//		tmp.y =	v1.z * v2.x - v1.x * v2.z;
//		tmp.z =	v1.x * v2.y - v1.y * v2.x;

//		return tmp;
//	}

	////////////////////////////////////////////////////
	//operator % - dot product
	////////////////////////////////////////////////////
	inline const float operator%(const Vector2 &v1, const Vector2 &v2)
	{
		return (v1.x * v2.x)+(v1.y * v2.y);
	}
	/*
	////////////////////////////////////////////////////
	//operator | - changes lenght of the vector
	////////////////////////////////////////////////////
	inline friend const Vector2 operator|(const Vector2 & vec, const float lenght){
		return
	*/
	
	////////////////////////////////////////////////////
	//operator==
	////////////////////////////////////////////////////
	inline bool operator==(const Vector2 &v1, const Vector2 &v2)
	{
		return ( ( absf(v1.x - v2.x) < EPSILON ) &&	//x
				( absf(v1.y - v2.y) < EPSILON ));	//y
	}

	////////////////////////////////////////////////////
	//operator !=
	////////////////////////////////////////////////////
	inline bool operator!=(const Vector2 &v1, const Vector2 &v2)
	{
		return !(v1==v2);
	}

	////////////////////////////////////////////////////
	//operator >
	////////////////////////////////////////////////////
	inline bool operator>(const Vector2 &v1, const Vector2 &v2)
	{
		return (v1.LenghtSqr() > v2.LenghtSqr());
	}

	////////////////////////////////////////////////////
	//operator <
	////////////////////////////////////////////////////
	inline bool operator<(const Vector2 &v1, const Vector2 &v2)
	{
		return v1.LenghtSqr() < v2.LenghtSqr();
	}

	////////////////////////////////////////////////////
	//IsZero()
	////////////////////////////////////////////////////
	inline const bool Vector2::IsZero() const
	{
		return((x==0)&&(y==0)) ? true : false;
	}

	////////////////////////////////////////////////////
	//Set(float,float,float)
	////////////////////////////////////////////////////
	inline void Vector2::Set(float xx, float yy)
	{
		x=xx;
		y=yy;
	}

	////////////////////////////////////////////////////
	//Set(float*)
	////////////////////////////////////////////////////
	inline void Vector2::Set(float * arr)
	{
		x=arr[0];
		y=arr[1];
	}

	////////////////////////////////////////////////////
	//Set(const Vector2 & vec)
	////////////////////////////////////////////////////
	inline void Vector2::Set(const Vector2 & vec)
	{
		x=vec.x;
		y=vec.y;
	}

	////////////////////////////////////////////////////
	//Abs() - sets components to absolute
	////////////////////////////////////////////////////
	inline void Vector2::Abs()
	{
		x=absf(x);
		y=absf(y);
	}

	////////////////////////////////////////////////////
	//Zero() - sets all components to 0
	////////////////////////////////////////////////////
	inline void Vector2::Zero()
	{
		x=0.0f;
		y=0.0f;
	}

	////////////////////////////////////////////////////
	//NormalizeFast() - reduces vector to unit lenght;
	//	faster, but less accurate than standard one
	////////////////////////////////////////////////////
	inline void Vector2::NormalizeFast()
	{
		const float tmpLenght = RSqrt(x*x + y*y);
		x *= tmpLenght;
		y *= tmpLenght;
	}


	////////////////////////////////////////////////////
	//Normalize() - reduces vector to unit-lenght (exact)
	////////////////////////////////////////////////////
	inline void Vector2::Normalize()
	{
	const float tmpLenght = 1.0f/sqrtf(x*x + y*y);
		x *= tmpLenght;
		y *= tmpLenght;
	}

	////////////////////////////////////////////////////
	//Lenght() - returns lenght of the vector
	////////////////////////////////////////////////////
	inline float Vector2::Lenght() const
	{
		return sqrtf(x*x+y*y);
	}

	////////////////////////////////////////////////////
	//LenghtSqr() - returns squared vector lenght
	////////////////////////////////////////////////////
	inline float Vector2::LenghtSqr() const
	{
		return (x*x + y*y);
	}

	////////////////////////////////////////////////////
	//ToString() - returns string representation of vector
	////////////////////////////////////////////////////
	inline std::string Vector2::ToString()
	{
		std::stringstream buff;
		std::string ret;
		buff << "V2(X: " << x <<" Y: "<< y <<")";
		//buff >> ret;
		return buff.str();
	}
	
}	//end of namespace ARK

#endif //__ARK_VECTOR2_H__