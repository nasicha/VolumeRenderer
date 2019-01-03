-- Vertex

#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) in vec3 vertex;

out vec2 texCoord;

void main()
{
	// ToDo
	gl_Position = vec4(vertex, 1.0);

	texCoord = (vertex.xy + 1.0)*0.5;
}

-- Fragment

uniform sampler2D frontFaces;
uniform sampler2D backFaces;
uniform sampler3D volume;

uniform int renderingMode;

in vec2 texCoord;
out vec4 fragColor;

void main()
{
	// ToDo
	fragColor = vec4(1.0, 0.0, 1.0, 1.0);



	
	switch(renderingMode)
	{
		case 0: //render front faces
		{
			
			break;
		}
		
		case 1: //render back faces
		{
			
			
			
			break;
		}
		
		case 2: //render volume (MIP)
		{
			
			
			
			break;
		}
		case 3: //render volume (Alpha-Compositing)
		{
			break;
		}
	}
}