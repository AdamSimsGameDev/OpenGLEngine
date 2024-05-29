#version 330 core
			
uniform vec3 u_LightPosition;
uniform vec3 u_LightDirection;
uniform vec4 u_LightColour;

layout(location = 0) out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
	vec3 norm = normalize(Normal);

	vec3 lightColor = vec3(1.0, 1.0, 1.0);
	float diff = clamp(dot(u_LightDirection, norm), 0., 1.);
	vec3 diffuse = diff * lightColor;

	vec3 objectColor = vec3(1.0, 1.0, 1.0);
	vec4 result = vec4((0.1 + diffuse) * objectColor, 1.0) * u_LightColour;
	color = result * texture(ourTexture, TexCoord);
}