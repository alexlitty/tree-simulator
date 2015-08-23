uniform float alpha;

void main()
{
    vec4 col = gl_Color;
    col.w = col.w * alpha;
    gl_FrontColor = col;

    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
}
