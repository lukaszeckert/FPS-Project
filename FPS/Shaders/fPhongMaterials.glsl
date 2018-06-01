#version 330 core

out vec4 FragColor;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec4 Normal;
in vec4 FragPos;

void main()
{
	float ambientStrength = 0.1;
	float specularStrength = 0.5;


	vec4 norm = normalize(Normal);
	vec4 lightDir = normalize(vec4(lightPos,1) - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff*lightColor;

	vec4 viewDir = normalize(vec4(viewPos,1.0)-FragPos);
	vec4 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor; 
	
	vec3 ambient = ambientStrength * lightColor;
	vec3 result = (ambient+diffuse+specular)*objectColor;
    FragColor = vec4(result, 1.0);
}