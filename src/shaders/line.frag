#version 330 core
out vec4 FragColor;
in vec3 FragPos;
uniform vec4 color = vec4(1.0, 0.5, 0.0, 1.0);
void main() {
  FragColor = color;
}