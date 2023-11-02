/****** Resources *******/

#define FLIP_TEXTURE_Y 1 

cbuffer CBufferPerObject
{
	float4x4 WorldViewProjection : WORLDVIEWPROJECTION < string UIWidget="None"; >;
}

RasterierState DisableCulling
{
    CullMode = NONE; 
}; 

Texture2D ColorSampler
{
    Filter = MIN_MAG_MIP_LINEAR; 
    AddressU = WRAP; 
    AddressV = WRAP; 
}; 

/***** Data Structures ******/

struct VS_INPUT
{
    float4 ObjectProjection : SV_Position; 
    float2 TextureCoordinate : TEXTCOORD; 
};

struct VS_OUTPUT
{
    
};
