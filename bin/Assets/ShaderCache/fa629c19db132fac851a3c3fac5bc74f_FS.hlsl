//-----------------------------------------------------------------------------
// Program Type: Fragment shader
// Language: hlsl
// Created by Ogre RT Shader Generator. All rights reserved.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//                         PROGRAM DEPENDENCIES
//-----------------------------------------------------------------------------
#include <OgreUnifiedShader.h>
#include "FFPLib_Texturing.glsl"
#include "SGXLib_PerPixelLighting.glsl"
#include "SGXLib_NormalMap.glsl"
#include "FFPLib_Common.glsl"

//-----------------------------------------------------------------------------
//                         GLOBAL PARAMETERS
//-----------------------------------------------------------------------------

SAMPLER2D(gNormalMapSampler0, 0);
float4	derived_ambient_light_colour;
float4	surface_emissive_colour;
float4	derived_scene_colour;
float	surface_shininess;
float4	light_attenuation;
float4	derived_light_diffuse_colour;
float4	derived_light_specular_colour;

//-----------------------------------------------------------------------------
// Function Name: main
// Function Desc: 
//-----------------------------------------------------------------------------
void main
	(
	 in float4	oPos_0 : POSITION, 
	 in float2	iTexcoord_0 : TEXCOORD0, 
	 in float3	iTexcoord_1 : TEXCOORD1, 
	 in float3	iTexcoord_2 : TEXCOORD2, 
	 out float4	oColor_0 : COLOR
	)
{
	float4	lColor_0;
	float4	lColor_1;
	float3	lTexcoord_2;

	lColor_0	=	vec4(1.00000,1.00000,1.00000,1.00000);

	lColor_1	=	vec4(0.000000,0.000000,0.000000,0.000000);

	oColor_0	=	lColor_0;

	SGX_FetchNormal(gNormalMapSampler0, iTexcoord_0, lTexcoord_2);

	oColor_0	=	derived_scene_colour;

	SGX_Light_Point_DiffuseSpecular(lTexcoord_2, iTexcoord_1, iTexcoord_2, light_attenuation, derived_light_diffuse_colour.xyz, derived_light_specular_colour.xyz, surface_shininess, oColor_0.xyz, lColor_1.xyz);

	lColor_0	=	oColor_0;

	oColor_0.xyz	=	oColor_0.xyz+lColor_1.xyz;
}

