#version 330 core

layout(location = 0) in vec3 vertexPosition;

 uniform mat4 MVP;
 uniform float angle;

void main(){
	float angleRad = radians(angle);

	vec4 oldPosition = MVP * vec4(vertexPosition, 1);
    vec4 newPosition = oldPosition;
    newPosition.x = oldPosition.x * cos(angleRad) - oldPosition.y * sin(angleRad);
    newPosition.y = oldPosition.x * sin(angleRad) + oldPosition.y * cos(angleRad);
	gl_Position = newPosition;

 }