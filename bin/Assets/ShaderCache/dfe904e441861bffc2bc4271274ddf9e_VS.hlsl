//-----------------------------------------------------------------------------
// Program Type: Vertex shader
// Language: hlsl
// Created by Ogre RT Shader Generator. All rights reserved.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//                         PROGRAM DEPENDENCIES
//-----------------------------------------------------------------------------
#include <OgreUnifiedShader.h>
#include "FFPLib_Common.glsl"
#include "FFPLib_Transform.glsl"
#include "SGXLib_PerPixelLighting.glsl"
#include "FFPLib_Texturing.glsl"

//-----------------------------------------------------------------------------
//                         GLOBAL PARAMETERS
//-----------------------------------------------------------------------------

float3x4	world_matrix_array_3x4[24];
float4x4	inverse_world_matrix;
float4x4	viewproj_matrix;
float3x3	normal_matrix;

//-----------------------------------------------------------------------------
// Function Name: main
// Function Desc: 
//-----------------------------------------------------------------------------
void main
	(
	 in float4	iPos_0 : POSITION, 
	 in float3	iNormal_0 : NORMAL, 
	 in uint4	iBlendIndices_0 : BLENDINDICES, 
	 in float4	iBlendWeights_0 : BLENDWEIGHT, 
	 out float4	oPos_0 : POSITION, 
	 out float3	oTexcoord_0 : TEXCOORD0
	)
{
	float4	lTexcoord_0;
	float3	lTexcoord_1;
	float4	TempVal4;
	float3	TempVal3;
	float4	lColor_4;
	float4	lColor_5;

	FFP_Transform(world_matrix_array_3x4[int(iBlendIndices_0.x)], iPos_0, TempVal4.xyz);

	TempVal4.w	=	1.00000;

	TempVal4	=	TempVal4*iBlendWeights_0.x;

	lTexcoord_0	=	TempVal4;

	FFP_Transform(world_matrix_array_3x4[int(iBlendIndices_0.y)], iPos_0, TempVal4.xyz);

	TempVal4.w	=	1.00000;

	TempVal4	=	TempVal4*iBlendWeights_0.y;

	lTexcoord_0	=	TempVal4+lTexcoord_0;

	FFP_Transform(inverse_world_matrix, lTexcoord_0, iPos_0);

	FFP_Transform(viewproj_matrix, lTexcoord_0, oPos_0);

	FFP_Transform(world_matrix_array_3x4[int(iBlendIndices_0.x)], iNormal_0, TempVal3);

	TempVal3	=	TempVal3*iBlendWeights_0.x;

	lTexcoord_1	=	TempVal3;

	FFP_Transform(world_matrix_array_3x4[int(iBlendIndices_0.y)], iNormal_0, TempVal3);

	TempVal3	=	TempVal3*iBlendWeights_0.y;

	lTexcoord_1	=	TempVal3+lTexcoord_1;

	FFP_Transform(inverse_world_matrix, lTexcoord_1, iNormal_0);

	lColor_4	=	vec4(1.00000,1.00000,1.00000,1.00000);

	lColor_5	=	vec4(0.000000,0.000000,0.000000,0.000000);
}

