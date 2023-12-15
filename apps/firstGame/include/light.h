#pragma once

#include <glm/glm.hpp>
#include "shader.h"

class DirectionalLight {
	public:
		glm::vec3 direction;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		DirectionalLight(
				glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f), 
				glm::vec3 ambient = glm::vec3(1.0f), 
				glm::vec3 diffuse = glm::vec3(1.0f),
				glm::vec3 specular = glm::vec3(1.0f)
		) {
			this->direction = direction;
			this->ambient = ambient;
			this->diffuse = diffuse;
			this->specular = specular;
		}

		void Apply(Shader& shader) {
			shader.setVec3("dirLight.direction", direction);
			shader.setVec3("dirLight.ambient", ambient);
			shader.setVec3("dirLight.diffuse", diffuse);
			shader.setVec3("dirLight.specular", specular);
		}
};

