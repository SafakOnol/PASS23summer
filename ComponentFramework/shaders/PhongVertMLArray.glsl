#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec4 vVertex;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 uvCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 lightPos[2];

layout(location = 0) out vec3 vertNormal;
layout(location = 1) out vec3 eyeDir; 
layout(location = 2) out vec3 lightDir[2];



void main() 
{
    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
    vertNormal = normalize(normalMatrix * vNormal); /// Rotate the normal to the correct orientation 
    vec3 vertPos = vec3(viewMatrix * modelMatrix * vVertex);
    vec3 vertDir = normalize(vertPos);
    eyeDir = -vertDir;
    lightDir[0] = normalize(vec3(lightPos[0]) - vertPos); 
    lightDir[1] = normalize(vec3(lightPos[1]) - vertPos);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vVertex;
    
}
