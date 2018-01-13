#include "CParticleSystemTransformFeedback.hpp"
#include "Shader.hpp"
#include "config.hpp"
#include "CParticle.hpp"
#include <GLFW\glfw3.h>
#include "glm/gtc/matrix_transform.hpp"

CParticleSystemTransformFeedback::CParticleSystemTransformFeedback()
{
}

double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

bool CParticleSystemTransformFeedback::InitalizeParticleSystem(Shader *const particlesShader)
{
	if (bInitialized)return false;

	const char* sVaryings[NUM_PARTICLE_ATTRIBUTES] =
	{
		"vPositionOut",
		"vVelocityOut",
		"vColorOut",
		"fLifeTimeOut",
		"fSizeOut",
		"iTypeOut",
	};

	for (int i = 0; i < NUM_PARTICLE_ATTRIBUTES; i++)
		glTransformFeedbackVaryings(particlesShader->getProgram(), 6, sVaryings, GL_INTERLEAVED_ATTRIBS);


	glGenTransformFeedbacks(1, &uiTransformFeedbackBuffer);
	glGenQueries(1, &uiQuery);

	glGenBuffers(2, uiParticleBuffer);
	glGenVertexArrays(2, uiVAO);

	CParticle partInitialization;
	partInitialization.iType = 0;

	for (int i = 0; i < 2; i++)
	{
		glBindVertexArray(uiVAO[i]);
		glBindBuffer(GL_ARRAY_BUFFER, uiParticleBuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CParticle)*MAX_PARTICLES_ON_SCENE, NULL, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(CParticle), &partInitialization);

		for (int i = 0; i < NUM_PARTICLE_ATTRIBUTES; i++)
			glEnableVertexAttribArray(i);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CParticle), (const GLvoid*)0); // Position
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CParticle), (const GLvoid*)12); // Velocity
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(CParticle), (const GLvoid*)24); // Color
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(CParticle), (const GLvoid*)36); // Lifetime
		glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(CParticle), (const GLvoid*)40); // Size
		glVertexAttribPointer(5, 1, GL_INT, GL_FALSE, sizeof(CParticle), (const GLvoid*)44); // Type
	}
	iCurReadBuffer = 0;
	iNumParticles = 1;

	bInitialized = true;

	return true;
}

void CParticleSystemTransformFeedback::UpdateParticles(float fTimePassed, Shader *const particlesShader)
{
	if (!bInitialized)return;

	particlesShader->use();

	particlesShader->setFloat("fTimePassed", fTimePassed);
	particlesShader->setVec3("vGenPosition", vGenPosition);
	particlesShader->setVec3("vGenVelocityMin", vGenVelocityMin);
	particlesShader->setVec3("vGenVelocityRange", vGenVelocityRange);
	particlesShader->setVec3("vGenColor", vGenColor);
	particlesShader->setVec3("vGenGravityVector", vGenGravityVector);

	particlesShader->setFloat("fGenLifeMin", fGenLifeMin);
	particlesShader->setFloat("fGenLifeRange", fGenLifeRange);

	particlesShader->setFloat("fGenSize", fGenSize);
	particlesShader->setFloat("iNumToGenerate", 0);

	fElapsedTime += fTimePassed;

	if (fElapsedTime > fNextGenerationTime)
	{
		particlesShader->setInt("iNumToGenerate", iNumToGenerate);
		fElapsedTime -= fNextGenerationTime;

		glm::vec3 vRandomSeed = glm::vec3(fRand(-10.0f, 20.0f), fRand(-10.0f, 20.0f), fRand(-10.0f, 20.0f));
		particlesShader->setVec3("vRandomSeed", vRandomSeed);
	}

	glEnable(GL_RASTERIZER_DISCARD);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, uiTransformFeedbackBuffer);

	glBindVertexArray(uiVAO[iCurReadBuffer]);
	glEnableVertexAttribArray(1); // Re-enable velocity

	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, uiParticleBuffer[1 - iCurReadBuffer]);

	glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, uiQuery);
	glBeginTransformFeedback(GL_POINTS);

	glDrawArrays(GL_POINTS, 0, iNumParticles);

	glEndTransformFeedback();

	glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
	glGetQueryObjectiv(uiQuery, GL_QUERY_RESULT, &iNumParticles);

	iCurReadBuffer = 1 - iCurReadBuffer;

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
}

void CParticleSystemTransformFeedback::SetMatrices(glm::mat4* a_matProjection, glm::vec3 vEye, glm::vec3 vView, glm::vec3 vUpVector)
{
	matProjection = *a_matProjection;
	matView = glm::lookAt(vEye, vView, vUpVector);

	vView = vView - vEye;
	vView = glm::normalize(vView);
	vQuad1 = glm::cross(vView, vUpVector);

	vQuad1 = glm::normalize(vQuad1);
	vQuad2 = glm::cross(vView, vQuad1);
	vQuad2 = glm::normalize(vQuad2);
}