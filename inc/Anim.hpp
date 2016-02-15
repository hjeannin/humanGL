#ifndef ANIM_HPP
# define ANIM_HPP

# include "Transformation.hpp"
# include <iostream>
# include <vector>

class Anim
{
public:
	Mat4<GLfloat>					*matrix;
	Anim							*parent;
	Transformation					*scale;
	std::vector<Transformation *>	animation_transform;
	std::vector<Transformation *>	setup_transform;

	Anim(void);
	Anim(Mat4<GLfloat> *m, Anim *p);
	~Anim(void);

	void		setScale(GLfloat x, GLfloat y, GLfloat z);

	void		addRotation(bool isAnimation, int axis, GLfloat angle,
							GLuint start_frame = 0, GLuint end_frame = 0);
	void		addTranslation(bool isAnimation, GLfloat x, GLfloat y, GLfloat z,
							GLuint start_frame = 0, GLuint end_frame = 0);
	void		addScale(bool isAnimation, GLfloat x, GLfloat y, GLfloat z,
							GLuint start_frame = 0, GLuint end_frame = 0);
	void		runSetupTransformVector(std::vector<Transformation *> &v, Mat4<GLfloat> *m);
	void		runAnimationTransformVector(std::vector<Transformation *> &v, Mat4<GLfloat> *m);
	void		runAnim(void);
};

#endif