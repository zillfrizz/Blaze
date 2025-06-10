#version 450

// HARDCODED
const mat3 ROTATIONS[6] = mat3[6](
    mat3( vec3( 0, 0, -1), vec3(0, 1, 0), vec3(1, 0, 0)),  // +X
    mat3( vec3( 0, 0,  1), vec3(0, 1, 0), vec3(-1, 0, 0)), // -X
    mat3( vec3( 1, 0,  0), vec3(0, 0, -1), vec3(0, 1, 0)), // +Y
    mat3( vec3( 1, 0,  0), vec3(0, 0,  1), vec3(0, -1, 0)),// -Y
    mat3( vec3( 1, 0,  0), vec3(0, 1, 0), vec3(0, 0, 1)),  // +Z
    mat3( vec3(-1, 0,  0), vec3(0, -1, 0), vec3(0, 0, -1)) // -Z
);

// VERTEX RATE
layout (location = 0) in uvec2 uv; 

//  INSTANCE RATE
layout (location = 1) in uvec3 position;
layout (location = 2) in uvec2 size;
layout (location = 3) in uint rotation;
layout (location = 4) in uint texId;
layout (location = 5) in uint light;

// OUTPUT
layout(location = 0) out uvec2 o_uv;
layout(location = 1) flat out uint o_texId;
layout(location = 2) flat out uint o_light;


void main(){
    vec3 pos = vec3(position);
    vec3 scaled = vec3(uv*size, 0);
    o_uv = uv.xy;
    o_texId = texId;
    o_light = light;
    gl_Position = vec4(ROTATIONS[rotation] * scaled + pos, 1.0);
}