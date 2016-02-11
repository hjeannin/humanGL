#include "Model.hpp"

Model::Model(void)
{
	return;
}

Model::~Model(void)
{
	if (_part_count != 0)
	{
		delete (part);
	}
	return;
}

GLuint
Model::getPartCount(void) const
{
	return this->_part_count;
}

void
Model::setNeededPart(GLuint n)
{
	_part_count = n;
	part = new Part[_part_count];	
}

void
Model::buildPouet(void)
{
	setNeededPart(3);
	genCubes();
	ids[SBC] = 0;
	ids[MGC] = 1;
	ids[BRC] = 2;

	changePartColor(SBC, 0x0000FF00);
	part[findIDIndex(SBC)].matrix.scale(0.5f, 0.5f, 0.5f);



	changePartColor(MGC, 0x00FF0000);
	part[findIDIndex(MGC)].matrix.scale(1.0f, 1.0f, 1.0f);

	part[findIDIndex(MGC)].matrix.translate(1.0f, 0.0f, 0.0f);



	changePartColor(BRC, 0xFF000000);
	part[findIDIndex(BRC)].matrix.scale(2.0f, 2.0f, 2.0f);

	part[findIDIndex(BRC)].matrix.translate(1.0f, 0.0f, 0.0f);

	part[findIDIndex(BRC)].matrix.translate(1.0f, 0.0f, 0.0f);
}

/*

class Anim
{
	Mat4<GLfloat>	*matrix;
	GLuint			part_index;
	Part			*Parent;
	Part			*Child;
	Transformation	*anim;
	Transformation	*setup;
};

for (every parts)
{
	if (Parent == NULL)
	{
		Transform.anim(my_matrix);
		Transform.setup(my_matrix);
	}
	else if (Parent != NULL)
	{
		if (Parent->Parent == NULL)
		{
			Parent->Transform.anim(my_matrix);
			Parent->Transform.setup(my_matrix);
			Transform.anim(my_matrix);
			Transform.setup(my_matrix);
		}
		else if (Parent->Parent != NULL)
		{
			Parent->Parent->Transform.anim(my_matrix);
			Parent->Parent->Transform.setup(my_matrix);
			Parent->Transform.anim(my_matrix);
			Parent->Transform.setup(my_matrix);
			Transform.anim(my_matrix);
			Transform.setup(my_matrix);
		}
	}
}

*/

void
Model::animate(void)
{
	if (frame < 600)
	{
		part[findIDIndex(SBC)].matrix.rotate(1.0f * frame, 1.0f, 0.0f, 0.0f);
		part[findIDIndex(SBC)].matrix.rotate(1.0f * frame, 0.0f, 1.0f, 0.0f);

		part[findIDIndex(MGC)].matrix.rotate(1.0f * frame, 1.0f, 0.0f, 0.0f);
		part[findIDIndex(MGC)].matrix.rotate(1.0f * frame, 0.0f, 1.0f, 0.0f);
		part[findIDIndex(MGC)].matrix.translate(1.0f, 0.0f, 0.0f);

		part[findIDIndex(BRC)].matrix.rotate(1.0f * frame, 1.0f, 0.0f, 0.0f);
		part[findIDIndex(BRC)].matrix.rotate(1.0f * frame, 0.0f, 1.0f, 0.0f);
		part[findIDIndex(BRC)].matrix.translate(1.0f, 0.0f, 0.0f);
		part[findIDIndex(BRC)].matrix.translate(1.0f, 0.0f, 0.0f);

	}
	frame++;
	if (frame == 600)
		frame = 0;
}

void
Model::reset(void)
{

	part[findIDIndex(SBC)].matrix.setIdentity();
	part[findIDIndex(SBC)].matrix.scale(0.5f, 0.5f, 0.5f);

	part[findIDIndex(MGC)].matrix.setIdentity();
	part[findIDIndex(MGC)].matrix.scale(1.0f, 1.0f, 1.0f);

	part[findIDIndex(BRC)].matrix.setIdentity();
	part[findIDIndex(BRC)].matrix.scale(2.0f, 2.0f, 2.0f);	
}

void
Model::buildHuman(void)
{
	/////////////////////////////////////////////////////
	//			BACK VIEW
	//
	//					[11]
	//LEFT				  |					RIGHT
	//		[32]--[31]--[10]--[21]--[22]
	//					 ||
	//					/	\
	//				[51]	[41]
	//				  |		  |
	//				[52]	[42]
	//
	/////////////////////////////////////////////////////

	setNeededPart(10);
	genCubes();
	fillHumanIDs();

	changePartColor(BODY, 0xad45ed00);
	part[0].matrix.scale(2.0f, 3.0f, 1.0f);

	changePartColor(HEAD, 0xFafafa00);
	part[1].matrix.translate(0.0f, 2.0f, 0.0f);

	part[2].matrix.scale(2.0f, 0.8f, 0.8f);
	part[2].matrix.translate(1.0f, 0.8f, 0.0f);
	
	part[3].matrix.scale(2.0f, 0.8f, 0.8f);
	part[3].matrix.translate(2.0f, 0.8f, 0.0f);

	part[4].matrix.scale(2.0f, 0.8f, 0.8f);
	part[4].matrix.translate(-1.0f, 0.8f, 0.0f);

	part[5].matrix.scale(2.0f, 0.8f, 0.8f);
	part[5].matrix.translate(-2.0f, 0.8f, 0.0f);

	part[6].matrix.scale(0.8f, 2.0f, 0.8f);
	part[6].matrix.translate(1.0f, -1.0f, 0.0f);

	part[7].matrix.scale(0.8f, 2.0f, 0.8f);
	part[7].matrix.translate(1.0f, -2.0f, 0.0f);

	part[8].matrix.scale(0.8f, 2.0f, 0.8f);
	part[8].matrix.translate(-1.0f, -1.0f, 0.0f);

	changePartColor(LEG_L_F, 0xffffff00);
	part[9].matrix.scale(0.8f, 2.0f, 0.8f);
	part[9].matrix.translate(-1.0f, -2.0f, 0.0f);
}

void
Model::fillHumanIDs(void)
{
	ids[BODY] = 0;
	ids[HEAD] = 1;
	ids[ARM_R_R] = 2;
	ids[ARM_R_F] = 3;
	ids[ARM_L_R] = 4;
	ids[ARM_L_F] = 5;
	ids[LEG_R_R] = 6;
	ids[LEG_R_F] = 7;
	ids[LEG_L_R] = 8;
	ids[LEG_L_F] = 9;
}

GLuint
Model::findIDIndex(int id)
{
	return (ids[id]);
}

void
Model::genCubes(void)
{
	if (_part_count != 0)
	{
		generateCube(&part[0], 0, 0);
		for (GLuint i = 1; i < _part_count; i++)
		{
			generateCube(&part[i],
				part[i - 1].f_num_elem + part[i -1].num_faces_before,
				part[i - 1].v_num_elem + part[i -1].num_vertices_before);
		}
	}
	else
	{
		std::cerr << "parts not allocated" << std::endl;
	}
}

void
Model::changePartColor(int id, GLuint color)
{
	GLuint		i = findIDIndex(id);
	GLubyte		a = (color >> 0) & 0xFF;
	GLubyte		b = (color >> 8) & 0xFF;
	GLubyte		g = (color >> 16) & 0xFF;
	GLubyte		r = (color >> 24) & 0xFF;

	for (GLuint j = 0; j < part[i].v_num_elem; j++)
	{
		part[i].v_array[j].r = r;
		part[i].v_array[j].g = g;
		part[i].v_array[j].b = b;
		part[i].v_array[j].a = a;
	}
}

void
Model::generateCube(Part *current_part, int nfb, int nvb)
{
	current_part->num_faces_before = nfb;
	current_part->num_vertices_before = nvb;
	current_part->shape = CUBE;
	current_part->v_num_elem = 8;
	current_part->f_num_elem = 36;
	current_part->v_array = new Point[current_part->v_num_elem];
	current_part->f_array = new GLuint[current_part->f_num_elem];
	current_part->v_mem_size = sizeof(GLfloat) * 4 * current_part->v_num_elem;
	current_part->f_mem_size = sizeof(GLuint) * current_part->f_num_elem;
	current_part->matrix.setIdentity();

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

// void
// Model::generateSphere(int size, GLubyte color_r, GLubyte color_g, GLubyte color_b)
// {
// 	// TODO adapt to struct Model
// 	int				number_of_lines = size;
// 	int				nolk = number_of_lines + 1;
// 	int				index = 0;
// 	int				index2 = 0;
// 	double			pi = M_PI;
// 	double			tmp1 = 0;
// 	double			tmp2 = 0;
// 	double			tmp3 = 0;
// 	float			color_decr = 0.1;
// 	int				number_of_points = number_of_lines * nolk;
// 	int				number_of_faces = (number_of_points * 2) - (number_of_lines * 2);

// 	this->vertices_num_elem = number_of_points;
// 	this->faces_num_elem = 3 * number_of_faces;
// 	this->vertices_array = new Point[this->vertices_num_elem];
// 	this->faces_array = new GLuint[this->faces_num_elem];
// 	this->vertices_mem_size = sizeof(GLfloat) * this->vertices_num_elem * 4;
// 	this->faces_mem_size = sizeof(GLuint) * this->faces_num_elem;

// 		// std::cout << "R : " << static_cast<int>(color_r) << " G : " << static_cast<int>(color_g) << " B : " << static_cast<int>(color_b) << std::endl;
// 	for (int k = 0; k < nolk ; k++)
// 	{
// 		color_r -= color_decr;
// 		color_g -= color_decr;
// 		color_b -= color_decr;
// 		// std::cout << "R : " << static_cast<int>(color_r) << " G : " << static_cast<int>(color_g) << " B : " << static_cast<int>(color_b) << std::endl;
// 		for (int i = 0; i < number_of_lines ; i++)
// 		{
// 			tmp1 = sin(pi * k / number_of_lines) * cos(2.0 * pi * i / number_of_lines);
// 			tmp2 = sin(pi * k / number_of_lines) * sin(2.0 * pi * i / number_of_lines);
// 			tmp3 = cos(pi * k / number_of_lines);
// 			this->vertices_array[index] = {static_cast<GLfloat>(tmp1),
// 										static_cast<GLfloat>(tmp2),
// 										static_cast<GLfloat>(tmp3),
// 										color_r, color_g, color_b, 0};
// 			// std::cout << vertices_array[i].x << "," << vertices_array[i].y << "," << vertices_array[i].z << std::endl;
// 			index++;
// 		}
// 	}
// 	for (int j = 0; j < faces_num_elem; j += 6)
// 	{
// 		this->faces_array[j] = index2;
// 		this->faces_array[j + 1] = index2 + 1;
// 		this->faces_array[j + 2] = index2 + number_of_lines;
// 		this->faces_array[j + 3] = index2 + 1;
// 		this->faces_array[j + 4] = index2 + number_of_lines;
// 		this->faces_array[j + 5] = index2 + number_of_lines + 1;
// 		index2++;
// 	}
// 	// printArray(faces_array, faces_num_elem);
// 	// printPointArray(this->vertices_array, this->vertices_num_elem);
// }
