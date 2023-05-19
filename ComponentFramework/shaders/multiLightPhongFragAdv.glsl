#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 fragColor;

layout(location = 0) in vec3 vertNormal;
layout(location = 1) in vec3 eyeDir; 
layout(location = 2) in vec3 lightDir0;
layout(location = 3) in vec3 lightDir1;


void main() 
{
    vec4 ks0 = vec4(0.6, 0.0, 0.0, 0.0);
	vec4 ks1 = vec4(0.0, 0.6, 0.0, 0.0);

	vec4 kd0 = vec4(0.6, 0.2, 0.2, 0.0);
	vec4 kd1 = vec4(0.2, 0.6, 0.2, 0.0);

	vec4 ka0 = 0.1 * kd0;
	vec4 ka1 = 0.1 * kd1;
	vec4 ka = ka0;
	
	float diff0 = max(dot(vertNormal, lightDir0), 0.0);
	float diff1 = max(dot(vertNormal, lightDir1), 0.0);

	/// Reflection is based incedent which means a vector from the light source
	/// not the direction to the light source
	vec3 reflection0 = normalize(reflect(-lightDir0, vertNormal));
	vec3 reflection1 = normalize(reflect(-lightDir1, vertNormal));

	float spec0 = max(dot(eyeDir, reflection0), 0.0);
	if(diff0 > 0.0)
	{
		spec0 = pow(spec0,14.0);
	}

	float spec1 = max(dot(eyeDir, reflection1), 0.0);
	if(diff1 > 0.0)
	{
		spec1 = pow(spec1,14.0);
	}

	//fragColor =  ka0 + (diff * kd) + (spec * ks);	

	fragColor =  ka0 + ka1 + ((diff0 * kd0) + (spec0 * ks0 )) + ((diff1 * kd1) + (spec1 * ks1));
	
}