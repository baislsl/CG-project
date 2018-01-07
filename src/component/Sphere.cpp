#include <TextureManager.h>
#include "Sphere.h"

Sphere::Sphere(int m, int n, std::string textureFileName)
{
	glGenBuffers(1, &EBO);
	if (!textureFileName.empty())
	{
		usingTexture = true;
		texture = TextureManager::getTextureManagerInstance()->load(textureFileName);
	}

	nrVert = m * n * 4;
	float *verts = new float[nrVert * 3];
	float *texCoords = new float[nrVert * 2];
	float stepAngZ = float(M_PI) / m;//纵向角度每次增加的值
	float stepAngXY = 2 * float(M_PI) / n;//横向角度每次增加的值
	float angZ = 0.0;//初始的纵向角度
	float angXY = 0.0;//初始的横向角度
	int index = 0;
	int indexTex = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			//构造一个顶点
			float x1 = sin(angZ) * cos(angXY);
			float y1 = sin(angZ) * sin(angXY);
			float z1 = cos(angZ);
			verts[index] = x1;
			index++;
			verts[index] = y1;
			index++;
			verts[index] = z1;
			index++;
			float v1 = angZ / float(M_PI);
			float u1 = angXY / float(M_PI * 2);
			texCoords[indexTex] = u1;
			indexTex++;
			texCoords[indexTex] = v1;
			indexTex++;

			float x2 = sin(angZ + stepAngZ) * cos(angXY);
			float y2 = sin(angZ + stepAngZ) * sin(angXY);
			float z2 = cos(angZ + stepAngZ);
			verts[index] = x2;
			index++;
			verts[index] = y2;
			index++;
			verts[index] = z2;
			index++;
			float v2 = (angZ + stepAngZ) / float(M_PI);
			float u2 = angXY / float(M_PI * 2);
			texCoords[indexTex] = u2;
			indexTex++;
			texCoords[indexTex] = v2;
			indexTex++;


			float x3 = sin(angZ + stepAngZ) * cos(angXY + stepAngXY);
			float y3 = sin(angZ + stepAngZ) * sin(angXY + stepAngXY);
			float z3 = cos(angZ + stepAngZ);
			verts[index] = x3;
			index++;
			verts[index] = y3;
			index++;
			verts[index] = z3;
			index++;
			float v3 = (angZ + stepAngZ) / float(M_PI);
			float u3 = (angXY + stepAngXY) / float(M_PI * 2);
			texCoords[indexTex] = u3;
			indexTex++;
			texCoords[indexTex] = v3;
			indexTex++;

			float x4 = sin(angZ) * cos(angXY + stepAngXY);
			float y4 = sin(angZ) * sin(angXY + stepAngXY);
			float z4 = cos(angZ);
			verts[index] = x4;
			index++;
			verts[index] = y4;
			index++;
			verts[index] = z4;
			index++;
			float v4 = angZ / float(M_PI);
			float u4 = (angXY + stepAngXY) / float(M_PI * 2);
			texCoords[indexTex] = u4;
			indexTex++;
			texCoords[indexTex] = v4;
			indexTex++;

			angXY += stepAngXY;
		}
		angXY = 0.0;//每次横向到达2PI角度则横向角度归0
		angZ += stepAngZ;
	}

	float *vertices = new float[nrVert * 8];
	for (int i = 0; i < nrVert; i++)
	{
		vertices[i * 8] = verts[i * 3];
		vertices[i * 8 + 1] = verts[i * 3 + 1];
		vertices[i * 8 + 2] = verts[i * 3 + 2];
		vertices[i * 8 + 3] = verts[i * 3];
		vertices[i * 8 + 4] = verts[i * 3 + 1];
		vertices[i * 8 + 5] = verts[i * 3 + 2];
		vertices[i * 8 + 6] = texCoords[i * 2];
		vertices[i * 8 + 7] = texCoords[i * 2 + 1];

	}

	delete[] verts;
	delete[] texCoords;
	unsigned int *indices = new unsigned int[m * n * 6];
	for (unsigned int i = 0; i < m * n; i++)
	{
		indices[i * 6] = i * 4;
		indices[i * 6 + 1] = i * 4 + 1;
		indices[i * 6 + 2] = i * 4 + 3;
		indices[i * 6 + 3] = i * 4 + 2;
		indices[i * 6 + 4] = i * 4 + 1;
		indices[i * 6 + 5] = i * 4 + 3;
	}
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nrVert * 8, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m * n * 6, indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	delete[] vertices;
}

void Sphere::render(const Shader &shader, const Camera &camera)
{
	shader.setMat4("model", modelMatrix);
	shader.setVec3("viewPos", camera.Position);
	shader.setVec3("material.diffuse", material.diffuse);
	shader.setVec3("material.specular", material.specular);
	shader.setVec3("material.ambient", material.ambient);
	shader.setBool("usingTexture", usingTexture);
	if (usingTexture) glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, nrVert);
	glDrawElements(GL_TRIANGLES, nrVert / 2 * 3, GL_UNSIGNED_INT, 0);
}
