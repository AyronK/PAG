#version 450 core

in vec2 fragVertexTexture;
//Zmienna wspó³rzêdnych tekstury z vertex shadera
smooth in vec3 Normal;
in vec3 FragPos;
out vec4 fragColor;
//Zmienna wyjœciowa dla koloru fragmentu

uniform vec3 lightColor;
uniform vec3 viewPosition;
uniform float currentTime;

//Directional light 
uniform vec3 directionalLightDirection;
uniform float animatedIntensity;

//Point light
uniform vec3 pointLightPosition;

//Spotlight 
uniform vec3 spotColors;
uniform vec3 spotLightPosition;
uniform vec3 spotLightDirection;
uniform float lightCutOff;
uniform float outerLightCutOff;

//textures and materials
uniform bool shouldUseDiffuseTexture;
uniform bool shouldReflect;
uniform bool shouldRefract;
uniform sampler2D diffuse0;
uniform vec3 diffuseColor;

//uniform sampler2D specular0;
uniform vec3 mambient;
uniform vec3 mdiffuse;
uniform vec3 mspecular;
uniform float mshininess;
uniform mat3 normalTransform;
uniform samplerCube skybox;

const float ATTENUATION_LINEAR = 0.09f;
const float ATTENUATION_QUADRATIC = 0.032f;

vec4 getTexel();
vec3 getDirectionalLight(vec3 viewDirection, vec3 normals);
vec3 getPointLight(vec3 viewDirection, vec3 normals);
vec3 getSpotLight(vec3 viewDirection, vec3 normals);
vec3 countSpecular(vec3 viewDirection, vec3 lightDirection, vec3 normals);
float countAttenuation(vec3 lightDirection);

void main()
{
	vec3 normals = normalize(normalTransform*Normal);
	vec3 viewDirection = normalize(viewPosition - FragPos);

	vec3 directionalLight = getDirectionalLight(viewDirection, normals);
	vec3 pointLight = getPointLight(viewDirection, normals);
	vec3 spotLight = getSpotLight(viewDirection, normals);

	vec3 lights = directionalLight +pointLight + spotLight;

	fragColor = getTexel() * vec4(lights, 1.0);
}

vec4 getTexel()
{
	if(shouldRefract)
	{
		float ratio = 1.0 / 1.05;
		vec3 I = normalize(FragPos - viewPosition);
		vec3 R = refract(I, normalize(Normal), ratio);
		return vec4(texture(skybox, R).rgb, 1.0);// texture(diffuse0, fragVertexTexture);//
		//return vec4(diffuseColor, 1);
	}
	else if (shouldReflect)
	{
		vec3 I = normalize(FragPos - viewPosition);
		vec3 R = reflect(I, normalize(Normal));
		return vec4(texture(skybox, R).rgb, 1.0);
	}
	else {
		return vec4(diffuseColor, 1);
	}
}

vec3 getDirectionalLight(vec3 viewDirection, vec3 normals)
{
	vec3 lightDirection = normalize(-directionalLightDirection);
	float diff = max(dot(normals, lightDirection), 0.0);

	vec3 ambient = mambient * lightColor * vec3(0.7) * animatedIntensity;
	vec3 diffuse = mdiffuse * lightColor * diff * vec3(0.9) * animatedIntensity;
	vec3 specular = countSpecular(viewDirection, lightDirection, normals);

	return  ambient + diffuse + specular;
}


vec3 getSpotLight(vec3 viewDirection, vec3 normals)
{
	vec3 lightDirection = normalize(spotLightPosition - FragPos);
	float diff = max(dot(normals, lightDirection), 0.0);

	float theta = dot(lightDirection, normalize(-spotLightDirection));
	float epsilon = lightCutOff - outerLightCutOff;
	float intensity = clamp((theta - outerLightCutOff) / epsilon, 0.0, 1.0);
	intensity *= 3;

	float attenuation = countAttenuation(spotLightPosition);

	vec3 diffuse = mdiffuse * spotColors * vec3(0.8f) * diff * intensity * attenuation;
	vec3 specular = countSpecular(viewDirection, lightDirection, normals) * attenuation * intensity;
	//vec3 ambient =   mambient * spotColors * vec3(1.2f) * attenuation;

	return diffuse + specular;
}


vec3 getPointLight(vec3 viewDirection, vec3 normals)
{
	vec3 lightDirection = normalize(pointLightPosition - FragPos);
	float diff = max(dot(normals, lightDirection), 0.0);

	float attenuation = countAttenuation(pointLightPosition);

	vec3 diffuse = mdiffuse * lightColor * vec3(0.8f) * diff *  attenuation;
	vec3 ambient = mambient * lightColor * vec3(0.7f) * attenuation;
	vec3 specular = countSpecular(viewDirection, lightDirection, normals) * attenuation;

	return ambient + diffuse + specular;
}

vec3 countSpecular(vec3 viewDirection, vec3 lightDirection, vec3 normals)
{
	vec3 reflectDirection = reflect(-lightDirection, normals);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), mshininess);
	return mspecular * vec3(1.0f, 1.0f, 1.0f) * spec;
}

float countAttenuation(vec3 lightDirection)
{
	float distance = length(lightDirection - FragPos);
	return 1.0 / (1.0 + ATTENUATION_LINEAR * distance + ATTENUATION_QUADRATIC * (distance * distance));
}




