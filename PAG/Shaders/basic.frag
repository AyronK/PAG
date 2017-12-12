#version 330 core 

in vec2 fragVertexTexture; //Zmienna wspó³rzêdnych tekstury z vertex shadera
smooth in vec3 Normal;  
in vec3 FragPos;

out vec4 fragColor; //Zmienna wyjœciowa dla koloru fragmentu


//all lights
uniform vec3 lightColor;
uniform vec3 viewPosition;
uniform float currentTime;

//Directional light 
uniform vec3 directionalColors;
uniform vec3 lightDirection;

//Point light
uniform vec3 pointLightPosition;

//Spotlight 
uniform vec3 spotLightPosition;
uniform vec3 spotLightDirection;
uniform float lightCutOff;
uniform float outerLightCutOff;

//textures and materials
uniform bool shouldUseDiffuseTexture;
uniform sampler2D diffuse0;
uniform vec3 diffuseColor;
//uniform sampler2D specular0;
uniform vec3 mambient;
uniform vec3 mdiffuse;
uniform vec3 mspecular;
uniform float mshininess;

uniform mat3 normalTransform;

void main()
{
	// DIRECTIONAL LIGHT
	// zmiana koloru w czasie
		// dlambient
	vec3 dlambient = mambient * directionalColors * vec3(0.2);
		// dldiffuse
	vec3 norm = normalize(normalTransform*Normal);
	vec3 lightDir = normalize(-lightDirection);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 dldiffuse = mdiffuse * directionalColors * diff * vec3(0.5);
		// dlspecular
	vec3 viewDir = normalize(viewPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mshininess);
	vec3 dlspecular = mspecular * vec3(1.0f, 1.0f, 1.0f) * spec;

	vec3 directionalLight = dlambient + dldiffuse + dlspecular;

	
	// POINT LIGHT
	// przemieszczanie w czasie
	float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
	// attenuation
    float distance = length(pointLightPosition - FragPos);
    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance)); 	  
		// plambient	
	vec3 plambient = mambient *  lightColor * vec3(0.8f) * vec3(0.9f) * attenuation; 
		// pldiffuse
	lightDir = normalize(pointLightPosition - FragPos);  
	diff = max(dot(norm, lightDir), 0.0);
	vec3 pldiffuse = mdiffuse * lightColor * vec3(0.8f) * diff *  attenuation; 
		// plspecular
    reflectDir = reflect(-lightDir, norm);  
    spec = pow(max(dot(viewDir, reflectDir), 0.0), mshininess);
	vec3 plspecular = mspecular *  vec3(1.0f, 1.0f, 1.0f) * spec * attenuation;

	vec3 pointLight = plambient + pldiffuse + plspecular;


	
	// SPOTLIGHT
	// zmiana intensywnosci w czasie
	lightDir = normalize(spotLightPosition - FragPos);  
	float theta = dot(lightDir, normalize(-spotLightDirection));
    float epsilon   = lightCutOff - outerLightCutOff;
	float intensity = clamp((theta - outerLightCutOff) / epsilon, 0.0, 1.0);   
	intensity = 2 * intensity + 3*sin(currentTime);	 
	// attenuation
    distance = length(spotLightPosition - FragPos);
    attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance)); 	
		// slambient	
	vec3 slambient =   mambient * lightColor * vec3(1.2f) * attenuation; 
		// sldiffuse
	diff = max(dot(norm, lightDir), 0.0);
	vec3 sldiffuse =   mdiffuse * lightColor * vec3(0.8f) * diff * intensity * attenuation;
		// slspecular
	reflectDir = reflect(-lightDir, norm);
	spec = pow(max(dot(viewDir, reflectDir), 0.0), mshininess); 
	vec3 slspecular =  vec3(1.0f, 1.0f, 1.0f) * spec * intensity * attenuation;   
	
	vec3 spotLight = slambient + sldiffuse + slspecular;



	vec3 lights = directionalLight + pointLight + spotLight;
	//vec3 lights = directionalLight;

	//vec3 lights = pointLight + spotLight;

	vec4 texel0;
	texel0=texture(diffuse0, fragVertexTexture);
	if (shouldUseDiffuseTexture)
		fragColor=texel0 * vec4(lights, 1.0);
	else
		fragColor=vec4(diffuseColor,1) * vec4(lights, 1.0);

	//fragColor=vec4(normalize(normalTransform*Normal),1);
}




