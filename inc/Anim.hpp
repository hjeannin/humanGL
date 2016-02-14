#ifndef ANIM_HPP
# define ANIM_HPP

# include "Transformation.hpp"
# include <vector>

class Anim
{
public:
	Mat4<GLfloat>					*matrix;
	Anim							*parent;
	std::vector<Transformation *>	animation_transform;
	std::vector<Transformation *>	setup_transform;

	Anim(void);
	Anim(Mat4<GLfloat> *m, Anim *p);
	~Anim(void);

	void		runTransformVector(std::vector<Transformation *> &v, Mat4<GLfloat> *m);

	void		runAnim(void);
	void		runSetup(void);
};

#endif