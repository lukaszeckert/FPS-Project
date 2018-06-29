#include "ObjectLoaderInterface.h"

Object* ObjectLoaderInterface::loadObjFile(const char * filename, std::vector<Texture *> *TextureArray)
{
	Object *object = new Object();
	objl::Loader Loader;
	bool loadout = Loader.LoadFile(filename);

	// Check to see if it loaded

	// If so continue
	if (loadout)
	{
		// Go through each loaded mesh and out its contents
		for (int i = 0; i < Loader.LoadedMeshes.size(); i++)
		{
			std::vector<VertexData> mesh_points;
			std::vector<VertexData*> points;

			// Copy one of the loaded meshes to be our current mesh
			objl::Mesh curMesh = Loader.LoadedMeshes[i];

			// Go through each vertex and print its number,
			//  position, normal, and texture coordinate
			for (size_t j = 0; j < curMesh.Vertices.size(); j++)
			{
				VertexData *vd = new VertexData(glm::vec3(curMesh.Vertices[j].Position.X, curMesh.Vertices[j].Position.Y, curMesh.Vertices[j].Position.Z),
					glm::vec3(curMesh.Vertices[j].Normal.X, curMesh.Vertices[j].Normal.Y, curMesh.Vertices[j].Normal.Z),
					glm::vec2(curMesh.Vertices[j].TextureCoordinate.X, curMesh.Vertices[j].TextureCoordinate.Y));
				points.push_back(vd);
	
			}

			for (size_t j = 0; j < curMesh.Indices.size(); j++)
			{
				mesh_points.push_back(*points[curMesh.Indices[j]]);
			}


			std::string tex_path = "GraphicModels/" + curMesh.MeshMaterial.map_Ka;
			Texture *tex = Texture::getTexture(tex_path);
			TextureArray->push_back(tex);

			std::string tex_spec_path = "GraphicModels/" + curMesh.MeshMaterial.map_Ks;
			Texture *tex_spec = Texture::getTexture(tex_spec_path);
			TextureArray->push_back(tex_spec);

			object->addMesh(new Mesh(curMesh.MeshName, mesh_points, tex, tex_spec));
		}

	}
	
	return object;
}
