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

HowManyGameObjects = 2

go_0 = {}
go_0[0] = { Name = "Player", HowManyCmps = 1}
go_0[1] = { Component = "Transform", Coord = {X = 1, Y = 1, Z = 1}}

go_1 = {}
go_1[0] = { Name = "Boss", HowManyCmps = 2}
go_1[1] = { Component = "Transform", Coord = {X = 3, Y = 3, Z = 3}}
go_1[2] = { Component = "AudioSource", Route = "./asdfasdf/treh.mp3"}


-- COMPONENT EXAMPLES
-- Transform 		-> go_goNumber[componentNumber] = { Component = "Transform", Coord = {X = 1, Y = 1, Z = 1}}
-- AudioSource 		-> go_goNumber[componentNumber] = { Component = "AudioSource", Route = "./src"}