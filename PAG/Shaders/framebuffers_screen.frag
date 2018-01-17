#version 410 core
out vec4 FragColor;

in vec2 TexCoords;

uniform bool useNightVision;
uniform sampler2D screenTexture;
uniform sampler2D noiseTex;
uniform float elapsedTime; // seconds for noise effect
uniform sampler2D hdrBuffer;
uniform bool hdr;
uniform float exposure;

void main()
{
	vec3 result = vec3(1.0, 1.0, 1.0);
    if(hdr)
    {
		const float gamma = 2.2;
		vec3 hdrColor = texture(hdrBuffer, TexCoords).rgb;
        // reinhard
        // result = hdrColor / (hdrColor + vec3(1.0));
        // exposure
         result = vec3(1.0) - exp(-hdrColor * exposure);
        // gamma correction
        result = pow(result, vec3(1.0 / gamma));
        //FragColor = vec4(result, 1.0);
    }

	//FragColor = mix(texture(screenTexture, TexCoords), texture(noiseTex, TexCoords), 0.5);
	//FragColor = texture(screenTexture, TexCoords);
	if (useNightVision) {
		vec2 uv;
		uv.x = 0.35*sin(elapsedTime*50.0);
		uv.y = 0.35*cos(elapsedTime*50.0);
		vec3 noise = texture(noiseTex, TexCoords.st + uv).rgb;
		vec3 sceneColor = texture(screenTexture, TexCoords.st + (noise.xy*0.005)).rgb;
		const vec3 lumvec = vec3(0.30, 0.59, 0.11);
		float intentisy = dot(lumvec, sceneColor);
		intentisy = clamp(0.5 * (intentisy - 0.5) + 0.5, 0.0, 1.0);
		float green = clamp(intentisy / 0.59, 0.0, 1.0);

		vec3 visionColor = vec3(0, green, 0);

		FragColor = vec4((sceneColor + (noise*0.2)) * visionColor * result, 1); //

	}
	else {
		if(hdr)
		{
			FragColor = vec4(result, 1.0);
		}
		else 
		{
			FragColor = texture(screenTexture, TexCoords);
		}
	}
	
}
