#shader vertex
##version 330 core

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColor;

out VertexData{ vec4 color; } outData;
out gl_PerVertex{ vec4 gl_Position; };

uniform mat4 modelViewTransform;

void main() {
    gl_Position = modelViewTransform * vec4(inPosition, 0.0, 1.0);
    outData.color = vec4(inColor, 1.0);
};

#shader fragment
#version 330 core

in FragmentData{
    vec4 color;
    vec2 texCoord;
} inData;

layout(location = 0) out vec4 fColor;

uniform sampler2D alpha;
uniform sampler2D diffuse;

void main() {
    vec4 alphaValue = texture(alpha, inData.texCoord);
    vec4 diffuseValue = texture(diffuse, inData.texCoord);
    fColor = inData.color * alphaValue * 0.99 + inData.color * diffuseValue * 0.01;
};

#shader geometry
#version 330 core

layout(points) in;
layout(triangle_strip) out;
layout(max_vertices = 4) out;

in VertexData{ vec4 color; } inData[];
in gl_PerVertex{ vec4 gl_Position; } gl_in[];

out FragmentData{
    vec4 color;
    vec2 texCoord;
} outData;

uniform float radius;
uniform float windowRatio;

void main() {

    gl_Position = gl_in[0].gl_Position + vec4(-radius / windowRatio, radius, 0.0, 0.0);
    outData.color = inData[0].color;
    outData.texCoord = vec2(0.0, 1.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(-radius / windowRatio, -radius, 0.0, 0.0);
    outData.color = inData[0].color;
    outData.texCoord = vec2(0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(radius / windowRatio, radius, 0.0, 0.0);
    outData.color = inData[0].color;
    outData.texCoord = vec2(1.0, 1.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(radius / windowRatio, -radius, 0.0, 0.0);
    outData.color = inData[0].color;
    outData.texCoord = vec2(1.0, 0.0);
    EmitVertex();

    EndPrimitive();
};