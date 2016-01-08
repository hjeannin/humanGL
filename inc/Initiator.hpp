#ifndef	INITIATOR_HPP
# define INITIATOR_HPP

# include <iostream>
# include "Mat4.hpp"

class Initiator
{

private:
	int			_status;

public:
	Mat4<GLfloat>	proj_matrix;
	Mat4<GLfloat>	view_matrix;
	Mat4<GLfloat>	trans_matrix;
	Mat4<GLfloat>	rot_matrix;
	Mat4<GLfloat>	scale_matrix;

	Initiator(void);
	Initiator(int _status);
	Initiator(Initiator const &src);
	~Initiator(void);

	int			getStatus(void) const;
	
	void		setProjMatrix(GLfloat fov, GLfloat near_cp, GLfloat far_cp);

	Initiator	&operator=(Initiator const &rhs);
};

std::ostream	&operator<<(std::ostream &o, Initiator const &i);

#endif
