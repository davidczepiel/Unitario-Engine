--Tranform = "1,1,1"
--name = "Apple"

--player ={}
--player["Name"] = "Apple"
--player["Transform"] = "1,1,1"
--player["Level"] = 2
 



go_0 = {}
go_0[0] = { Name = "0", HowMany = 2}
go_0[1] = { Component = "Transform", Coord = {X = 1, Y = 1, Z = 1}}
go_0[2] = { Component = "AudioSource", Route = "./asdfasdf/bleh.mp3"}

go_1 = {}
go_1[0] = { Name = "1", HowMany = 2}
go_1[1] = { Component = "Transform", Coord = {X = 3, Y = 3, Z = 3}}
go_1[2] = { Component = "AudioSource", Route = "./asdfasdf/treh.mp3"}

function getaS(n)
    return aS[n]
end