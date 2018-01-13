
class  ParticlesSystemFactory {


	static void ConfigFireParticles(CParticleSystemTransformFeedback* particlesSystem)
	{
		particlesSystem->SetGeneratorProperties(
			glm::vec3(0.0f, 2.5f, 0.0f), // position
			glm::vec3(-0.025, 0.3, -0.025), // Minimal velocity
			glm::vec3(0.025, 0.05, 0.025f), // Maximal velocity
			glm::vec3(0, 0, 0), // Gravity force 
			glm::vec3(1.0f, 0.5f, 0.0f), // Color 
			13.5f, // Minimum lifetime in seconds
			45.0f, // Maximum lifetime in seconds
			0.04f, // Rendered size
			0.01f, // Spawn every 
			1); // count of particles
	}
};
