#shader vertex
#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 color;
in layout(location = 2) vec2 texCoord;

uniform mat4 MVP;

out vec3 u_Color;
out vec2 u_TexCoord;

void main()
{
	gl_Position = MVP * vec4(position, 1.0);
	u_Color = color;
	u_TexCoord = texCoord;
}

#shader fragment
#version 430

out vec4 color;
in vec3 u_Color;
in vec2 u_TexCoord;

uniform sampler2D tex;

void main()
{
	color = texture(tex, u_TexCoord);
}