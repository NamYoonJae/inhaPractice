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
struct VS_INPUT 
{
   float4 Position : POSITION0;
   float2 mUV : TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 Position : POSITION0;
   float2 mUV      : TEXCOORD0;
};

float time : Time0_2PI;

VS_OUTPUT Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;
   Output.Position = mul(Input.Position, matWorld);
   Output.Position = mul( Output.Position, matViewProjection );
   Output.mUV = Input.mUV;

   //float Deg2Rad = 3.14 * 2.0 / 360;
   float time2Rad = time;//clamp(time,0.0f,3.14 * 2.0);
   
   float s = sin(time2Rad);
   float c = cos(time2Rad);
   
   float2x2 matrixR = float2x2(c,-s,s,c);
   Output.mUV -= 0.5;
   Output.mUV = mul(matrixR,Output.mUV);
   Output.mUV += 0.5;
   
   // 3.14 -> 180 
   //Output.mUV.x = Output.mUV.x + (cos(time)*0.1+0.5);
   
   
   return( Output );
   
}






texture Lava_Tex;
sampler2D Texture0 = sampler_state
{
   Texture = (Lava_Tex);
};


float4 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main(float2 mUV:TEXCOORD0) : COLOR0
{   
   float4 albedo = tex2D(Texture0,mUV);
   return albedo;
   
}




//--------------------------------------------------------------//
// Technique Section for Default_DirectX_Effect
//--------------------------------------------------------------//
technique Default_DirectX_Effect
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main();
   }

}

