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
// HitFlash
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string HitFlash_Pass_0_Model : ModelData = "..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.x";

float4x4 gWorldMatrix : World;
float4x4 gViewMatrix : View;
float4x4 gProjectionMatrix : Projection;

struct VS_INPUT 
{
   float4 Position : POSITION0;
   float2 TexCoord : TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 Position : POSITION0;
   float2 TexCoord : TEXCOORD0;
};

VS_OUTPUT HitFlash_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.Position = mul( Input.Position, gWorldMatrix );
   Output.Position = mul( Output.Position, gViewMatrix );
   Output.Position = mul( Output.Position, gProjectionMatrix );
  
   Output.TexCoord = Input.TexCoord; 
   
   return( Output );
}




texture DiffuseMap_Tex
<
   string ResourceName = "..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Textures\\Earth.jpg";
>;
sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseMap_Tex);
};

struct PS_INPUT
{
   float2 TexCoord : TEXCOORD0;
};

float Offset
<
   string UIName = "Offset";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = 0.00;
   float UIMax = 1.00;
> = float( 1.00 );

float4 HitFlash_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR
{   
   float4 albedo = tex2D(DiffuseSampler, Input.TexCoord);
   
   albedo.r += (0.2f-Offset);
   albedo.g += (0.2f-Offset);
   albedo.b += (0.2f-Offset);
   
   return albedo.rgba;
   
}




//--------------------------------------------------------------//
// Technique Section for HitFlash
//--------------------------------------------------------------//
technique HitFlash
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 HitFlash_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 HitFlash_Pass_0_Pixel_Shader_ps_main();
   }

}

