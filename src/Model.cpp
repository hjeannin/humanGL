#include "Model.hpp"

Model::Model(void)
{
	return;
}

Model::~Model(void)
{
	// TODO transform *part in vector for deletion
	// for (GLuint i = 0; i < _part_count; i++)
	// {
	// 	delete (part[i]);
	// }
	for (GLuint j = 0; j < anim_vector.size(); j++)
	{
		delete (anim_vector[j]);
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
Model::changePartColor(int index, GLuint color)
{
	GLubyte		a = (color >> 0) & 0xFF;
	GLubyte		b = (color >> 8) & 0xFF;
	GLubyte		g = (color >> 16) & 0xFF;
	GLubyte		r = (color >> 24) & 0xFF;

	for (GLuint j = 0; j < part[index].v_num_elem; j++)
	{
		part[index].v_array[j].r = r;
		part[index].v_array[j].g = g;
		part[index].v_array[j].b = b;
		part[index].v_array[j].a = a;
	}
}

Mat4<GLfloat>
*Model::findMatrix(int index)
{
	return (&part[index].matrix);
}

void
Model::runAnimVectorAnim(void)
{
	for (GLuint i = 0; i < anim_vector.size(); i++)
	{
		anim_vector[i]->runAnim(frame);
	}	
}

////////////////////////
// SEE use in Initiator->drawModel()
void
Model::animate(void)
{
	frame++;
	if (frame == max_frame)
		frame = 0;
	runAnimVectorAnim();
}

void
Model::reset(void)
{
	for (GLuint i = 0; i < _part_count; i++)
	{
		part[i].matrix.setIdentity();
	}
}
////////////////////////

void
Model::multiAnim(void)
{
	Anim	*main = new Anim(findMatrix(0), NULL);
	Anim	*sub1 = new Anim(findMatrix(1), main);
	Anim	*sub2 = new Anim(findMatrix(2), main);
	Anim	*sub3 = new Anim(findMatrix(3), main);
	Anim	*sub4 = new Anim(findMatrix(4), main);
	Anim	*sub5 = new Anim(findMatrix(5), main);
	Anim	*sub6 = new Anim(findMatrix(6), main);
	Anim	*sub7 = new Anim(findMatrix(7), main);
	Anim	*sub8 = new Anim(findMatrix(8), main);
	Anim	*sub9 = new Anim(findMatrix(9), main);
	Anim	*sub10 = new Anim(findMatrix(10), main);
	Anim	*sub11 = new Anim(findMatrix(11), main);
	Anim	*sub12 = new Anim(findMatrix(12), main);
	Anim	*sub13 = new Anim(findMatrix(13), main);
	Anim	*sub14 = new Anim(findMatrix(14), main);
	Anim	*sub15 = new Anim(findMatrix(15), main);
	Anim	*sub16 = new Anim(findMatrix(16), main);
	Anim	*sub17 = new Anim(findMatrix(17), main);
	Anim	*sub18 = new Anim(findMatrix(18), main);

	anim_vector.push_back(main);
	anim_vector.push_back(sub1);
	anim_vector.push_back(sub2);
	anim_vector.push_back(sub3);
	anim_vector.push_back(sub4);
	anim_vector.push_back(sub5);
	anim_vector.push_back(sub6);
	anim_vector.push_back(sub7);
	anim_vector.push_back(sub8);
	anim_vector.push_back(sub9);
	anim_vector.push_back(sub10);
	anim_vector.push_back(sub11);
	anim_vector.push_back(sub12);
	anim_vector.push_back(sub13);
	anim_vector.push_back(sub14);
	anim_vector.push_back(sub15);
	anim_vector.push_back(sub16);
	anim_vector.push_back(sub17);
	anim_vector.push_back(sub18);
}

void
Model::buildWTF(void)
{
	GLuint		sf = 0;
	GLuint		mf = 60;
	GLuint		ef = 120;

	max_frame = ef;
	setNeededPart(19);
	genCubes();
	multiAnim();
	anim_vector[0]->addRotation(ANIM, Y_AXIS, 360.0f, sf, ef);
	anim_vector[0]->addRotation(ANIM, X_AXIS, 360.0f, sf, ef);

	anim_vector[1]->addTranslation(SETUP, 1.0f, 0.0f, 0.0f);
	anim_vector[2]->addTranslation(SETUP, -1.0f, 0.0f, 0.0f);
	anim_vector[3]->addTranslation(SETUP, 0.0f, 1.0f, 0.0f);
	anim_vector[4]->addTranslation(SETUP, 0.0f, -1.0f, 0.0f);
	anim_vector[5]->addTranslation(SETUP, 0.0f, 0.0f, 1.0f);
	anim_vector[6]->addTranslation(SETUP, 0.0f, 0.0f, -1.0f);

	anim_vector[7]->addTranslation(SETUP, 1.0f, 1.0f, 0.0f);
	anim_vector[8]->addTranslation(SETUP, 1.0f, -1.0f, 0.0f);
	anim_vector[9]->addTranslation(SETUP, -1.0f, 1.0f, 0.0f);
	anim_vector[10]->addTranslation(SETUP, -1.0f, -1.0f, 0.0f);

	anim_vector[11]->addTranslation(SETUP, 1.0f, 1.0f, 1.0f);
	anim_vector[12]->addTranslation(SETUP, 1.0f, -1.0f, 1.0f);
	anim_vector[13]->addTranslation(SETUP, -1.0f, 1.0f, 1.0f);
	anim_vector[14]->addTranslation(SETUP, -1.0f, -1.0f, 1.0f);

	anim_vector[15]->addTranslation(SETUP, 1.0f, 1.0f, -1.0f);
	anim_vector[16]->addTranslation(SETUP, 1.0f, -1.0f, -1.0f);
	anim_vector[17]->addTranslation(SETUP, -1.0f, 1.0f, -1.0f);
	anim_vector[18]->addTranslation(SETUP, -1.0f, -1.0f, -1.0f);

	anim_vector[1]->addTranslation(ANIM, -2.0f, 0.0f, 0.0f, sf, mf);
	anim_vector[2]->addTranslation(ANIM, 2.0f, 0.0f, 0.0f, sf, mf);
	anim_vector[1]->addTranslation(ANIM, 2.0f, 0.0f, 0.0f, mf, ef);
	anim_vector[2]->addTranslation(ANIM, -2.0f, 0.0f, 0.0f, mf, ef);

	anim_vector[3]->addTranslation(ANIM, 0.0f, -2.0f, 0.0f, sf, mf);
	anim_vector[4]->addTranslation(ANIM, 0.0f, 2.0f, 0.0f, sf, mf);
	anim_vector[3]->addTranslation(ANIM, 0.0f, 2.0f, 0.0f, mf, ef);
	anim_vector[4]->addTranslation(ANIM, 0.0f, -2.0f, 0.0f, mf, ef);

	anim_vector[5]->addTranslation(ANIM, 0.0f, 0.0f, -2.0f, sf, mf);
	anim_vector[6]->addTranslation(ANIM, 0.0f, 0.0f, 2.0f, sf, mf);
	anim_vector[5]->addTranslation(ANIM, 0.0f, 0.0f, 2.0f, mf, ef);
	anim_vector[6]->addTranslation(ANIM, 0.0f, 0.0f, -2.0f, mf, ef);

	anim_vector[7]->addTranslation(ANIM, -2.0f, -2.0f, 0.0f, sf, mf);
	anim_vector[8]->addTranslation(ANIM, -2.0f, 2.0f, 0.0f, sf, mf);
	anim_vector[7]->addTranslation(ANIM, 2.0f, 2.0f, 0.0f, mf, ef);
	anim_vector[8]->addTranslation(ANIM, 2.0f, -2.0f, 0.0f, mf, ef);

	anim_vector[9]->addTranslation(ANIM, 2.0f, -2.0f, 0.0f, sf, mf);
	anim_vector[10]->addTranslation(ANIM, 2.0f, 2.0f, 0.0f, sf, mf);
	anim_vector[9]->addTranslation(ANIM, -2.0f, 2.0f, 0.0f, mf, ef);
	anim_vector[10]->addTranslation(ANIM, -2.0f, -2.0f, 0.0f, mf, ef);

	anim_vector[11]->addTranslation(ANIM, -2.0f, -2.0f, -2.0f, sf, mf);
	anim_vector[12]->addTranslation(ANIM, -2.0f, 2.0f, -2.0f, sf, mf);
	anim_vector[11]->addTranslation(ANIM, 2.0f, 2.0f, 2.0f, mf, ef);
	anim_vector[12]->addTranslation(ANIM, 2.0f, -2.0f, 2.0f, mf, ef);

	anim_vector[13]->addTranslation(ANIM, 2.0f, -2.0f, -2.0f, sf, mf);
	anim_vector[14]->addTranslation(ANIM, 2.0f, 2.0f, -2.0f, sf, mf);
	anim_vector[13]->addTranslation(ANIM, -2.0f, 2.0f, 2.0f, mf, ef);
	anim_vector[14]->addTranslation(ANIM, -2.0f, -2.0f, 2.0f, mf, ef);

	anim_vector[15]->addTranslation(ANIM, -2.0f, -2.0f, 2.0f, sf, mf);
	anim_vector[16]->addTranslation(ANIM, -2.0f, 2.0f, 2.0f, sf, mf);
	anim_vector[15]->addTranslation(ANIM, 2.0f, 2.0f, -2.0f, mf, ef);
	anim_vector[16]->addTranslation(ANIM, 2.0f, -2.0f, -2.0f, mf, ef);

	anim_vector[17]->addTranslation(ANIM, 2.0f, -2.0f, 2.0f, sf, mf);
	anim_vector[18]->addTranslation(ANIM, 2.0f, 2.0f, 2.0f, sf, mf);
	anim_vector[17]->addTranslation(ANIM, -2.0f, 2.0f, -2.0f, mf, ef);
	anim_vector[18]->addTranslation(ANIM, -2.0f, -2.0f, -2.0f, mf, ef);
}

void
Model::buildPouet(void)
{
	setNeededPart(3);
	genCubes();
	
	changePartColor(SBC, 0x0000FF00);
	changePartColor(MGC, 0x00FF0000);
	changePartColor(BRC, 0xFF000000);

	Anim		*sbc_a = new Anim(findMatrix(SBC), NULL);
	Anim		*mgc_a = new Anim(findMatrix(MGC), sbc_a);
	Anim		*brc_a = new Anim(findMatrix(BRC), mgc_a);
	
	anim_vector = {sbc_a, mgc_a, brc_a};

	anim_vector[SBC]->setScale(1.0f, 7.0f, 1.0f);
	anim_vector[SBC]->addRotation(ANIM, Y_AXIS, 360.0f, 0, 1200);

	anim_vector[MGC]->setScale(3.0f, 1.0f, 1.0f);
	anim_vector[MGC]->addTranslation(SETUP, 2.0f, 0.0f, 0.0f);
	anim_vector[MGC]->addTranslation(SETUP, 0.0f, 3.0f, 0.0f);
	// anim_vector[MGC]->addRotation(ANIM, X_AXIS, 3000.0f, 0, 1200);
	// anim_vector[MGC]->addTranslation(ANIM, 0.0f, 1.0f, 0.0f, 0, 200);
	
	anim_vector[BRC]->setScale(1.0f, 10.0f, 3.0f);
	// anim_vector[BRC]->addRotation(SETUP, Z_AXIS, 90.0f);
	anim_vector[BRC]->addTranslation(SETUP, 1.0f, 0.0f, 0.0f);
	anim_vector[BRC]->addRotation(ANIM, X_AXIS, 3600.0f, 0, 1200);
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
