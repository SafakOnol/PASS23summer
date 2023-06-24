#version 450
#extension GL_ARB_separate_shader_objects : enable

// Attributes 
layout (location = 0) in vec4 vVertex;
layout (location = 1) in vec3 vNormal;

layout (location = 0) uniform mat4 viewMatrix;
layout (location = 1) uniform mat4 projectionMatrix;
layout (location = 2) uniform mat4 modelMatrix;
// layout (location = 3) uniform mat3 normalMatrix; TODO! -> carry it to CPU

layout (location = 0) out vec3 vertNormal;
layout (location = 1) out vec3 vertDir; // vector I from the website



void main() {

    mat4 m = transpose(inverse(modelMatrix)); 
    mat3 normalMatrix = mat3(m);
    vertNormal = normalMatrix * vNormal;
    vertNormal = normalize(vertNormal);

    vec3 vertPos = vec3(viewMatrix * modelMatrix * vVertex);
    vertDir = normalize(vertPos); 
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vVertex;

}