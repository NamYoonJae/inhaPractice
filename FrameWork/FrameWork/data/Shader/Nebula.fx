float4x4 WorldITXf : WorldInverseTranspose;
float4x4 WvpXf : WorldViewProjection;
float4x4 WorldXf : World;
float4x4 ViewITXf : ViewInverseTranspose;
float4x4 ViewIXf;
float4x4 WorldViewXf;

float Scale
<
   string UIName = "Scale";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = 0.00;
   float UIMax = 2.00;
> = float( 0.00 );
float4x4 NebXf
<
   string UIName = "NebXf";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
> = float4x4( 2.00, -2.00, -2.00, 0.00, -2.00, -2.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 1.00 );
struct VS_INPUT 
{
    float3 Position    : POSITION;
    float4 UV        : TEXCOORD0;
    float4 Normal    : NORMAL;
    float4 Tangent    : TANGENT0;
    float4 Binormal    : BINORMAL0;
   
};

struct VS_OUTPUT 
{
    float4 HPosition    : POSITION;
    float2 UV    : TEXCOORD0;
    float3 WorldNormal    : TEXCOORD1;
    float3 WorldEyeVec    : TEXCOORD2;
    float3 WorldTangent    : TEXCOORD3;
    float3 WorldBinorm    : TEXCOORD4;
    float4 NebCoords    : TEXCOORD5;
   
};

VS_OUTPUT VS( VS_INPUT Input )
{
   VS_OUTPUT OUT = (VS_OUTPUT)0;
    OUT.WorldNormal = mul(Input.Normal,WorldITXf).xyz;
    OUT.WorldTangent = mul(Input.Tangent,WorldITXf).xyz;
    OUT.WorldBinorm = mul(Input.Binormal,WorldITXf).xyz;
    float4 Po = float4(Input.Position.xyz,1.0);
    float4 Pw = mul(Po,WorldXf);
    float4 Pu = mul(Pw,NebXf);   // P in "user coords"
    // OUT.LightVec = (LightPos - Pw.xyz);
    OUT.UV = Input.UV.xy;
    OUT.WorldEyeVec = normalize(ViewITXf[3].xyz - Pw.xyz);
    OUT.HPosition = mul(Po,WvpXf);
    OUT.NebCoords = float4((Scale*Pu.xyz)+float3(0.5,0.5,0.5),1.0);
    return OUT;
   
}




texture nebTexture_Tex;
sampler2D nebSamp = sampler_state
{
   Texture = (nebTexture_Tex);
};

struct PS_INPUT 
{
    float4 HPosition    : POSITION;
    float2 UV    : TEXCOORD0;
    float3 WorldNormal    : TEXCOORD1;
    float3 WorldEyeVec    : TEXCOORD2;
    float3 WorldTangent    : TEXCOORD3;
    float3 WorldBinorm    : TEXCOORD4;
    float4 NebCoords    : TEXCOORD5;
   
};

float4 PS(PS_INPUT Input) : COLOR0
{   
   float4 nc = tex2D(nebSamp,Input.NebCoords.xy);
   float4 na = tex2D(nebSamp,Input.NebCoords.xz);
   float4 result = nc * na.w;
   return float4(result.rgb,1.0);
}




//--------------------------------------------------------------//
// Technique Section for Nebula
//--------------------------------------------------------------//
technique Nebula
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 VS();
      PixelShader = compile ps_2_0 PS();
   }

}

