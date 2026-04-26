		#ShaderVertex
		#version 330 core
		layout(location=0)in vec3 aPos;
		layout(location=1)in vec2 aTexCoord;
		out vec2 TexCoord;
		uniform mat4 model;
		uniform mat4 view;
		uniform mat projecction;
		void main()
		{
			gl_Position=projection*view*model*vec4(aPos,1.0);
			TexCoord=aTexCoord;
		}


		#ShaderFragment;
		#version 330 core 
		out vec4 FragColor;
		in vec2 TexCoord;
		uniform sampler2D texture1;
		uniform sampler2D texture2;
		void main()
		{
			FragColor=mix(texture(texture1,TeCoord),texture(texture2,TexCoord));
		}

