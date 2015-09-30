#version 330 core

layout (location = 0) out vec4 out_Color;

uniform vec2 light;

in DATA{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
}fs_in;

uniform sampler2D textures[32];

void main()
{
	float intensity = 1.0 / length(fs_in.position.xy - light);
	vec4 color = fs_in.color;
	if(fs_in.tid > 0.0){
		int tid = int(fs_in.tid - 0.5);
		vec4 textureColor;
		switch(tid){
			case 0: textureColor = texture(textures[0], fs_in.uv); break;
			case 1: textureColor = texture(textures[1], fs_in.uv); break;
			case 2: textureColor = texture(textures[2], fs_in.uv); break;
			case 3: textureColor = texture(textures[3], fs_in.uv); break;
			case 4: textureColor = texture(textures[4], fs_in.uv); break;
			case 5: textureColor = texture(textures[5], fs_in.uv); break;
			case 6: textureColor = texture(textures[6], fs_in.uv); break;
			case 7: textureColor = texture(textures[7], fs_in.uv); break;
			case 8: textureColor = texture(textures[8], fs_in.uv); break;
			case 9: textureColor = texture(textures[9], fs_in.uv); break;
			case 10: textureColor = texture(textures[10], fs_in.uv); break;
			case 11: textureColor = texture(textures[11], fs_in.uv); break;
			case 12: textureColor = texture(textures[12], fs_in.uv); break;
			case 13: textureColor = texture(textures[13], fs_in.uv); break;
			case 14: textureColor = texture(textures[14], fs_in.uv); break;
			case 15: textureColor = texture(textures[15], fs_in.uv); break;
			case 16: textureColor = texture(textures[16], fs_in.uv); break;
			case 17: textureColor = texture(textures[17], fs_in.uv); break;
			case 18: textureColor = texture(textures[18], fs_in.uv); break;
			case 19: textureColor = texture(textures[19], fs_in.uv); break;
			case 20: textureColor = texture(textures[20], fs_in.uv); break;
			case 21: textureColor = texture(textures[21], fs_in.uv); break;
			case 22: textureColor = texture(textures[22], fs_in.uv); break;
			case 23: textureColor = texture(textures[23], fs_in.uv); break;
			case 24: textureColor = texture(textures[24], fs_in.uv); break;
			case 25: textureColor = texture(textures[25], fs_in.uv); break;
			case 26: textureColor = texture(textures[26], fs_in.uv); break;
			case 27: textureColor = texture(textures[27], fs_in.uv); break;
			case 28: textureColor = texture(textures[28], fs_in.uv); break;
			case 29: textureColor = texture(textures[29], fs_in.uv); break;
			case 30: textureColor = texture(textures[30], fs_in.uv); break;
			case 31: textureColor = texture(textures[31], fs_in.uv); break;
		}
		color = fs_in.color * textureColor;
	}
	out_Color = color; // * intensity;
}