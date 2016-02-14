#ifndef ANIM_HPP
# define ANIM_HPP

# include "Transformation.hpp"
# include <vector>

class Anim
{
public:
	Mat4<GLfloat>					*matrix;
	GLuint							part_index;
	int								parent_id;
	std::vector<Transformation *>	anim;
	std::vector<Transformation *>	setup;

	Anim(void);
	Anim(Mat4<GLfloat> *m, GLuint pi, int p_id);
	~Anim(void);

	void		runAnim(void);
	void		runSetup(void);
};

#endif