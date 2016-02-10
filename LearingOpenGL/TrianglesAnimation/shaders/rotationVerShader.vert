#version 330

in vec4 vPosition;

uniform vec3 theta;
uniform vec3 center;

void main()
{
	// Compute the sines and cosines of theta for each of
	// the three axes in one computation.
	vec3 angles = radians( theta );
	vec3 c = cos( angles );
	vec3 s = sin( angles );
		

	//these matrices are column-major
	mat4 rx = mat4( 
	1.0, 0.0, 0.0, 0.0,
	0.0, c.x, -s.x, 0.0,
	0.0, s.x, c.x, 0.0,
	0.0, 0.0, 0.0, 1.0 );

	mat4 ry = mat4( 
	c.y, 0.0, s.y, 0.0,
	0.0, 1.0, 0.0, 0.0,
	-s.y, 0.0, c.y, 0.0,
	0.0, 0.0, 0.0, 1.0 );

	mat4 rz = mat4(
	c.z, -s.z, 0.0, 0.0,
	s.z, c.z, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0 );

		
	mat4 t1 = mat4(
	1.0, 0.0, 0.0, 0.667,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0 );

	mat4 t2 = mat4(
	1.0, 0.0, 0.0, -0.667,
	0.0, 1.0, 0.0, -1.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0 );


	//gl_Position =  vPosition *t1* rx * ry * rz * t2 ;
	gl_Position =  vPosition * rx * ry * rz;
	//gl_Position = vPosition * t1;
}