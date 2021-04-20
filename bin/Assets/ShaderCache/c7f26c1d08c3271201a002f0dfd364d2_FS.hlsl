//-----------------------------------------------------------------------------
// Program Type: Fragment shader
// Language: hlsl
// Created by Ogre RT Shader Generator. All rights reserved.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//                         PROGRAM DEPENDENCIES
//-----------------------------------------------------------------------------
#include <OgreUnifiedShader.h>
#include "SGXLib_PerPixelLighting.glsl"
#include "FFPLib_Common.glsl"
#include "FFPLib_Texturing.cg"

//-----------------------------------------------------------------------------
//                         GLOBAL PARAMETERS
//-----------------------------------------------------------------------------

float4	derived_ambient_light_colour;
float4	surface_emissive_colour;
float4	derived_scene_colour;
float	surface_shininess;
float4	light_position_view_space;
float4	derived_light_diffuse_colour;

//-----------------------------------------------------------------------------
// Function Name: main
// Function Desc: 
//-----------------------------------------------------------------------------
void main
	(
	 in float4	oPos_0 : POSITION, 
	 in float3	iTexcoord_0 : TEXCOORD0, 
	 out float4	oColor_0 : COLOR
	)
{
	float4	lColor_0;
	float4	lColor_1;

	lColor_0	=	vec4(1.00000,1.00000,1.00000,1.00000);

	lColor_1	=	vec4(0.000000,0.000000,0.000000,0.000000);

	oColor_0	=	lColor_0;

	oColor_0	=	derived_scene_colour;

	SGX_Light_Directional_Diffuse(iTexcoord_0, light_position_view_space.xyz, derived_light_diffuse_colour.xyz, oColor_0.xyz);

	lColor_0	=	oColor_0;

	oColor_0.xyz	=	oColor_0.xyz+lColor_1.xyz;
}

