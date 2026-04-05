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
		 uniform sampler2D text[32]        ;
		 void main()  
{  
			 int index = int(texture_index) ;
			 switch(index)
   {
    case 0: color = texture(text[0], texture_positions); 
					break;
    case 1: color = texture(text[1], texture_positions); break;
    case 2: color = texture(text[2], texture_positions); break;
    case 3: color = texture(text[3], texture_positions); break;
	case 4: color = texture(text[4], texture_positions); break;
    case 5: color = texture(text[5], texture_positions); break;
    case 6: color = texture(text[6], texture_positions); break;
    case 7: color = texture(text[7], texture_positions); break;
	case 8: color = texture(text[8], texture_positions); break;
    case 9: color = texture(text[9], texture_positions); break;
    case 10: color = texture(text[10], texture_positions); break;
    case 11: color = texture(text[11], texture_positions); break;
	case 12: color = texture(text[12], texture_positions); break;
    case 13: color = texture(text[13], texture_positions); break;
    case 14: color = texture(text[14], texture_positions); break;
    case 15: color = texture(text[15], texture_positions); break;
	case 16: color = texture(text[16], texture_positions); break;
    case 17: color = texture(text[17], texture_positions); break;
    case 18: color = texture(text[18], texture_positions); break;
    case 19: color = texture(text[19], texture_positions); break;
	case 20: color = texture(text[20], texture_positions); break;
    case 21: color = texture(text[21], texture_positions); break;
    case 22: color = texture(text[22], texture_positions); break;
    case 23: color = texture(text[23], texture_positions); break;
	case 24: color = texture(text[24], texture_positions); break;
    case 25: color = texture(text[25], texture_positions); break;
    case 26: color = texture(text[26], texture_positions); break;
    case 27: color = texture(text[27], texture_positions); break;
	case 28: color = texture(text[28], texture_positions); break;
    case 29: color = texture(text[29], texture_positions); break;
    case 30: color = texture(text[30], texture_positions); break;
    case 31: color = texture(text[31], texture_positions); break;
	default : color = frag_color ;
	int index = int(texture_index);
			 /*if(texture(text[index] , texture_positions).xyz == vec3(0.0f,0.0f,0.0f)) 
								 color = frag_color;
			 else				 color = texture(text[index] , texture_positions);*/
    }
}