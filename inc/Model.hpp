#ifndef MODEL_HPP
# define MODEL_HPP

# define TYPE_CUBE		42
# define TYPE_SPHERE	43

# include "Mat4.hpp"

class Model
{
private:
	GLuint			_part_count;

public:	
	struct Point
	{
		GLfloat		x;
		GLfloat		y;
		GLfloat		z;
		GLubyte		r;
		GLubyte		g;
		GLubyte		b;
		GLubyte		a;
	};

	struct Part
	{
		Mat4<GLfloat>	matrix;
		GLuint			num_vertices_before = 0;
		GLuint			num_faces_before = 0;
		int				v_mem_size;
		int				v_num_elem;
		Point			*v_array;
		int				f_mem_size;
		int				f_num_elem;
		GLuint			*f_array;
		int				type;		
	};

	Part			*part;

	Model(void);
	Model(GLuint part_count);
	~Model(void);
	
	void		genCubes(void);
	void		changePartColor(Part *current_part, GLuint color);
	void		generateCube(Model *model, int nfb, int nvb);
	void		generateSphere(int size, GLubyte color_r, GLubyte color_g, GLubyte color_b);

};

#endif