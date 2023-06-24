#version 450
#extension GL_ARB_separate_shader_objects : enable

uniform samplerCube skyboxTexture;

layout(location = 0) in vec3 texCoords;
layout(location = 0) out vec4 fragColor;

void main() {
    fragColor = texture(skyboxTexture, texCoords);
}