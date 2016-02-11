#include "Model.hpp"

Model::Model(void) : _part_count(1)
{
	part = new Part[_part_count];
	return;
}

Model::Model(GLuint pt) : _part_count(pt)
{
	part = new Part[_part_count];
	return;
}

Model::~Model(void)
{
	delete (part);
	return;
}

void
Model::genCubes(void)
{
	generateCube(&part[0], 0, 0);
	for (int i = 1; i < _part_count; i++)
	{
		generateCube(&part[i],
			part[i - 1].f_num_elem + part[i -1].num_faces_before,
			part[i - 1].v_num_elem + part[i -1].num_vertices_before);
	}
}

void
Model::changePartColor(Part *current_part, GLuint color)
{
	GLubyte		a = (color >> 0) & 0xFF;
	GLubyte		b = (color >> 8) & 0xFF;
	GLubyte		g = (color >> 16) & 0xFF;
	GLubyte		r = (color >> 24) & 0xFF;
	// TODO not change vertices too.
	current_part->v_array[0] = {-0.5f, 0.5f, 0.5f, r, g, b, a};
	current_part->v_array[1] = {0.5f, 0.5f, 0.5f, r, g, b, a};
	current_part->v_array[2] = {0.5f, -0.5f, 0.5f, r, g, b, a};
	current_part->v_array[3] = {-0.5f, -0.5f, 0.5f, r, g, b, a};
	current_part->v_array[4] = {-0.5f, 0.5f, -0.5f, r, g, b, a};
	current_part->v_array[5] = {0.5f, 0.5f, -0.5f, r, g, b, a};
	current_part->v_array[6] = {0.5f, -0.5f, -0.5f, r, g, b, a};
	current_part->v_array[7] = {-0.5f, -0.5f, -0.5f, r, g, b, a};
}

void
Model::generateCube(Part *current_part, int nfb, int nvb)
{
	current_part->num_faces_before = nfb;
	current_part->num_vertices_before = nvb;
	current_part->type = TYPE_CUBE;
	current_part->v_num_elem = 8;
	current_part->f_num_elem = 36;
	current_part->v_array = new Point[current_part->v_num_elem];
	current_part->f_array = new GLuint[current_part->f_num_elem];
	current_part->v_mem_size = sizeof(GLfloat) * 4 * current_part->v_num_elem;
	current_part->f_mem_size = sizeof(GLuint) * current_part->f_num_elem;
	current_part->m_matrix.setIdentity();

	//////////////////////////////////////////////////////////////////
	//                                           glFrontFace(GL_CW);//
    //          4----5		        ^  Y	                     	//
    //         /|   /|              |                     .------.  //
    //       0----1  |              |                    /       |  //
    //       |  7-|--6              |----->  X             .->   )  //
    //       |/   | /              /                      |     /   //
    //       3____2               /                        \___/    //
    //                          |,  Z                               //
	//                                           DEFAULT is GL_CCW  //
	//////////////////////////////////////////////////////////////////

	current_part->v_array[0] = {-0.5f, 0.5f, 0.5f, 123, 123, 123, 0};
	current_part->v_array[1] = {0.5f, 0.5f, 0.5f, 255, 0, 0, 0};
	current_part->v_array[2] = {0.5f, -0.5f, 0.5f, 255, 255, 255, 0};
	current_part->v_array[3] = {-0.5f, -0.5f, 0.5f, 0, 0, 255, 0};
	current_part->v_array[4] = {-0.5f, 0.5f, -0.5f, 255, 255, 0, 0};
	current_part->v_array[5] = {0.5f, 0.5f, -0.5f, 255, 0, 255, 0};
	current_part->v_array[6] = {0.5f, -0.5f, -0.5f, 0, 255, 255, 0};
	current_part->v_array[7] = {-0.5f, -0.5f, -0.5f, 0, 255, 0, 0};

	current_part->f_array[0] = nvb + 0;
	current_part->f_array[1] = nvb + 1;
	current_part->f_array[2] = nvb + 2;

	current_part->f_array[3] = nvb + 2;
	current_part->f_array[4] = nvb + 3;
	current_part->f_array[5] = nvb + 0;
	
	current_part->f_array[6] = nvb + 1;
	current_part->f_array[7] = nvb + 5;
	current_part->f_array[8] = nvb + 6;
	
	current_part->f_array[9] = nvb + 6;
	current_part->f_array[10] = nvb + 2;
	current_part->f_array[11] = nvb + 1;
	
	current_part->f_array[12] = nvb + 5;
	current_part->f_array[13] = nvb + 6;
	current_part->f_array[14] = nvb + 7;
	
	current_part->f_array[15] = nvb + 7;
	current_part->f_array[16] = nvb + 4;
	current_part->f_array[17] = nvb + 5;
	
	current_part->f_array[18] = nvb + 4;
	current_part->f_array[19] = nvb + 0;
	current_part->f_array[20] = nvb + 3;
	
	current_part->f_array[21] = nvb + 3;
	current_part->f_array[22] = nvb + 7;
	current_part->f_array[23] = nvb + 4;
	
	current_part->f_array[24] = nvb + 4;
	current_part->f_array[25] = nvb + 5;
	current_part->f_array[26] = nvb + 1;
	
	current_part->f_array[27] = nvb + 1;
	current_part->f_array[28] = nvb + 0;
	current_part->f_array[29] = nvb + 4;
	
	current_part->f_array[30] = nvb + 2;
	current_part->f_array[31] = nvb + 6;
	current_part->f_array[32] = nvb + 7;
	
	current_part->f_array[33] = nvb + 7;
	current_part->f_array[34] = nvb + 3;
	current_part->f_array[35] = nvb + 2;
}

void
Model::generateSphere(int size, GLubyte color_r, GLubyte color_g, GLubyte color_b)
{
	// TODO adapt to struct Model
	int				number_of_lines = size;
	int				nolk = number_of_lines + 1;
	int				index = 0;
	int				index2 = 0;
	double			pi = M_PI;
	double			tmp1 = 0;
	double			tmp2 = 0;
	double			tmp3 = 0;
	float			color_decr = 0.1;
	int				number_of_points = number_of_lines * nolk;
	int				number_of_faces = (number_of_points * 2) - (number_of_lines * 2);

	this->vertices_num_elem = number_of_points;
	this->faces_num_elem = 3 * number_of_faces;
	this->vertices_array = new Point[this->vertices_num_elem];
	this->faces_array = new GLuint[this->faces_num_elem];
	this->vertices_mem_size = sizeof(GLfloat) * this->vertices_num_elem * 4;
	this->faces_mem_size = sizeof(GLuint) * this->faces_num_elem;

		// std::cout << "R : " << static_cast<int>(color_r) << " G : " << static_cast<int>(color_g) << " B : " << static_cast<int>(color_b) << std::endl;
	for (int k = 0; k < nolk ; k++)
	{
		color_r -= color_decr;
		color_g -= color_decr;
		color_b -= color_decr;
		// std::cout << "R : " << static_cast<int>(color_r) << " G : " << static_cast<int>(color_g) << " B : " << static_cast<int>(color_b) << std::endl;
		for (int i = 0; i < number_of_lines ; i++)
		{
			tmp1 = sin(pi * k / number_of_lines) * cos(2.0 * pi * i / number_of_lines);
			tmp2 = sin(pi * k / number_of_lines) * sin(2.0 * pi * i / number_of_lines);
			tmp3 = cos(pi * k / number_of_lines);
			this->vertices_array[index] = {static_cast<GLfloat>(tmp1),
										static_cast<GLfloat>(tmp2),
										static_cast<GLfloat>(tmp3),
										color_r, color_g, color_b, 0};
			// std::cout << vertices_array[i].x << "," << vertices_array[i].y << "," << vertices_array[i].z << std::endl;
			index++;
		}
	}
	for (int j = 0; j < faces_num_elem; j += 6)
	{
		this->faces_array[j] = index2;
		this->faces_array[j + 1] = index2 + 1;
		this->faces_array[j + 2] = index2 + number_of_lines;
		this->faces_array[j + 3] = index2 + 1;
		this->faces_array[j + 4] = index2 + number_of_lines;
		this->faces_array[j + 5] = index2 + number_of_lines + 1;
		index2++;
	}
	// printArray(faces_array, faces_num_elem);
	// printPointArray(this->vertices_array, this->vertices_num_elem);
}
