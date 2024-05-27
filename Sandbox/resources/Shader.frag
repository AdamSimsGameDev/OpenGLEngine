#version 330 core
			
uniform vec3 u_LightPosition;  

layout(location = 0) out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(u_LightPosition - FragPos);  

	vec3 lightColor = vec3(1.0, 1.0, 1.0);
	float diff = clamp(dot(lightDir, norm), 0., 1.);
	vec3 diffuse = diff * lightColor;

	vec3 objectColor = vec3(1.0, 1.0, 1.0);
	vec3 result = (0.1 + diffuse) * objectColor;
	color = vec4(result, 1.0) * texture(ourTexture, TexCoord);
}