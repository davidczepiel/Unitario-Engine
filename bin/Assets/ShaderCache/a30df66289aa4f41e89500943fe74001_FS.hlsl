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
#include "FFPLib_Texturing.cg"
#include "SGXLib_TriplanarTexturing.glsl"

//-----------------------------------------------------------------------------
//                         GLOBAL PARAMETERS
//-----------------------------------------------------------------------------

float4	derived_ambient_light_colour;
float4	surface_emissive_colour;
float4	derived_scene_colour;
float	surface_shininess;
float4	light_position_view_space;
float4	light_attenuation;
float4	derived_light_diffuse_colour;
SAMPLER2D(tp_sampler_from_x0, 0);
SAMPLER2D(tp_sampler_from_y1, 1);
SAMPLER2D(tp_sampler_from_z2, 2);
float3	gTPParams0;

//-----------------------------------------------------------------------------
// Function Name: main
// Function Desc: 
//-----------------------------------------------------------------------------
void main
	(
	 in float4	oPos_0 : POSITION, 
	 in float3	iTexcoord_0 : TEXCOORD0, 
	 in float3	iTexcoord_1 : TEXCOORD1, 
	 in float3	iTexcoord_2 : TEXCOORD2, 
	 in float4	iTexcoord_3 : TEXCOORD3, 
	 out float4	oColor_0 : COLOR
	)
{
	float4	lColor_0;
	float4	lColor_1;
	float3	lTexcoord_2;
	float3	lTexcoord_3;

	lColor_0	=	vec4(1.00000,1.00000,1.00000,1.00000);

	lColor_1	=	vec4(0.000000,0.000000,0.000000,0.000000);

	oColor_0	=	lColor_0;

	oColor_0	=	derived_scene_colour;

	lTexcoord_3	=	vec3(-1.00000,-1.00000,-1.00000)*iTexcoord_1;

	lTexcoord_2	=	light_position_view_space.xyz-iTexcoord_1;

	SGX_Light_Point_Diffuse(iTexcoord_0, lTexcoord_2, light_attenuation, derived_light_diffuse_colour.xyz, oColor_0.xyz);

	lColor_0	=	oColor_0;

	SGX_TriplanarTexturing(oColor_0, iTexcoord_2, iTexcoord_3, tp_sampler_from_x0, tp_sampler_from_y1, tp_sampler_from_z2, gTPParams0, oColor_0);

	oColor_0.xyz	=	oColor_0.xyz+lColor_1.xyz;
}

