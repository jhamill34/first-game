#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "window.h"
#include "shader.h"
#include "camera.h"
#include "model.h"
#include "light.h"

void processInput(GLFWwindow* window);

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main() {
	GLFWwindow *window = setupWindow();

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("shaders/shaders.vert", "shaders/shaders.frag");
	Model ourModel("models/backpack/backpack.obj");
	DirectionalLight dirLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.05f), glm::vec3(0.4f), glm::vec3(0.5f));

	glm::vec4 bgColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
		// per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

		// don't forget to enable shader before setting uniforms
        ourShader.use();
		ourShader.setVec3("viewPos", camera.Position);
		dirLight.Apply(ourShader);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);	

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, deltaTime);
	} 
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	} 
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.ProcessKeyboard(LEFT, deltaTime);
	} 
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.ProcessKeyboard(RIGHT, deltaTime);
	} 

	unsigned char lookFlags = 0;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		lookFlags |= LOOK_LEFT;
	} 
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		lookFlags |= LOOK_RIGHT;
	} 
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		lookFlags |= LOOK_UP;
	} 
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		lookFlags |= LOOK_DOWN;
	}

	if (lookFlags != 0) {
		camera.ProcessRotation(lookFlags);
	}
}

