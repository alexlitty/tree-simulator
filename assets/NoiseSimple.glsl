float noise(vec2 n)
{
    return fract(sin(dot(n.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
    float v = noise(gl_FragCoord.xy);
    gl_FragColor = vec4(v, v, v, 1);
}
