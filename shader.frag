uniform sampler2D texture;
uniform vec4 inputColor; 

vec4 sqr(vec4 a)
{
    return a * a;
}

void main() 
{
    vec2 uv = gl_TexCoord[0].xy;
    vec4 texColor = texture2D(texture, uv);

    gl_FragColor = sqr((sqrt(inputColor) + sqrt(texColor)) * 0.5);
}