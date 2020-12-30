
//--------------------------------------------------------------//
// SpecularMapping
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//

float4x4 gWorldMatrix : World;
float4x4 gWorldViewProjectionMatrix : WorldViewProjection;

float4 gWorldLightPos
<
	string UIName = "gWorldLightPos";
	string UIWidget = "Direction";
	bool UIVisible = false;
	float4 UIMin = float4(-10.00, -10.00, -10.00, -10.00);
	float4 UIMax = float4(10.00, 10.00, 10.00, 10.00);
	bool Normalize = false;
> = float4( 500.00, 500.00, -500.00, 1.00 );

float4 gWorldCameraPos : ViewPosition;

struct VS_INPUT 
{
   float4 mPosition : POSITION;
   float3 mNormal   : NORMAL;
   float2 mUV       : TEXCOORD0;
   
};

struct VS_OUTPUT 
{
   float4 mPosition   : POSITION;
   float2 mUV         : TEXCOORD0;
   float3 mDiffuse    : TEXCOORD1;
   float3 mViewDir    : TEXCOORD2;
   float3 mReflection : TEXCOORD3;
};

VS_OUTPUT VS( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.mPosition = mul( Input.mPosition, gWorldViewProjectionMatrix);
   Output.mUV = Input.mUV;

   float3 lightDir = Output.mPosition.xyz - gWorldLightPos.xyz;
   lightDir = normalize(lightDir);
   
   float3 viewDir = normalize(Output.mPosition.xyz - gWorldCameraPos.xyz);
   Output.mViewDir = viewDir;
   
   float3  worldNormal = mul(Input.mNormal, (float3x3)gWorldMatrix);
   worldNormal = normalize(worldNormal);
   
   Output.mDiffuse = dot(-lightDir, worldNormal);
   Output.mReflection = reflect(lightDir, worldNormal);
   
   return( Output );
   
}


struct PS_INPUT
{
   float2 mUV         : TEXCOORD0;
   float3 mDiffuse    : TEXCOORD1;
   float3 mViewDir    : TEXCOORD2;
   float3 mReflection : TEXCOORD3;
};


texture DiffuseMap_Tex;
sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseMap_Tex);
};

texture SpecularMap_Tex;
sampler2D SpecularSampler = sampler_state
{
   Texture = (SpecularMap_Tex);
};

float3 gLightColor
<
	string UIName = "gLightColor";
	string UIWidget = "Numeric";
	bool UIVisible = false;
	float UIMin = -1.00;
	float UIMax = 1.00;
> = float3(0.7f, 0.7f, 1.0f);

float4 PS(PS_INPUT Input) : COLOR
{   
   float4 albedo = tex2D(DiffuseSampler, Input.mUV);
   

   float3 diffuse = gLightColor * albedo.rgb * saturate(Input.mDiffuse);
   float3 reflection = normalize(Input.mReflection);
   float3 viewDir = normalize(Input.mViewDir);
   float3 specular = 0;
   if(diffuse.x > 0)
   {
      specular = saturate(dot(reflection, - viewDir));
      specular = pow(specular, 20.0f);
      
      float4 specularIntensity = tex2D(SpecularSampler, Input.mUV);
      specular *= specularIntensity.rgb * gLightColor.rgb;
   }
   float3 ambient = float3(0.02f, 0.02f, 0.02f);
   
   return saturate(float4(ambient + diffuse + specular, 1.0f ));
}




//--------------------------------------------------------------//
// Technique Section for SpecularMapping
//--------------------------------------------------------------//
technique SpecularMapping
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 VS();
      PixelShader = compile ps_2_0 PS();
   }

}

