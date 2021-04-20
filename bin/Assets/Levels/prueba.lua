-- How to define game objects in the scene file
-- Step1: HowManyGameObjects must contain one more number than the last go_X that was declared because these start at 0
-- 		  If you want to add a go add one to this variable
-- Step2: Structure
--  go_Number = {}   								-> where "Number" is the next to the last go declared
--  go_Number[0] = { Name = "", HowManyCmps = X}	-> Name is the name of the GameObject. HowManyCmps is the number of components of the go
--  go_Number[1] = { Component = " ", General Data} -> Component is the ENUM used to identify the COMPONENT (getComponentType method from LuaParser). 
--													   General Data is the component data

-- You must bear in mind that in the definition of go, the first position of the array will always be the data that it needs to know its name 
-- and how many components it has. The following positions in the array will be used to define the components

-- You can find component definition examples at the end of this document

HowManyGameObjects = 7

go_0 = {}
go_0[0] = { Name = "Player", HowManyCmps = 3}
go_0[1] = { Component = "Transform", Coord = {X = 1, Y = 1, Z = 1}}
go_0[2] = { Component = "ASD", Coord = {X = 1, Y = 1, Z = 1}}
--Fmod vector3 position coge la posicion del transform
go_0[3] = { Component = "Listener", ListenerNumber = 0, 
			Velocity = {X = 1, Y = 0, Z = 5}, Forward = {X = 3, Y = 2, Z = 1}, Up = {X = 8, Y = 7, Z = 9}}
 
go_1 = {}
go_1[0] = { Name = "Boss", HowManyCmps = 3}
go_1[1] = { Component = "Transform", Coord = {X = 3, Y = 3, Z = 3}}
go_1[2] = { Component = "AudioSource", Route = "./asdfasdf/treh.mp3"}
go_1[3] = { Component = "Camera", Orientation = {X = 3, Y = 2, Z = 1}, Plane = {Near = 2, Far = 9999},
			Projection = true, Fovy = 6, Frustrum = {Left = 4, Right = 3, Top = 2, Bot = 1}, 
			OrthoWindow = {W = 8, H = 9}, Viewport = {Left = 9, Top = 8, W = 7, H = 6}}

go_2 = {}
go_2[0] = { Name = "DarkLight", HowManyCmps = 2}
go_2[1] = { Component = "Transform", Coord = {X = 3, Y = 3, Z = 3}}
go_2[2] = { Component = "LightComponent", LightType= "POINT", Visible = false,Diffuse = {Red = 1, Green= 1, Blue = 1}, 
	   		Specular = {Red = 1, Green= 1, Blue = 1},
			Attenuation = {Range = 1, Constant = 1, Linear = 1, Quadratic = 1},
			SpotLightRange = {InnerAngle = 1, OuterAngle = 1, FallOf = 1}}

go_3 = {}
go_3[0] = { Name = "SexyAnimations", HowManyCmps = 3}
go_3[1] = { Component = "Transform", Coord = {X = 1, Y = 2, Z = 3}}
go_3[2] = { Component = "Animator", HowManyStates = 2,
			State1 = {Name = "initial", Loop = true},
			State2 = {Name = "second", Loop = false}}
go_3[3] = { Component = "ImageRender", DefaultDimension = {W = 1, H = 2}, MaterialName = "SoyFeo", Visible = false, 
			BillboardOrigin = "BBO_TOP_LEFT", BillboardType = "BBT_POINT", BillboardRotationType = "BBR_VERTEX",
			Scale = {X = 0.3, Y = 0.5, Z = 1}, Rotation = {X = 1, Y = 2, Z = 3, Angle = 180}}

go_4 = {}
go_4[0] = {Name = "SexyButton", HowManyCmps = 2}
go_4[1] = {	Component = "Transform", Coord = {X = 1, Y = 2, Z = 3}}
go_4[2] = {	Component = "OverlayComponent", Hide=true, Name = "SexyOverlay", Container = "SexyContainer", Material= "SexyOverlaymMaterial"}
go_4[3] = {	Component = "ButtonComponent", Active = false, OverLayName="ovName", ContainerName= "SexyContainer", 
			DefaultMaterial = "defaultMaterial", HoverMaterial = "hoverMaterial", PressMaterial = "pressMaterial"}

go_5 = {}
go_5[0] = {Name = "SexyRenderObject", HowManyCmps = 2}
go_5[1] = {	Component = "Transform", Coord = {X = 1, Y = 2, Z = 3}}
go_5[2] = {	Component = "RenderObject", MeshName="SexyMesh", Material="SexyMaterial", 
			RotateAngle = 1, Rotate={X=1, Y=1, Z=1}, Scale = {X=1, Y=1, Z=1}, LookAt ={X=1, Y=1, Z=1},
			Visible=false, Shadows=false, RenderingDistance = 1}

go_6 = {}
go_6[0] = {Name = "SexyRenderObject", HowManyCmps = 2}
go_6[1] = {	Component = "Transform", Coord = {X = 1, Y = 2, Z = 3}}
go_6[2] = {	Component = "ParticleSystem", Path="SexyPath"}




-- COMPONENT EXAMPLES

-- Transform 		-> go_goNumber[componentNumber] = { Component = "Transform", Coord = {X = 1, Y = 1, Z = 1}}

-- AudioSource 		-> go_goNumber[componentNumber] = { Component = "AudioSource", Route = "./src"}

-- LightComponent	-> go_goNumber[componentNumber] = { Component = "LightComponent", LightType= "POINT", Visible = false,
--														Diffuse = {Red = 1, Green= 1, Blue = 1} 
--														Specular = {Red = 1, Green= 1, Blue = 1}
--														Attenuation = {Range = 1, Constant = 1, Linear = 1, Quadratic = 1}
--														SpotLightRange = {InnerAngle = 1, OuterAngle = 1, FallOf = 1}}

-- ListenerComponent-> go_goNumber[componentNumber] = { Component = "Listener", ListenerNumber = 0, 
--														Velocity = {X = 1, Y = 0, Z = 5}, Forward = {X = 3, Y = 2, Z = 1}, Up = {X = 8, Y = 7, Z = 9}}

-- AnimatorComponent-> go_goNumber[componentNumber] = { Component = "Animator", HowManyStates = 2,
--														State1 = {Name = "initial", Loop = true},
--														State2 = {Name = "second", Loop = false},
--														StateN = {Name = "anotherOne", Loop = "true"}}

-- ButtonComponent	-> go_goNumber[componentNumber] = { Component = "ButtonComponent", Active = false, OverLayName="ovName", ContainerName= "SexyContainer", 
--														DefaultMaterial = "defaultMaterial", HoverMaterial = "hoverMaterial", PressMaterial = "pressMaterial"}

-- CameraComponent  -> go_goNumber[componentNumber] = { Component = "Camera", Orientation = {X = 3, Y = 2, Z = 1}, 
--    Projection (F = orthographic, T = perspective)	Plane = {Near = 2, Far = 9999}, Projection = true, Fovy = 6, 
--								 						Frustrum = {Left = 4, Right = 3, Top = 2, Bot = 1}, 
--								 						OrthoWindow = {W = 8, H = 9}, Viewport = {Left = 9, Top = 8, W = 7, H = 6}}

-- Overlay 			-> go_goNumber[componentNumber] = { Component = "OverlayComponent", Hide=true, Name = "SexyOverlay", Container = "SexyContainer", Material= "SexyOverlaymMaterial"}

-- RenderObject 	-> go_goNumber[componentNumber] = { Component = "RenderObject", MeshName="SexyMesh", Material="SexyMaterial", 
--														RotateAngle = 1, Rotate={X=1, Y=1, Z=1}, Scale = {X=1, Y=1, Z=1}, LookAt ={X=1, Y=1, Z=1},
--														Visible=false, Shadows=false, RenderingDistance = 1}

-- ImageRender      -> go_goNumber[componentNumber] = { Component = "ImageRender", DefaultDimension = {W = 1, H = 2}, 
--														MaterialName = "SoyFeo", Visible = false, 
--														BillboardOrigin = "BBO_TOP_LEFT", BillboardType = "BBT_POINT",
--														BillboardRotationType = "BBR_VERTEX",
--														Scale = {X = 0.3, Y = 0.5, Z = 1}, Rotation = {X = 1, Y = 2, Z = 3, Angle = 180}}

-- PartycleSystem 	-> go_goNumber[componentNumber] = { Component = "ParticleSystem", Path="SexyPath"}