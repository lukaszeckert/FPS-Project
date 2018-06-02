LIBS=-lGL -lglfw -lGLEW
HEADERS=Models/Entity.h Models/VertexBuffer.h Models/Texture.h Models/Camera.h Models/VertexData.h Models/TriangleV.h Loaders/ShaderLoader.h Loaders/OBJ_Loader.h Loaders/lodepng.h Managers/ResourceManager.h Managers/GameManager.h Interfaces/ShaderInterface.h Interfaces/ObjectLoaderInterface.h LightSystem/GlobalLight.h LightSystem/LightSystem.h LightSystem/PointLight.h Render/RenderSystem.h
FILES=Models/VertexBuffer.cpp Models/Texture.cpp Models/Camera.cpp Models/VertexData.cpp Models/Entity.cpp Loaders/lodepng.cpp Loaders/ShaderLoader.cpp Managers/GameManager.cpp Managers/ResourceManager.cpp main.cpp Interfaces/ShaderInterface.cpp Interfaces/ObjectLoaderInterface.cpp LightSystem/LightSystem.cpp LightSystem/PointLight.cpp LightSystem/GlobalLight.cpp Render/RenderSystem.cpp

main_file: $(FILES) $(HEADERS)
	g++ -I ./Dependencies -o main_file $(FILES)  $(LIBS) -Wno-write-strings
