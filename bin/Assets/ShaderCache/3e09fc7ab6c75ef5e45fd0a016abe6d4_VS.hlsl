//-----------------------------------------------------------------------------
// Program Type: Vertex shader
// Language: hlsl
// Created by Ogre RT Shader Generator. All rights reserved.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//                         PROGRAM DEPENDENCIES
//-----------------------------------------------------------------------------
#include <OgreUnifiedShader.h>
#include "FFPLib_Transform.cg"
#include "FFPLib_Common.glsl"
#include "FFPLib_Texturing.cg"

//-----------------------------------------------------------------------------
//                         GLOBAL PARAMETERS
//-----------------------------------------------------------------------------

float4x4	worldviewproj_matrix;

//-----------------------------------------------------------------------------
// Function Name: main
// Function Desc: 
//-----------------------------------------------------------------------------
void main
	(
	 in float4	iPos_0 : POSITION, 
	 in float2	iTexcoord_0 : TEXCOORD0, 
	 out float4	oPos_0 : POSITION, 
	 out float2	oTexcoord_0 : TEXCOORD0
	)
{
	float4	lColor_0;
	float4	lColor_1;

	FFP_Transform(worldviewproj_matrix, iPos_0, oPos_0);

	lColor_0	=	vec4(1.00000,1.00000,1.00000,1.00000);

	lColor_1	=	vec4(0.000000,0.000000,0.000000,0.000000);

	oTexcoord_0	=	iTexcoord_0;
}

