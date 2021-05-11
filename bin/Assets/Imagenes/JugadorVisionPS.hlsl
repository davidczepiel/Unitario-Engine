sampler RT : register(s0);
float strength;
uniform float Time;

struct VS_OUTPUT {
   float4 pos: POSITION;
   float2 texCoord0: TEXCOORD0;
};

// //returns number between -1 and 1
float random(float2 uv)
{
    return frac(sin(dot(uv,float2(12.9898,78.233)))*43758.5453123);
}

float4 ps_main( VS_OUTPUT input ): COLOR0
{
    float incS = (10. * strength) / 1920;
    float incT = (10. * strength) / 1080;

    // incrementos para acceder a los 9 pixeles vecinos
    float2 incUV[9] = {
        float2(-incS, incT), // top‐left
        float2(0, incT) , // top‐center
        float2(incS, incT) , // top‐right
        float2(-incS, 0) , // center‐left
        float2(0, 0) , // center‐center
        float2(incS, 0) , // center‐right
        float2(-incS, -incT) , // bottom‐left
        float2(0, -incT) , // bottom‐center
        float2(incS, -incT) // bottom‐right
    };

    if(strength < 0) strength = 0;
    else if(strength > 1) strength = 1;

    //number between 0 and 8
    int randomCell = (int)((random(float2(input.texCoord0.x * input.texCoord0.y, Time)) + 1) * 4);

    float4 color = tex2D(RT, input.texCoord0.xy) * (1 - strength);
    color += tex2D(RT, (input.texCoord0.xy + incUV[randomCell])) * strength;

    color[3] = 1.0f;

    return color;
}
