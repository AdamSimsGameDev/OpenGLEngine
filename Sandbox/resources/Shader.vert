#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec3 FragPos;  
out vec3 Normal;

void main()
{
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
	FragPos = vec3(u_Model * vec4(a_Position, 1.0));
	Normal = a_Normal;
}