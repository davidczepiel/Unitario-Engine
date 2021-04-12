//-----------------------------------------------------------------------------
// Program Type: Fragment shader
// Language: hlsl
// Created by Ogre RT Shader Generator. All rights reserved.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//                         PROGRAM DEPENDENCIES
//-----------------------------------------------------------------------------
#include <OgreUnifiedShader.h>
#include "FFPLib_Common.glsl"
#include "FFPLib_Texturing.cg"
#include "SGXLib_LayeredBlending.glsl"

//-----------------------------------------------------------------------------
//                         GLOBAL PARAMETERS
//-----------------------------------------------------------------------------

SAMPLER2D(gTextureSampler0, 0);
SAMPLER2D(gTextureSampler1, 1);
float4	custom2;

//-----------------------------------------------------------------------------
// Function Name: main
// Function Desc: 
//-----------------------------------------------------------------------------
void main
	(
	 in float4	oPos_0 : POSITION, 
	 in float2	iTexcoord_0 : TEXCOORD0, 
	 in float2	iTexcoord_1 : TEXCOORD1, 
	 out float4	oColor_0 : COLOR
	)
{
	float4	lColor_0;
	float4	lColor_1;
	float4	texel_0;
	float4	texel_1;

	lColor_0	=	vec4(1.00000,1.00000,1.00000,1.00000);

	lColor_1	=	vec4(0.000000,0.000000,0.000000,0.000000);

	oColor_0	=	lColor_0;

	texel_0	=	texture2D(gTextureSampler0, iTexcoord_0);

	texel_1	=	texture2D(gTextureSampler1, iTexcoord_1);

	oColor_0	=	texel_0*oColor_0;

	SGX_src_mod_inv_modulate(texel_1, custom2, texel_1);

	SGX_blend_luminosity(texel_1, oColor_0, oColor_0);

	oColor_0.xyz	=	oColor_0.xyz+lColor_1.xyz;
}

