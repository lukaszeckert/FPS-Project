LIBS=-lGL -lglfw -lGLEW
HEADERS=Models/Entity.h Models/VertexBuffer.h Models/Texture.h Models/Camera.h Models/VertexData.h Models/TriangleV.h Models/Object.h Models/Mesh.h \
   Loaders/ShaderLoader.h Loaders/OBJ_Loader.h Loaders/lodepng.h Managers/ResourceManager.h Managers/GameManager.h Interfaces/ShaderInterface.h \
	 Interfaces/ObjectLoaderInterface.h LightSystem/GlobalLight.h LightSystem/LightSystem.h LightSystem/PointLight.h LightSystem/DirectionalLight.h \
	 LightSystem/SpotLight.h Render/RenderSystem.h Render/Scane.h Loaders/ScaneLoader.h
	 
FILES=Models/VertexBuffer.cpp Models/Texture.cpp Models/Camera.cpp Models/VertexData.cpp Models/Entity.cpp Loaders/lodepng.cpp Models/Object.cpp Models/Mesh.cpp \
   Loaders/ShaderLoader.cpp Managers/GameManager.cpp Managers/ResourceManager.cpp main.cpp Interfaces/ShaderInterface.cpp Interfaces/ObjectLoaderInterface.cpp \
	 LightSystem/LightSystem.cpp LightSystem/PointLight.cpp LightSystem/GlobalLight.cpp LightSystem/DirectionalLight.cpp LightSystem/SpotLight.cpp \
	 Render/RenderSystem.cpp Render/Scane.cpp Loaders/ScaneLoader.cpp

main_file: $(FILES) $(HEADERS)
	g++ -g -I ./Dependencies -I /usr/local/include/bullet -o main_file $(FILES)  $(LIBS) -Wno-write-strings /usr/local/lib/libBulletDynamics.a /usr/local/lib/libBulletCollision.a /usr/local/lib/libLinearMath.a
