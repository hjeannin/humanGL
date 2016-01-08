#include "Matrix.hpp"

Mat4::Mat4(void)
{
	identity();
	return;
}

Mat4::Mat4(const Glfloat src[16])
{
	setMat4(src);
	return;
}

Mat4::Mat4(Glfloat m00, Glfloat m01, Glfloat m02, Glfloat m03,    // col 1
		   Glfloat m04, Glfloat m05, Glfloat m06, Glfloat m07,    // col 2
		   Glfloat m08, Glfloat m09, Glfloat m10, Glfloat m11,    // col 3
		   Glfloat m12, Glfloat m13, Glfloat m14, Glfloat m15);   // col 4
{
	setMat4(m00, m01, m02, m03, m04, m05, m06, m07, m08, m09, m10, m11, m12, m13, m14, m15);   
}

Mat4::Mat4(Mat4 const &src)
{
	*this = src;
	return;
}

Mat4::~Mat4(void)
{
	return;
}

void
Mat4::setMat4(const Glfloat src[16])
{
	_m[0] = src[0];
	_m[1] = src[1];
	_m[2] = src[2];
	_m[3] = src[3];
	_m[4] = src[4];
	_m[5] = src[5];
	_m[6] = src[6];
	_m[7] = src[7];
	_m[8] = src[8];
	_m[9] = src[9];
	_m[10] = src[10];
	_m[11] = src[11];
	_m[12] = src[12];
	_m[13] = src[13];
	_m[14] = src[14];
	_m[15] = src[15];
}

Mat4::setMat4(Glfloat m00, Glfloat m01, Glfloat m02, Glfloat m03,    // col 1
			  Glfloat m04, Glfloat m05, Glfloat m06, Glfloat m07,    // col 2
			  Glfloat m08, Glfloat m09, Glfloat m10, Glfloat m11,    // col 3
			  Glfloat m12, Glfloat m13, Glfloat m14, Glfloat m15);   // col 4
{
	_m[0] = src[0];
	_m[1] = src[1];
	_m[2] = src[2];
	_m[3] = src[3];
	_m[4] = src[4];
	_m[5] = src[5];
	_m[6] = src[6];
	_m[7] = src[7];
	_m[8] = src[8];
	_m[9] = src[9];
	_m[10] = src[10];
	_m[11] = src[11];
	_m[12] = src[12];
	_m[13] = src[13];
	_m[14] = src[14];
	_m[15] = src[15];	
}


const Glfloat*
Mat4::getMat4(void) const
{
	return this->_status;
}

Mat4
&Mat4::operator=(Mat4 const &rhs)
{
	this->_status = rhs.getStatus();
	return *this;
}

std::ostream
&operator<<(std::ostream &o, Mat4 const &i)
{
	o << "I am the Mat4 of the world! My status is : " << i.getStatus() << std::endl;
	return o;
}
