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
		// Create/Open e1Out.txt
		std::ofstream file("e1Out.txt");
		
		// Go through each loaded mesh and out its contents
		for (int i = 0; i < Loader.LoadedMeshes.size(); i++)
		{
			std::vector<VertexData> mesh_points;
			std::vector<VertexData*> points;

			// Copy one of the loaded meshes to be our current mesh
			objl::Mesh curMesh = Loader.LoadedMeshes[i];

			// Print Mesh Name
			//file << "Mesh " << i << ": " << curMesh.MeshName << "\n";

			// Print Vertices
			//file << "Vertices:\n";

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

			// Print Material
			file << "Material: " << curMesh.MeshMaterial.name << "\n";
			file << "Ambient Color: " << curMesh.MeshMaterial.Ka.X << ", " << curMesh.MeshMaterial.Ka.Y << ", " << curMesh.MeshMaterial.Ka.Z << "\n";
			file << "Diffuse Color: " << curMesh.MeshMaterial.Kd.X << ", " << curMesh.MeshMaterial.Kd.Y << ", " << curMesh.MeshMaterial.Kd.Z << "\n";
			file << "Specular Color: " << curMesh.MeshMaterial.Ks.X << ", " << curMesh.MeshMaterial.Ks.Y << ", " << curMesh.MeshMaterial.Ks.Z << "\n";
			file << "Specular Exponent: " << curMesh.MeshMaterial.Ns << "\n";
			file << "Optical Density: " << curMesh.MeshMaterial.Ni << "\n";
			file << "Dissolve: " << curMesh.MeshMaterial.d << "\n";
			file << "Illumination: " << curMesh.MeshMaterial.illum << "\n";
			file << "Ambient Texture Map: " << curMesh.MeshMaterial.map_Ka << "\n";
			file << "Diffuse Texture Map: " << curMesh.MeshMaterial.map_Ka << "\n";
			file << "Specular Texture Map: " << curMesh.MeshMaterial.map_Ks << "\n";
			file << "Alpha Texture Map: " << curMesh.MeshMaterial.map_d << "\n";
			file << "Bump Map: " << curMesh.MeshMaterial.map_bump << "\n";

			// Leave a space to separate from the next mesh
			file << "\n";

			std::string tex_path = "GraphicModels/" + curMesh.MeshMaterial.map_Ka;
			Texture *tex = Texture::getTexture(tex_path);
			TextureArray->push_back(tex);

			std::string tex_spec_path = "GraphicModels/" + curMesh.MeshMaterial.map_Ks;
			Texture *tex_spec = Texture::getTexture(tex_spec_path);
			TextureArray->push_back(tex_spec);

			object->addMesh(new Mesh(curMesh.MeshName, mesh_points, tex, tex_spec));
		}

		// Close File
		file.close();

	}
	// If not output an error
	else
	{
		// Create/Open e1Out.txt
		std::ofstream file("e1Out.txt");

		// Output Error
		file << "Failed to Load File. May have failed to find it or it was not an .obj file.\n";

		// Close File
		file.close();
	}
	return object;
}
