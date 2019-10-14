uniform sampler2D texture; 

in vec4 fragPos;

void main()
{
    vec2 uv = gl_TexCoord[0].xy;

    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, uv);

    vec3 index = fragPos.xyz;
    // multiply it by the color
    gl_FragColor = gl_Color * pixel + vec4(uv, 0.0, 1.0)*0.0001;
}