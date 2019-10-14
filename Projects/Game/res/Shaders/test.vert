varying out vec4 fragPos;

void main()
{
    // transform the vertex position
    fragPos = gl_Vertex;
    gl_Position = gl_ModelViewProjectionMatrix * fragPos;

    // transform the texture coordinates
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // forward the vertex color
    gl_FrontColor = gl_Color;
}