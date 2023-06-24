#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 vertNormal;
layout(location = 1) in vec3 vertDir;

uniform samplerCube skyboxTexture;

layout(location = 0) out vec4 fragColor;

void main() {	

	vec3 reflectionVector = reflect(vertDir, vertNormal);

	//fragColor = vec4(1.0, 0.0, 0.0, 0.0);

	vec4 fragColorReflect = texture(skyboxTexture, reflectionVector);

	// complete it for the assignment
	// do the reflection vector

	float refractionRatio = 1.00 / 1.52; // air to glass
	vec3 refractionVector = refract(vertDir, vertNormal, refractionRatio);

	vec4 fragColorRefract = texture(skyboxTexture, refractionVector);

	fragColor = mix(fragColorReflect, fragColorRefract, dot(-vertDir, vertNormal));

	// look for the refraction vector

	// understand the calculations thoroghly! go figure

}