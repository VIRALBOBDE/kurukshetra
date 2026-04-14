		 #shader vertex
		 #version 330 core   

		 //input variables
		 layout  (location = 0) in vec2 pos;  
		 layout  (location = 1) in vec4 vert_color ;
		 layout  (location = 2) in vec2 tex_pos;
		 layout  (location = 3) in float tex_ind;

		 //output variables
 		 out vec4 frag_color ;
		 out vec2 texture_positions;
		 out float texture_index ;

		 //uniform variables
		 uniform mat4 view_projection;


		 void main()  
		 {  
         gl_Position       = view_projection * vec4(pos,0.0,1.0) ;
		 texture_positions = tex_pos           ; 
		 frag_color = vert_color               ;
		 texture_index = tex_ind               ;
		  //gl_Position       =  vec4(pos.x/1280 , pos.y/720 ,0.0,1.0) ;    test case  1
		 } 


		 #shader fragment
		 #version 330 core  

		 //input variables
		 in  vec4 frag_color           ;
		 in  vec2 texture_positions    ;
		 in  float texture_index       ;

		 //output variables
		 out vec4 color                ;

		 //uniform variables
		 uniform sampler2D text        ;
		 void main()  
		 {  
			 if(texture(text , texture_positions).xyz == vec3(0.0f,0.0f,0.0f)) 
								 color = frag_color;
			 else				 color = texture(text , texture_positions);
		 }