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
// Default_DirectX_Effect
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//


float4x4 matViewProjection : ViewProjection;
float4x4 matWorld : World;
float Time : Time0_X;
struct VS_INPUT 
{
   float4 Position : POSITION0;
   float2 Tex :TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 Position : POSITION0;
   float2 Tex :TEXCOORD0;
};

VS_OUTPUT vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;
   Output.Position = mul( Input.Position, matWorld);
   Output.Position = mul( Output.Position, matViewProjection );
   Output.Tex = Input.Tex + Time * 0.3;
   
   
   return( Output );
   
}





texture Base_Tex;
sampler2D Texture0 = sampler_state
{
   Texture = (Base_Tex);
};

struct PS_INPUT
{
   float4 Position : POSITION0;
   float2 Tex :TEXCOORD0;
};

float4 ps_main(PS_INPUT Input) : COLOR0
{   
   float4 albedo = tex2D(Texture0,Input.Tex);
   return albedo;
   
}




//--------------------------------------------------------------//
// Technique Section for Default_DirectX_Effect
//--------------------------------------------------------------//
technique Default_DirectX_Effect
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 vs_main();
      PixelShader = compile ps_2_0 ps_main();
   }

}

