#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec4 vVertex;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 uvCoord;

const int MAX_LIGHTS = 10;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform int numLights = 2;

uniform vec3 lightPos[MAX_LIGHTS];

layout(location = 0) out vec3 vertNormal;
layout(location = 1) out vec3 eyeDir; 
layout(location = 2) out vec3 lightDir[MAX_LIGHTS];



void main() 
{
    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
    vertNormal = normalize(normalMatrix * vNormal); /// Rotate the normal to the correct orientation 
    vec3 vertPos = vec3(viewMatrix * modelMatrix * vVertex);
    vec3 vertDir = normalize(vertPos);
    eyeDir = -vertDir;
    //lightDir[0] = normalize(vec3(lightPos[0]) - vertPos); 
    //lightDir[1] = normalize(vec3(lightPos[1]) - vertPos);

    for (int i = 0; i < numLights; i++)

    {
        lightDir[i] = normalize(lightPos[i]  + (-vertPos));
    }

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vVertex;
    
}
