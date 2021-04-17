--Tranform = "1,1,1"
--name = "Apple"

--player ={}
--player["Name"] = "Apple"
--player["Transform"] = "1,1,1"
--player["Level"] = 2

player = {Name = "Apple",Id = 1, Level = 2, Transform = {X = 1, Y = 1, Z = 1} }
audioSource = { Transform = {X = 1, Y = 1, Z = 1}, AudioSource = {Route = "./asdfasdf/asd.mp3"}} 

aS1 = { Name = "NombreDelObjeto", HowMany = 2}

aS = {}
aS[0] = { Name = "NombreDelObjeto", HowMany = 2}
aS[1] = { Component = "Transform", Data = {X = 1, Y = 1, Z = 1}}
aS[2] = { Component = "AudioSource", Route = "./asdfasdf/bleh.mp3"}

objetos = {} --New array
objetos[0] = {Name = "Yikes", Id = 0}
objetos[1] = {Name = "Is this shit working?", Id = 1}

function getObjetos(n)
    printDone("Metodo accedido locario")
    return objetos[n]
end

function getaS(n)
    return aS[n]
end