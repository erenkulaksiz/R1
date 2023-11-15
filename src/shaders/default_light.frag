#version 330 core
out vec4 FragColor;
in vec3 FragPos;
in vec2 texCoord;
in vec3 Normal;

struct Material {
    sampler2D diffuse;
    sampler2D normalMap;
    sampler2D specular;
    float shininess;
}; 

struct PointLight {
  vec3 position;

  float constant;
  float linear;
  float quadratic;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

	vec4 color;

  float intensity;

  bool enabled;
};

struct DirectionalLight {
  vec3 direction;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

  vec4 color;

  float intensity;

  bool enabled;
};

#define MAX_POINT_LIGHTS 5
#define MAX_DIRECTIONAL_LIGHTS 5

uniform int numberOfPointLights;
uniform int numberOfDirectionalLights;
uniform vec3 camPos;
uniform bool lightsEnabled;
uniform Material material;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient; // Ambient light should not be textured
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    ambient *= light.color.rgb;
    diffuse *= light.color.rgb;
    specular *= light.color.rgb;

    return (ambient + diffuse + specular) * light.intensity;
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient; // Ambient light should not be textured
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));
    ambient *= light.color.rgb;
    diffuse *= light.color.rgb;
    specular *= light.color.rgb;

    return (ambient + diffuse + specular) * light.intensity;
}

void main() {
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(camPos - FragPos);

  vec3 result = vec3(0.0);

  if(lightsEnabled) {
    for (int i = 0; i < numberOfPointLights; ++i) {
      if (!pointLights[i].enabled) {
        continue;
      }
      result += CalcPointLight(pointLights[i], normal, FragPos, viewDir);
    }

    for(int i = 0; i < numberOfDirectionalLights; ++i) {
      if (!directionalLights[i].enabled) {
        continue;
      }
      result += CalcDirectionalLight(directionalLights[i], normal, FragPos, viewDir);
    }
  } else {
    result = vec3(texture(material.diffuse, texCoord));
  }

	FragColor = vec4(result, 1.0f);
}