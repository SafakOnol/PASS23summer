#version 450
#extension GL_ARB_separate_shader_objects : enable

// Attributes 
layout(location = 0) in vec4 vVertex;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 uvCoord;

// uniform variables
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 lightPos[9];
uniform vec4 diffuse[9];
uniform vec4 specular[9];

// set vector locations
layout(location = 0) out vec3 vertNormal;
layout(location = 1) out vec3 eyeDir;
layout(location = 2) out vec2 texCoord;
layout(location = 3) out vec3 lightDir[9];
layout(location = 13) out vec4 diffuseFrag[9];
layout(location = 23) out vec4 specularFrag[9];

// apply values
void main() {

    for (int x = 0; x < diffuse.length; x++)
    {
        diffuseFrag[x] = diffuse[x];
        specularFrag[x] = specular[x];
    }


    texCoord = uvCoord;
    texCoord.y *= -1.0;
    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix))); // Inverse & Transpose to generate normalMatrix for light
    vertNormal = normalize(normalMatrix * vNormal); // Rotate the normal to the correct orientation

    vec3 vertPos = vec3(viewMatrix * modelMatrix * vVertex); // get vertex position from matrices
    vec3 vertDir = normalize(vertPos); // get vertex direction
    eyeDir = -vertDir; // eye direction is the negative vertex direction

    for (int li = 0; li < lightDir.length; li++)
    {
        lightDir[li] = normalize(lightPos[li] - vertPos);
    }

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vVertex;
}