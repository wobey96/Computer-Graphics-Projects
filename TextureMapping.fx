/****** Resources *******/

#define FLIP_TEXTURE_Y 1 

cbuffer CBufferPerObject
{
	float4x4 WorldViewProjection : WORLDVIEWPROJECTION < string UIWidget="None"; >;
}

RasterizerState DisableCulling
{
    CullMode = NONE; 
}; 

Texture2D ColorTexture <
	string ResourceName = "default_color.dds"; 
	string UIName = "Color Texture"; 
	string ResourceType = "2D"; 
>;

SamplerState ColorSampler
{
    Filter = MIN_MAG_MIP_LINEAR; 
    AddressU = WRAP; 
    AddressV = WRAP; 
}; 

/***** Data Structures ******/

struct VS_INPUT
{
    float4 ObjectPosition: POSITION; 
    float2 TextureCoordinate : TEXTCOORD; 
};

struct VS_OUTPUT
{
    float4 Position : SV_Position; 
	float2 TextureCoordinate : TEXTCOORD; 
};

/***** Utility Functions ******/

float2 get_corrected_texture_coordinate(float2 textureCoordinate)
{
	#if FLIP_TEXTURE_Y
		return float2(textureCoordinate.x, 1.0 - textureCoordinate.y); 
	#else
		return textureCoordinate; 
	#endif
}

/***** Vertex Shader ******/

VS_OUTPUT vertex_shader(VS_INPUT IN)
{
	VS_OUTPUT OUT = (VS_OUTPUT) 0; 
	OUT.Position = mul(IN.ObjectPosition, WorldViewProjection); 
	OUT.TextureCoordinate = get_corrected_texture_coordinate(IN.TextureCoordinate);
	
	return OUT; 
}

/***** Pixel Shader ******/

float4 pixel_shader(VS_OUTPUT IN) : SV_Target
{
	return ColorTexture.Sample(ColorSampler, IN.TextureCoordinate); 
}

/***** Techniques ******/

technique10 main10
{
	pass p0
	{
		
		SetVertexShader(CompileShader(vs_4_0, vertex_shader()));
		SetGeometryShader(NULL); 
		SetPixelShader(CompileShader(ps_4_0, pixel_shader()));
		SetRasterizerState(DisableCulling); 
		
	}
}
