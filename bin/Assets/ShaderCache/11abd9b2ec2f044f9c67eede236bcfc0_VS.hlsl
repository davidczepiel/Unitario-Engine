//-----------------------------------------------------------------------------
// Program Type: Vertex shader
// Language: hlsl
// Created by Ogre RT Shader Generator. All rights reserved.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//                         PROGRAM DEPENDENCIES
//-----------------------------------------------------------------------------
#include <OgreUnifiedShader.h>
#include "FFPLib_Transform.glsl"
#include "FFPLib_Texturing.glsl"
#include "SGXLib_NormalMap.glsl"
#include "FFPLib_Common.glsl"

//-----------------------------------------------------------------------------
//                         GLOBAL PARAMETERS
//-----------------------------------------------------------------------------

float4x4	worldviewproj_matrix;
float3	camera_position;
float4x4	world_matrix;
float3x3	inv_world_rotation_matrix0;
float4	light_position;
float3x3	inv_world_rotation_matrix1;

//-----------------------------------------------------------------------------
// Function Name: main
// Function Desc: 
//-----------------------------------------------------------------------------
void main
	(
	 in float4	iPos_0 : POSITION, 
	 in float3	iNormal_0 : NORMAL, 
	 in float3	iTangent_0 : TANGENT, 
	 in float2	iTexcoord_0 : TEXCOORD0, 
	 out float4	oPos_0 : POSITION, 
	 out float2	oTexcoord_0 : TEXCOORD0, 
	 out float3	oTexcoord_1 : TEXCOORD1, 
	 out float3	oTexcoord_2 : TEXCOORD2
	)
{
	float4	lColor_0;
	float4	lColor_1;
	float3x3	lMatTBN;
	float3	lNormalMapTempDir;
	float3	lTexcoord_4;

	FFP_Transform(worldviewproj_matrix, iPos_0, oPos_0);

	lColor_0	=	vec4(1.00000,1.00000,1.00000,1.00000);

	lColor_1	=	vec4(0.000000,0.000000,0.000000,0.000000);

	SGX_ConstructTBNMatrix(iNormal_0, iTangent_0, lMatTBN);

	oTexcoord_0	=	iTexcoord_0;

	FFP_Transform(world_matrix, iPos_0, lTexcoord_4);

	lNormalMapTempDir	=	camera_position.xyz-lTexcoord_4.xyz;

	FFP_Transform(inv_world_rotation_matrix1, lNormalMapTempDir, lNormalMapTempDir);

	FFP_Transform(lMatTBN, lNormalMapTempDir, oTexcoord_1);

	lNormalMapTempDir	=	light_position.xyz-lTexcoord_4;

	FFP_Transform(inv_world_rotation_matrix1, lNormalMapTempDir, lNormalMapTempDir);

	FFP_Transform(lMatTBN, lNormalMapTempDir, oTexcoord_2);
}

