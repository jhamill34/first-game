#pragma once

#include <string>
#include <vector>

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "shader.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

struct DefaultMaterial {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

class Mesh {
	public:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;
		DefaultMaterial material;

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, DefaultMaterial defaultMaterial) {
			this->vertices = vertices;
			this->indices = indices;
			this->textures = textures;
			this->material = defaultMaterial;

			setupMesh();
		}

		void Draw(Shader& shader) {
			unsigned int diffuseNr = 1;
			unsigned int specularNr = 1;
			unsigned int emitterNr = 1;

			for(unsigned int i = 0; i < textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
				// retrieve texture number (the N in diffuse_textureN)
				std::string number;
				std::string name = textures[i].type;
				if(name == "texture_diffuse")
					number = std::to_string(diffuseNr++);
				else if(name == "texture_specular")
					number = std::to_string(specularNr++);
				else if (name == "texture_emitter") 
					number = std::to_string(emitterNr++);

				shader.setInt(("material." + name + number).c_str(), i);
				glBindTexture(GL_TEXTURE_2D, textures[i].id);
			}

			shader.setFloat("material.shininess", material.shininess);
			shader.setVec3("material.ambient", material.ambient);
			shader.setVec3("material.diffuse", material.diffuse);
			shader.setVec3("material.specular", material.specular);

			// draw mesh
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			
			glActiveTexture(GL_TEXTURE0);
		}
	
	private:
		unsigned int VAO, VBO, EBO;

		void setupMesh() {
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

			glBindVertexArray(0);
		}
};

