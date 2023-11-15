#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec2 texCoord;

uniform sampler2D tex0;
uniform vec4 color;

void main() {
    FragColor = texture(tex0, texCoord) * color;
}
