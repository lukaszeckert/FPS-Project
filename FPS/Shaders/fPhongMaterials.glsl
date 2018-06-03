#version 330 core

out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
uniform Material material;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec4 Normal;
in vec4 FragPos;

void main()
{

	vec3 ambient = material.ambient * light.ambient;

	vec4 norm = normalize(Normal);
	vec4 lightDir = normalize(vec4(lightPos,1) - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse* (diff * material.diffuse);

	vec4 viewDir = normalize(vec4(viewPos,1.0)-FragPos);
	vec4 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular); 
	
	vec3 result = (ambient+diffuse+specular);
    FragColor = vec4(result, 1.0);
}