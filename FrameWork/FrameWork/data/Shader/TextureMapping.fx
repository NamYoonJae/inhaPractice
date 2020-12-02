//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// TextureMapping
//--------------------------------------------------------------//

float4x4 gWorldMatrix : World;
float4x4 gViewMatrix : View;
float4x4 gProjectionMatrix : Projection;

struct VS_INPUT
{
   float4 mPosition : POSITION;
   float2 mTexCoord : TEXCOORD0;
};

struct VS_OUTPUT
{
   float4 mPosition : POSITION;
   float2 mTexCoord : TEXCOORD0;
};

VS_OUTPUT VS(VS_INPUT Input)
{
   VS_OUTPUT Output;
   
   Output.mPosition = mul(Input.mPosition, gWorldMatrix);
   Output.mPosition = mul(Output.mPosition, gViewMatrix);
   Output.mPosition = mul(Output.mPosition, gProjectionMatrix);
   
   Output.mTexCoord = Input.mTexCoord;
   
   return Output;
}

texture DiffuseMap_Tex;

sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseMap_Tex);
};

struct PS_INPUT
{
   float2 mTexCoord : TEXCOORD0;
};

float4 PS( PS_INPUT Input ) : COLOR
{
   float4 albedo = tex2D(DiffuseSampler, Input.mTexCoord);
   
   if(0.24f < Input.mTexCoord.y && Input.mTexCoord.y < 0.25f)
      albedo = 1;
   else if(0.49f < Input.mTexCoord.y && Input.mTexCoord.y < 0.50f)
      albedo = float4(1, 0, 0, 1);
   else if(0.74f < Input.mTexCoord.y && Input.mTexCoord.y < 0.75f)
      albedo = 1;
      
   if(0.24f < Input.mTexCoord.x && Input.mTexCoord.x < 0.25f)
      albedo = 1;
   else if(0.49f < Input.mTexCoord.x && Input.mTexCoord.x < 0.50f)
      albedo = 1;
   else if(0.74f < Input.mTexCoord.x && Input.mTexCoord.x < 0.75f)
      albedo = 1;
   else if(0.99f < Input.mTexCoord.x && Input.mTexCoord.x < 1.0f)
      albedo = 1;
      
   return albedo.rgba;
}

//--------------------------------------------------------------//
// Technique Section for TextureMapping
//--------------------------------------------------------------//
technique TextureMapping
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 VS();
      PixelShader = compile ps_2_0 PS();
   }

}

