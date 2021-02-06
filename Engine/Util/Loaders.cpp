#include "Loaders.h"

#include "../Resources/Texture.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../Resources/tiny_obj_loader.h"

#include <iomanip>

namespace vn
{
	Mesh vn::loadMeshFromObj(const std::string& filepath)
	{
		{
			tinyobj::attrib_t attributes;
			std::vector<tinyobj::shape_t> shapes;
			std::vector<tinyobj::material_t> materials;
			std::string errors;
			Mesh objMesh;
			if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &errors, filepath.c_str()))
			{
				std::cout << errors << std::endl;
			}
			/*unsigned int indices = 0;
			for (const auto& shape : shapes)
			{
				for (const auto& index : shape.mesh.indices)
				{
					Vertex vert;
					
					vert.position = 
					{
						attributes.vertices[3 * index.vertex_index + 0],
						attributes.vertices[3 * index.vertex_index + 1],
						attributes.vertices[3 * index.vertex_index + 2]
					};

					vert.uv =
					{
						attributes.texcoords[2 * index.texcoord_index + 0],
						attributes.texcoords[2 * index.texcoord_index + 1]
					};
					
					vert.normal =
					{
						attributes.normals[3 * index.normal_index + 0],
						attributes.normals[3 * index.normal_index + 1],
						attributes.normals[3 * index.normal_index + 2]
					};
					
					objMesh.vertices.push_back(vert);
					objMesh.indicies.push_back(++indices);
					indices++;
				}
			}*/

			// Loop over shapes
			for (size_t s = 0; s < shapes.size(); s++) {
				// Loop over faces(polygon)
				size_t index_offset = 0;
				for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
					int fv = shapes[s].mesh.num_face_vertices[f];

					// Loop over vertices in the face.
					for (size_t v = 0; v < fv; v++) {
						// access to vertex

						tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

						Vertex vert;

						vert.position = vec3
						{
						attributes.vertices[3 * idx.vertex_index + 0],
						attributes.vertices[3 * idx.vertex_index + 1],
						attributes.vertices[3 * idx.vertex_index + 2] 
						};

						if (!attributes.texcoords.empty())
						{
							vert.normal = vec3
							{
							attributes.normals[3 * idx.normal_index + 0],
							attributes.normals[3 * idx.normal_index + 1],
							attributes.normals[3 * idx.normal_index + 2]
							};
						}
						else
						{
							vert.normal = vec3(0.0f);
						}

						if (!attributes.texcoords.empty())
						{
							vert.uv = vec2
							{
							attributes.texcoords[2 * idx.texcoord_index + 0],
							attributes.texcoords[2 * idx.texcoord_index + 1]
							};
						}
						else
						{
							vert.uv = vec2(0.0f);
						}

						objMesh.vertices.push_back(vert);
						objMesh.indicies.push_back(objMesh.indicies.size());

						// Optional: vertex colors
						// tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
						// tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
						// tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
					}
					index_offset += fv;

					// per-face material
					shapes[s].mesh.material_ids[f];
				}
			}

			return objMesh;
		}
	}

	void loadStateFromFile(const std::string& filepath, std::vector<GameObject>& gameObjects)
	{
		nlohmann::json level;
		std::ifstream in(filepath);
		if (!in.is_open())
		{
			throw std::runtime_error("Unable to open file: " + filepath);	//Error Handling
		}
		in >> level;
		in.close();

		for (auto& j : level)
		{
			Transform t;

			t.pos.x = j["px"];
			t.pos.y = j["py"];
			t.pos.z = j["pz"];
			t.rot.x = j["rx"];
			t.rot.y = j["ry"];
			t.rot.z = j["rz"];
			t.scale.x = j["sx"];
			t.scale.y = j["sy"];
			t.scale.z = j["sz"];
			
			GameObject obj(t);

			obj.mass = j["mass"];
			obj.texture_id = j["texture_id"];
			obj.model_id = j["model_id"];

			gameObjects.emplace_back(obj);
		}

	}

	void saveStateToFile(const std::string& filepath, std::vector<GameObject>& gameObjects)
	{
		nlohmann::json level;
		int index = 0;
		for (auto object : gameObjects)
		{
			//Nesting JSON
			nlohmann::json j;
			Transform t = object.getCurrentTransform();
			j["px"] = t.pos.x;
			j["py"] = t.pos.y;
			j["pz"] = t.pos.z;
			j["rx"] = t.rot.x;
			j["ry"] = t.rot.y;
			j["rz"] = t.rot.z;
			j["sx"] = t.scale.x;
			j["sy"] = t.scale.y;
			j["sz"] = t.scale.z;
			j["mass"] = object.mass;
			j["texture_id"] = object.texture_id;
			j["model_id"] = object.model_id;

			level["object" + std::to_string(index)] = j;
			index++;
		}


		std::ofstream out(filepath);
		out << std::setw(4) << level << std::endl;
		out.close();
	}

	void loadTextureList(const std::string& filepath, std::vector<Texture>& gameObjects)
	{

	}

	//void loadModelList(const std::string& filepath, std::vector<>& models)
}