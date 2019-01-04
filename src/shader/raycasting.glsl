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
	

	
	switch(renderingMode)
	{
		case 0: //render front faces
		{
			
			float stepSize = 0.001f;

			vec3 exitPoint = texture(backFaces, texCoord).xyz;
			vec3 entryPoint = texture(frontFaces, texCoord).xyz;

			if (exitPoint == entryPoint) {
				discard;
			}

			vec3 dir = exitPoint - entryPoint;
			float len = length(dir);
			vec3 step = normalize(dir) * stepSize;
			float stepLen = length(step);
			
			vec3 voxel = entryPoint;
			vec4 colorAcum = vec4(0.0); 
			float alphaAcum = 0.0f;
			float lengthAcum = 0.0f;
			vec4 colorSample = vec4(0.0);
			float alphaSample = 0.0f;;

			for (int i = 0; i < 500; i++) {
				colorSample = texture(volume, texCoord);


				voxel += step;
				lengthAcum += stepLen;

				
				if (lengthAcum >= len || colorAcum.a > 1.0) {
					break;
				}

			}

			fragColor = colorAcum;



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