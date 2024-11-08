#version 330 core

out vec4 FragColor;

in vec2 UV;

uniform sampler2D tex0;

uniform sampler2D normals;
uniform vec3 crntPos;
uniform float ambient;

struct PointLight {    
    vec3 position;
    vec4 color;
};

#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec4 PointLightCalc(PointLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightVec = light.position - crntPos;
	float distance = length(lightVec);
	float a = 0.05f;
	float b = 0.01f;
	float intensity = 1.0f / (a * distance * distance + b * distance + 1.0f);

	vec3 lightDir = normalize(lightVec);
	float diffuse = max(dot(normal, lightDir), 0.0f);

	float specular = 0.0f;
	if (diffuse != 0.0f)
	{
		float specularLight = 0.5f;
		vec3 halfwayVec = normalize(viewDir + lightDir);
		float specAmount = pow(max(dot(normal, halfwayVec), 0.0f), 8);
		specular = specAmount * specularLight;
	}

	if (texture(tex0, UV).a < 0.1f)
	{
		discard;
	}

	return light.color * (diffuse * intensity + specular * intensity);
}

void main()
{
	vec3 norm = normalize(texture(normals, UV).xyz * 2 - 1.0f);
	vec3 viewDir = vec3(0.0f, 0.0f, 1.0f);

	vec4 result = vec4(ambient, ambient, ambient, 1.0f);
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
	{
			result += PointLightCalc(pointLights[i], norm, viewDir);
	}

	FragColor = texture(tex0, UV) * result;
}