#include "headers/renderer.h"

void renderer2D::start_batch()
{
	m_buffer_ptr = m_buffer_base;
	/*texture_counter = 1;*/
}

renderer2D::renderer2D(int width , int height , const char* name) : m_width(width) , m_height(height)
{
	m_window =  new window (width, height , name , 3, 3);
	m_window -> checkwindow();
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	//checking if window is open or not
	if (!(m_window->checkwindow()))
	{
		cout << "couldn't open window from renderer !!";
		__debugbreak();
	}

	m_texture_slot.fill(0);	
	unsigned int offset = 0;
	for (int i = 0; i < 6000; i += 6)
	{
		m_ibo_buffer[i + 0] = offset + 0;
		m_ibo_buffer[i + 1] = offset + 1;
		m_ibo_buffer[i + 2] = offset + 2;
		m_ibo_buffer[i + 3] = offset + 2;
		m_ibo_buffer[i + 4] = offset + 3;
		m_ibo_buffer[i + 5] = offset + 0;	
		offset += 4;
	}

	//testing this with coordintes and indices array 
	/*float coordinates[] =
	{
		100.0f, 100.0f, 0.0f , 0.0f ,
		300.0f, 100.0f, 1.0f , 0.0f ,
		300.0f, 300.0f, 1.0f , 1.0f ,
		100.0f, 300.0f, 0.0f , 1.0f
	};

	unsigned int indices[] =
	{
		0,1,2,
		2,3,0
	};
	m_vao = new vao ;
	m_vbo = new vbo (coordinates, sizeof(coordinates));
	m_ibo = new ibo (indices, sizeof(indices));
	m_vao->loaddata(0, 2, 4, 0, 0);
	m_vao->loaddata(1, 2, 4, 2, 0);
	int actual_gpu_size = 0;
	GLcall(glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &actual_gpu_size));
	std::cout << "GPU KE ANDAR BUFFER KI SIZE CONSTRUCTOR SE : " << actual_gpu_size << " bytes\n" << std::endl;
	m_vbo->unbind();*/
	// RESULT : works perfectly fine 
	// OBSERVATIONS : no matter where we declare all the stuff (vao , vbo , ibo and all ) we can use them in the application with proper functions 


	//    ALL CLEAR
	//   STARTING DANGER ZONE
	m_vao = new vao;
	m_vbo = new vbo( sizeof(vertex)*MaxVertexCount);
	int actual_gpu_size = 0;
	GLcall(glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &actual_gpu_size));
	std::cout << "GPU KE ANDAR BUFFER KI SIZE CONSTRUCTOR SE : " << actual_gpu_size << " bytes\n" << std::endl;
	m_ibo = new ibo(m_ibo_buffer, MaxIndexCount);
	m_vao->loaddata(0, 2 , 9 , 0 , 0);
	m_vao->loaddata(1, 4 , 9 , 2 , 0);
	m_vao->loaddata(2, 2 , 9 , 6 , 0);
	m_vao->loaddata(3, 1 , 9 , 8 , 0);
	m_vbo->unbind();
}

void renderer2D::set_shader(string name_of_the_shader)
{
	m_shader = new shader("resources/shaders/default.shader");
	m_shader->use();
	m_shader->setsampler("text", 0);
	m_camera = new camera(m_width , m_height);
	glm::mat4 viewprojectionmatrix = m_camera->view_projection_matrix();
	m_shader->setsamplermatrix("view_projection", viewprojectionmatrix);
}

void renderer2D::set_texture(string location_of_the_texture, int slot)
{
	m_texture = new texture(location_of_the_texture, slot);
	m_texture->bind(texture_counter);
	m_texture_slot[texture_counter] = m_texture->get_texture_id();
	texture_counter++;
}

void renderer2D::swap_buffers()
{
	m_window -> swapbuffer();
}

void renderer2D::Begin_Scene( int texture_slot)
{
	
	/*viewprojectionmatrix = m_camera->view_projection_matrix();
	viewprojectionmatrix *= glm::translate(glm::mat4(1.0f), { 0.0f,0.0f,0.0f });
	m_shader->setsamplermatrix("view_projection", viewprojectionmatrix);*/
	start_batch();

}

void renderer2D::draw_quad(glm::vec2 left_bottom_corner, glm::vec2 right_top_corner, glm::vec3 r_g_b_values) //, vertex* structure_batao)
{
	//m_buffer_ptr = m_buffer_base;
	//m_buffer_ptr = structure_batao;
	//left bottom wala corner ka data
	m_buffer_ptr->coordinate = { left_bottom_corner.x,left_bottom_corner.y };
	m_buffer_ptr->rgba_value = glm::vec4(r_g_b_values, 1.0f);
	m_buffer_ptr->texturecoordinates = glm::vec2(0.0f, 0.0f);
	m_buffer_ptr->texture_index = 0.0f;
	m_buffer_ptr++;

	//right bottom wala corner ka data
	m_buffer_ptr->coordinate = { right_top_corner.x  ,left_bottom_corner.y };
	m_buffer_ptr->rgba_value = glm::vec4(r_g_b_values, 1.0f);
	m_buffer_ptr->texturecoordinates = glm::vec2(1.0f, 0.0f);
	m_buffer_ptr->texture_index = 0.0f;
	m_buffer_ptr++;

	//right top wala corner ka data
	m_buffer_ptr->coordinate = { right_top_corner.x  ,right_top_corner.y };
	m_buffer_ptr->rgba_value = glm::vec4(r_g_b_values, 1.0f);
	m_buffer_ptr->texturecoordinates = glm::vec2(1.0f, 1.0f);
	m_buffer_ptr->texture_index = 0.0f;
	m_buffer_ptr++;

	//left top wala corner ka data
	m_buffer_ptr->coordinate = { left_bottom_corner.x  , right_top_corner.y };
	m_buffer_ptr->rgba_value = glm::vec4(r_g_b_values, 1.0f);
	m_buffer_ptr->texturecoordinates = glm::vec2(0.0f, 1.0f);
	m_buffer_ptr->texture_index = 0.0f;
	m_buffer_ptr++;

	//uint32_t size = (uint32_t)((uint8_t*)m_buffer_ptr - (uint8_t*)m_buffer_base);
	//if (size == 0) return;
	// 
	//uint32_t indices = (uint32_t)((float)size / (float)sizeof(vertex) * 1.5f);
	////			THIS IS FOR TESTING
	//          std::cout << "BASE PTR: " << m_buffer_base << std::endl;
	//          std::cout << "CUR PTR : " << m_buffer_ptr << std::endl;
	//          std::cout << "SIZE    : " << size << std::endl;
	//		  m_vbo->bind();
	//m_vbo->subdata(m_buffer_base, size);
	//m_shader->use();
	//m_vao->bind();
	////m_ibo->bind();
	//m_texture->bind(0);
	//GLcall(glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, NULL));
}

void renderer2D::draw_quad(glm::vec2 left_bottom_corner, glm::vec2 right_top_corner, glm::vec3 r_g_b_values, vertex* structure_batao)
{
	
	//left bottom wala corner ka data
	structure_batao[0].coordinate = { left_bottom_corner.x,left_bottom_corner.y };
	structure_batao[0].rgba_value = glm::vec4(r_g_b_values, 1.0f);
	structure_batao[0].texturecoordinates = glm::vec2(0.0f, 0.0f);
	structure_batao[0].texture_index = 0.0f;

	cout <<endl<< "data bhar diya hai 1 ka :\n" << structure_batao[0].coordinate.x << "\n" << structure_batao[0].coordinate.y << "\n" << structure_batao[0].rgba_value.x << "\n" << structure_batao[0].rgba_value.y << "\n" << structure_batao[0].rgba_value.z << "\n" << structure_batao[0].rgba_value.w << "\n" << structure_batao[0].texturecoordinates.x << "\n" << structure_batao[0].texturecoordinates.y <<"\n" << structure_batao[0].texture_index;
	

	//right bottom wala corner ka data
	structure_batao[1].coordinate = { right_top_corner.x  ,left_bottom_corner.y };
	structure_batao[1].rgba_value = glm::vec4(r_g_b_values, 1.0f);
	structure_batao[1].texturecoordinates = glm::vec2(1.0f, 0.0f);
	structure_batao[1].texture_index = 0.0f;
	
	cout << endl << "data bhar diya hai 2 ka:\n" << structure_batao[1].coordinate.x << "\n" << structure_batao[1].coordinate.y << "\n" << structure_batao[1].rgba_value.x << "\n" << structure_batao[1].rgba_value.y << "\n" << structure_batao[1].rgba_value.z << "\n" << structure_batao[1].rgba_value.w << "\n" << structure_batao[1].texturecoordinates.x << "\n" << structure_batao[1].texturecoordinates.y << "\n" << structure_batao[1].texture_index;

	//right top wala corner ka data
	structure_batao[2].coordinate = { right_top_corner.x  ,right_top_corner.y };
	structure_batao[2].rgba_value = glm::vec4(r_g_b_values, 1.0f);
	structure_batao[2].texturecoordinates = glm::vec2(1.0f, 1.0f);
	structure_batao[2].texture_index = 0.0f;
	
	cout << endl << "data bhar diya hai 3 ka:\n" << structure_batao[2].coordinate.x << "\n" << structure_batao[2].coordinate.y << "\n" << structure_batao[2].rgba_value.x << "\n" << structure_batao[2].rgba_value.y << "\n" << structure_batao[2].rgba_value.z << "\n" << structure_batao[2].rgba_value.w << "\n" << structure_batao[2].texturecoordinates.x << "\n" << structure_batao[2].texturecoordinates.y << "\n" << structure_batao[2].texture_index;

	//left top wala corner ka data
	structure_batao[3].coordinate = { left_bottom_corner.x  , right_top_corner.y };
	structure_batao[3].rgba_value = glm::vec4(r_g_b_values, 1.0f);
	structure_batao[3].texturecoordinates = glm::vec2(0.0f, 1.0f);
	structure_batao[3].texture_index = 0.0f;

	cout << endl << "data bhar diya hai 4 ka:\n" << structure_batao[3].coordinate.x << "\n" << structure_batao[3].coordinate.y << "\n" << structure_batao[3].rgba_value.x << "\n" << structure_batao[3].rgba_value.y << "\n" << structure_batao[3].rgba_value.z << "\n" << structure_batao[3].rgba_value.w << "\n" << structure_batao[3].texturecoordinates.x << "\n" << structure_batao[3].texturecoordinates.y << "\n" << structure_batao[3].texture_index;

}

void renderer2D::End_Scene()
{
	Flush();
}

void renderer2D::Flush()
{
	uint32_t size = (uint32_t)((uint8_t*)m_buffer_ptr - (uint8_t*)m_buffer_base);
	if (size == 0) return;

	//==========================================================================================================//
	//                                          DEBUGGING !!                                                    //
	//==========================================================================================================//
	  // --- ASLI SACH YAHAN PATA CHALEGA ---
	//std::cout << "\n--- FLUSH DEBUG ---" << std::endl;
	//std::cout << "Buffer Ptr Address : " << m_buffer_ptr << std::endl;
	//std::cout << "Buffer Base Address: " << m_buffer_base << std::endl;
	//std::cout << "Calculated Size    : " << size << " bytes" << std::endl;
	//std::cout << "VBO Max Capacity   : " << sizeof(vertex) * 4000 << " bytes" << std::endl;
	//std::cout << "-------------------\n";

	//// --- ASLI X-RAY SCANNER ---
	//m_vbo->bind(); // Pehle VBO pakdo
	//int actual_gpu_size = 0;
	//GLcall(glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &actual_gpu_size));
	//std::cout << "GPU KE ANDAR BUFFER KI SIZE FLUSH SE: " << actual_gpu_size << " bytes\n" << std::endl;
	//// --------------------------

	////==========================================================================================================//
	////                                          DEBUGGING !!                                                    //
	////==========================================================================================================//
	////NAYA VBO KO BIND AND USE KARO
	//


	uint32_t indices = (uint32_t)((float)size / (float)sizeof(vertex) * 1.5f);
	m_vbo->loaddata(m_buffer_base, (int)(size/sizeof(vertex)));
	m_shader->use();
	m_vao->bind();
	//m_ibo->bind();
	m_texture->bind(0);
	GLcall(glDrawElements(GL_TRIANGLES, indices , GL_UNSIGNED_INT, NULL));

}

renderer2D::~renderer2D()
{
	delete m_window      ;
	delete m_vao         ;
	delete m_vbo         ;
	delete m_buffer_base ;
	delete m_ibo         ;
	delete m_shader      ;
	delete m_camera		 ;
	delete m_texture     ;
}









