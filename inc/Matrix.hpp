#ifndef	MATRIX_HPP
# define MATRIX_HPP

# include <SFML/OpenGL.hpp>
# include <iostream>

class Mat4
{

private:
	Glfloat		_m[16];

public:

	Mat4(void);
	Mat4(const Glfloat src[16]);
	Mat4(Glfloat m00, Glfloat m01, Glfloat m02, Glfloat m03,	// col 1
		 Glfloat m04, Glfloat m05, Glfloat m06, Glfloat m07,	// col 2
		 Glfloat m08, Glfloat m09, Glfloat m10, Glfloat m11,	// col 3
		 Glfloat m12, Glfloat m13, Glfloat m14, Glfloat m15);	// col 4
	Mat4(Mat4 const &src);
	~Mat4(void);

	void			setMat4(const Glfloat src[16]);
	void			setMat4(Glfloat m00, Glfloat m01, Glfloat m02, Glfloat m03,	// col 1
							Glfloat m04, Glfloat m05, Glfloat m06, Glfloat m07,	// col 2
							Glfloat m08, Glfloat m09, Glfloat m10, Glfloat m11,	// col 3
							Glfloat m12, Glfloat m13, Glfloat m14, Glfloat m15);// col 4

	const Glfloat*	getMat4(void) const;

	Mat4	&operator=(Mat4 const &rhs);
};

std::ostream	&operator<<(std::ostream &o, Mat4 const &i);

#endif
