#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 fragColor;
layout(location = 0) in vec3 vertNormal;
layout(location = 1) in vec3 eyeDir;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 lightDir[9];
layout(location = 13) in vec4 diffuseFrag[9];
layout(location = 23) in vec4 specularFrag[9];

uniform sampler2D myTexture;

void main() {

	vec4 kTexture = texture(myTexture, texCoord);
	vec4 ka = 0.01 * kTexture;

	float diff[9];
	vec3 reflection[9];
	float spec[9];

	for(int i = 0; i <= lightDir.length - 1; i++)
	{
		diff[i] = max(dot(vertNormal, lightDir[i]), 0.0);
		reflection[i] = normalize(reflect(-lightDir[i], vertNormal));
		spec[i] = max(dot(eyeDir, reflection[i]), 0.0);
		spec[i] = pow(spec[i], 14.0);
	}

	fragColor = ka;
	for (int j = 0; j <= lightDir.length - 1; j++)
	{
		fragColor += (diff[j] * kTexture * diffuseFrag[j]) + (spec[j] * specularFrag[j]);
	}

}