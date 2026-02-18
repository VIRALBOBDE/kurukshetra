		 #shader vertex
		 #version 330 core   
		 layout  (location = 0) in vec2 pos;  
		 layout  (location = 1) in vec2 tex_pos;
		 out vec2 texture_positions;
		 uniform mat4 view_projection;
		 void main()  
		 {  
		 gl_Position       = view_projection * vec4(pos,0.0,1.0) ;
		 texture_positions = tex_pos           ; 
		 } 


		 #shader fragment
		 #version 330 core  
		 in  vec2 texture_positions    ;
		 out vec4 color                ;
		 uniform sampler2D text        ;
		 void main()  
		 {  
			 if(texture(text , texture_positions).xyz == vec3(0.0f,0.0f,0.0f)) 
								 color = vec4(0.0,1.0,0.0,1.0);
			 else				 color = texture(text , texture_positions);
		 }