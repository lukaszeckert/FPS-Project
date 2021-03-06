#version 330 core

out vec4 FragColor;
 

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 
struct DirLight{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

#define NR_POINT_LIGHTS 4

in vec4 Normal;
in vec4 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform int point_lights_number;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

uniform Material materialTex;


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);



void main()
{

    vec3 norm = vec3(normalize(Normal));
    vec3 viewDir = normalize(viewPos - vec3(FragPos));
    vec3 result = vec3(0,0,0);
    result = CalcDirLight(dirLight, norm, viewDir);
    for(int i = 0; i < point_lights_number; i++)
        result += CalcPointLight(pointLights[i], norm, vec3(FragPos), viewDir);    
    result += CalcSpotLight(spotLight, norm, vec3(FragPos), viewDir);    
    
    FragColor = vec4(result, 1.0);
}


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialTex.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(materialTex.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(materialTex.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(materialTex.specular, TexCoords));
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialTex.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(materialTex.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(materialTex.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(materialTex.specular, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
	
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
   // float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0.01);//materialTex.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	//if(intensity == 0)return vec3(1,0,0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(materialTex.diffuse, TexCoords));
    vec3 diffuse = light.diffuse  *  diff* vec3(texture(materialTex.diffuse, TexCoords));
    vec3 specular = light.specular  *  vec3(texture(materialTex.specular, TexCoords));
	ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
	//return intesity;
	  return (ambient + diffuse + specular);
   
}