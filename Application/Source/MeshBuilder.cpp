#include "MeshBuilder.h"
#include "LoadOBJ.h"
#include <vector>
#include <GL\glew.h>
#include <MyMath.h>


/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	v.pos.Set(lengthX * -0.5, 0, 0);
	v.color.Set(1.f, 0.f, 0.f);
	vertex_buffer_data.push_back(v);

	v.pos.Set(lengthX * 0.5, 0, 0);
	v.color.Set(1.f, 0.f, 0.f);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, lengthY * -0.5, 0);
	v.color.Set(0.f, 1.f, 0.f);
	vertex_buffer_data.push_back(v);
	
	v.pos.Set(0, lengthY * 0.5, 0);
	v.color.Set(0.f, 1.f, 0.f);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, 0, lengthZ * -0.5);
	v.color.Set(0.f, 1.f, 0.f);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, 0, lengthZ * 0.5);
	v.color.Set(0.f, 0.f, 1.f);
	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_MODE::DRAW_LINES;
	mesh->indexSize = index_buffer_data.size();
	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, float size)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	v.normal.Set(0, 1, 0);

	float s = 0.5f * size;
	float texturesize = 1;

	v.pos.Set(-s, 0, s);
	v.texCoord.Set(0, 0);
	v.normal = Vector3(0, 1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(s, 0, s);
	v.texCoord.Set(texturesize, 0);
	v.normal = Vector3(0, 1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	
	v.pos.Set(s, 0, -s);
	v.texCoord.Set(texturesize, texturesize);
	v.normal = Vector3(0, 1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(-s, 0.f, -s);
	v.texCoord.Set(0, texturesize);
	v.normal = Vector3(0, 1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);



	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_1), color_buffer_data_1, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_MODE::DRAW_TRIANGLES;
	mesh->indexSize = index_buffer_data.size();
	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	v.color = color;
	v.pos.Set((lengthX * 0.5), (lengthY * -0.5), (lengthZ * 0.5));
	vertex_buffer_data.push_back(v);

	v.pos.Set((lengthX * 0.5), (lengthY * 0.5), (lengthZ * 0.5));
	vertex_buffer_data.push_back(v);

	v.pos.Set((lengthX * -0.5), (lengthY * -0.5), (lengthZ * 0.5));
	vertex_buffer_data.push_back(v);

	v.pos.Set((lengthX * -0.5), (lengthY * 0.5), (lengthZ * 0.5));
	vertex_buffer_data.push_back(v);

	v.pos.Set((lengthX * 0.5), (lengthY * -0.5), (lengthZ * -0.5));
	vertex_buffer_data.push_back(v);

	v.pos.Set((lengthX * 0.5), (lengthY * 0.5), (lengthZ * -0.5));
	vertex_buffer_data.push_back(v);

	v.pos.Set((lengthX * -0.5), (lengthY * -0.5), (lengthZ * -0.5));
	vertex_buffer_data.push_back(v);

	v.pos.Set((lengthX * -0.5), (lengthY * 0.5), (lengthZ * -0.5));
	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(1);

	index_buffer_data.push_back(4);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(6);

	index_buffer_data.push_back(1);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(3);

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_1), color_buffer_data_1, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_MODE::DRAW_TRIANGLES;
	mesh->indexSize = index_buffer_data.size();
	return mesh;
}

Mesh* MeshBuilder::GenerateWireCube(const std::string& meshName, Color color, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	v.color = color;
	v.pos.Set((lengthX * 0.5), (lengthY * -0.5), (lengthZ * 0.5));
	vertex_buffer_data.push_back(v);

	v.pos.Set((lengthX * 0.5), (lengthY * 0.5), (lengthZ * 0.5));
	vertex_buffer_data.push_back(v);

	v.pos.Set((lengthX * -0.5), (lengthY * -0.5), (lengthZ * 0.5));
	vertex_buffer_data.push_back(v);

	v.pos.Set((lengthX * -0.5), (lengthY * 0.5), (lengthZ * 0.5));
	vertex_buffer_data.push_back(v);

	v.pos.Set((lengthX * 0.5), (lengthY * -0.5), (lengthZ * -0.5));
	vertex_buffer_data.push_back(v);

	v.pos.Set((lengthX * 0.5), (lengthY * 0.5), (lengthZ * -0.5));
	vertex_buffer_data.push_back(v);

	v.pos.Set((lengthX * -0.5), (lengthY * -0.5), (lengthZ * -0.5));
	vertex_buffer_data.push_back(v);

	v.pos.Set((lengthX * -0.5), (lengthY * 0.5), (lengthZ * -0.5));
	vertex_buffer_data.push_back(v);

	{
		index_buffer_data.push_back(0);
		index_buffer_data.push_back(1);
		
		index_buffer_data.push_back(2);
		index_buffer_data.push_back(3);
		
		index_buffer_data.push_back(3);
		index_buffer_data.push_back(0);

		index_buffer_data.push_back(1);
		index_buffer_data.push_back(4);

		index_buffer_data.push_back(4);
		index_buffer_data.push_back(5);

		index_buffer_data.push_back(5);
		index_buffer_data.push_back(6);

		index_buffer_data.push_back(6);
		index_buffer_data.push_back(7);

		index_buffer_data.push_back(7);
		index_buffer_data.push_back(2);

		index_buffer_data.push_back(2);
		index_buffer_data.push_back(0);

		index_buffer_data.push_back(0);
		index_buffer_data.push_back(4);

		index_buffer_data.push_back(4);
		index_buffer_data.push_back(6);

		index_buffer_data.push_back(6);
		index_buffer_data.push_back(2);

		index_buffer_data.push_back(6);
		index_buffer_data.push_back(0);
		
		index_buffer_data.push_back(1);
		index_buffer_data.push_back(3);

		index_buffer_data.push_back(3);
		index_buffer_data.push_back(7);

		index_buffer_data.push_back(7);
		index_buffer_data.push_back(5);

		index_buffer_data.push_back(5);
		index_buffer_data.push_back(1);

		index_buffer_data.push_back(3);
		index_buffer_data.push_back(5);
	}
	
	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_1), color_buffer_data_1, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_MODE::DRAW_LINES;
	mesh->indexSize = index_buffer_data.size();
	return mesh;
}

Mesh* MeshBuilder::GenerateCircle(const std::string& meshName, std::string axis, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	const float PI = 3.1415926f;
	if(axis == "z")
		for (int i = 0; i < 360; i++)
		{
			float theta = (i * PI) / 180.0f;
			float x = radius * cosf(theta);//calculate the x component
			float y = radius * sinf(theta);//calculate the y component
			float z = 0.f;

			v.pos.Set(x, y, z);
			v.color.Set(1.f, 0.f, 0.f);
			vertex_buffer_data.push_back(v);
			index_buffer_data.push_back(i);
		}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_1), color_buffer_data_1, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_MODE::DRAW_TRIANGLE_FAN;
	mesh->indexSize = index_buffer_data.size();
	return mesh;
}

Mesh* MeshBuilder::GenerateSphere(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float radius)
{	
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	
	float degreePerStack = 180.f / numStack;
	float degreePerSlice = 360.f / numSlice;
	
	for (unsigned stack = 0; stack < numStack + 1; ++stack)
	{
		float phi = -90 + stack * degreePerStack;
		for (unsigned slice = 0; slice < numSlice + 1; ++slice)
		{
			float theta = slice * degreePerSlice;
			v.pos.Set(radius * cosf(Math::DegreeToRadian(phi)) * cosf(Math::DegreeToRadian(theta)), radius * sinf(Math::DegreeToRadian(phi)), radius * cosf(Math::DegreeToRadian(phi)) * sinf(Math::DegreeToRadian(theta)));
			v.color = color;
			v.normal.Set( cosf(Math::DegreeToRadian(phi)) * cosf(Math::DegreeToRadian(theta)),  sinf(Math::DegreeToRadian(phi)),  cosf(Math::DegreeToRadian(phi)) * sinf(Math::DegreeToRadian(theta)));
			vertex_buffer_data.push_back(v);
		}
	}
	for (unsigned stack = 0; stack < numStack; ++stack)
	{
		for (unsigned slice = 0; slice < numSlice + 1; ++slice)
		{
			index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
		}
	}
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_MODE::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();
	return mesh;
}

Mesh* MeshBuilder::GenerateHemisphere(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float radius, bool hollow)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	int idx = 0;

	if (!hollow)
		for (int theta = 0; theta <= 360; theta += 10)
		{
			v.normal.Set(0, -1, 0);
			v.pos.Set(0, 0, 0);
			v.color = color;
			vertex_buffer_data.push_back(v);
			index_buffer_data.push_back(idx++);

			v.normal.Set(0, -1, 0);
			v.pos.Set(radius * cosf(Math::DegreeToRadian(theta)), 0, radius * sinf(Math::DegreeToRadian(theta)));
			v.color = color;
			vertex_buffer_data.push_back(v);
			index_buffer_data.push_back(idx++);
		}
	for (int phi = 0; phi < 90; phi += 10)
	{
		for (int theta = 0; theta <= 360; theta += 10) //slice
		{
			v.normal.Set(radius * cosf(Math::DegreeToRadian(phi)) * cosf(Math::DegreeToRadian(theta)), radius * sinf(Math::DegreeToRadian(phi)), radius * cosf(Math::DegreeToRadian(phi)) * sinf(Math::DegreeToRadian(theta)));
			v.pos.Set(radius * cosf(Math::DegreeToRadian(phi)) * cosf(Math::DegreeToRadian(theta)), radius * sinf(Math::DegreeToRadian(phi)), radius * cosf(Math::DegreeToRadian(phi)) * sinf(Math::DegreeToRadian(theta)));
			v.color = color;
			vertex_buffer_data.push_back(v);
			index_buffer_data.push_back(idx++);

			v.normal.Set(radius * cosf(Math::DegreeToRadian(phi + 10)) * cosf(Math::DegreeToRadian(theta)), radius * sinf(Math::DegreeToRadian(phi + 10)), radius * cosf(Math::DegreeToRadian(phi + 10)) * sinf(Math::DegreeToRadian(theta)));
			v.pos.Set(radius * cosf(Math::DegreeToRadian(phi + 10)) * cosf(Math::DegreeToRadian(theta)), radius * sinf(Math::DegreeToRadian(phi + 10)), radius * cosf(Math::DegreeToRadian(phi + 10)) * sinf(Math::DegreeToRadian(theta)));
			v.color = color;
			vertex_buffer_data.push_back(v);
			index_buffer_data.push_back(idx++);
		}
	}
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_MODE::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();
	return mesh;
}

Mesh* MeshBuilder::GenerateCylinder(const std::string& meshName, Color color, float numStack, float height, float radius, bool hollow)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	int idx = 0;
	float stackHeight = height / numStack;

	if (!hollow)
	{
		for (int theta = 0; theta <= 360; theta += 10) //top
		{
			v.pos.Set(0, -height / 2, 0);
			v.normal.Set(0, -height / 2, 0);;
			v.color = color;
			vertex_buffer_data.push_back(v);
			index_buffer_data.push_back(idx++);

			v.pos.Set(radius * cosf(Math::DegreeToRadian(theta)), -height / 2, radius * sinf(Math::DegreeToRadian(theta)));
			v.normal.Set(radius * cosf(Math::DegreeToRadian(theta)), -height / 2, radius * sinf(Math::DegreeToRadian(theta)));
			v.color = color;
			vertex_buffer_data.push_back(v);
			index_buffer_data.push_back(idx++);
		}
	}

	for (int stack = 0; stack < numStack; ++stack)
	{
		for (int theta = 0; theta <= 360; theta += 10)
		{
			v.pos.Set(radius * cosf(Math::DegreeToRadian(theta)), -height / 2 + stack * stackHeight, radius * sinf(Math::DegreeToRadian(theta)));
			v.normal.Set(radius * cosf(Math::DegreeToRadian(theta)), 0, radius * sinf(Math::DegreeToRadian(theta)));
			v.color = color;
			vertex_buffer_data.push_back(v);
			index_buffer_data.push_back(idx++);

			v.pos.Set(radius * cosf(Math::DegreeToRadian(theta)), -height / 2 + (stack + 1) * stackHeight, radius * sinf(Math::DegreeToRadian(theta)));
			v.normal.Set(radius * cosf(Math::DegreeToRadian(theta)), 0, radius * sinf(Math::DegreeToRadian(theta)));
			v.color = color;
			vertex_buffer_data.push_back(v);
			index_buffer_data.push_back(idx++);


		}
	}

	if (!hollow)
	{
		for (int theta = 0; theta <= 360; theta += 10) //bottom
		{
			v.pos.Set(radius * cosf(Math::DegreeToRadian(theta)), height / 2, radius * sinf(Math::DegreeToRadian(theta)));
			v.normal.Set(radius * cosf(Math::DegreeToRadian(theta)), height / 2, radius * sinf(Math::DegreeToRadian(theta)));
			v.color = color;
			vertex_buffer_data.push_back(v);
			index_buffer_data.push_back(idx++);

			v.pos.Set(0, height * 0.5, 0);
			v.normal.Set(0, height * 0.5, 0);;
			v.color = color;
			vertex_buffer_data.push_back(v);
			index_buffer_data.push_back(idx++);
		}
	}


	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_MODE::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();
	return mesh;
}

Mesh* MeshBuilder::GenConeFrust(const std::string& meshName, Color color, float numStack, float height, float topradius, Position topoffset, float btmradius, bool hollow)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	int idx = 0;
	float stackHeight = height / numStack;

	if (!hollow)
	{
		for (int theta = 0; theta <= 360; theta += 10) //bottom
		{
			v.pos.Set(0, -height / 2, 0);
			v.normal.Set(0, -height / 2, 0);;
			v.color = color;
			vertex_buffer_data.push_back(v);
			index_buffer_data.push_back(idx++);

			v.pos.Set(btmradius * cosf(Math::DegreeToRadian(theta)), -height / 2, btmradius * sinf(Math::DegreeToRadian(theta)));
			v.normal.Set(btmradius * cosf(Math::DegreeToRadian(theta)), -height / 2, btmradius * sinf(Math::DegreeToRadian(theta)));
			v.color = color;
			vertex_buffer_data.push_back(v);
			index_buffer_data.push_back(idx++);
		}
	}

	for (int stack = 0; stack < numStack; ++stack)
	{
		for (int theta = 0; theta <= 360; theta += 10)
		{
			v.pos.Set(btmradius * cosf(Math::DegreeToRadian(theta)), -height / 2 + stack * stackHeight, btmradius * sinf(Math::DegreeToRadian(theta)));
			v.normal.Set(btmradius * cosf(Math::DegreeToRadian(theta)), 0, btmradius * sinf(Math::DegreeToRadian(theta)));
			v.color = color;
			vertex_buffer_data.push_back(v);
			index_buffer_data.push_back(idx++);

			v.pos.Set(topradius * cosf(Math::DegreeToRadian(theta)) + topoffset.x, -height / 2 + (stack + 1) * stackHeight + topoffset.y, topradius * sinf(Math::DegreeToRadian(theta)) + topoffset.z);
			v.normal.Set(topradius * cosf(Math::DegreeToRadian(theta)), 0, topradius * sinf(Math::DegreeToRadian(theta)));
			v.color = color;
			vertex_buffer_data.push_back(v);
			index_buffer_data.push_back(idx++);


		}
	}

	if (!hollow)
	{
		for (int theta = 0; theta <= 360; theta += 10) //top
		{
			v.pos.Set(topradius * cosf(Math::DegreeToRadian(theta)) + topoffset.x, height / 2 + topoffset.y, topradius * sinf(Math::DegreeToRadian(theta)) + topoffset.z);
			v.normal.Set(topradius * cosf(Math::DegreeToRadian(theta)) + topoffset.x, height / 2 + topoffset.y, topradius * sinf(Math::DegreeToRadian(theta)) + topoffset.z);
			v.color = color;
			vertex_buffer_data.push_back(v);
			index_buffer_data.push_back(idx++);

			v.pos.Set(0 + topoffset.x, height * 0.5 + topoffset.y, 0 + topoffset.z);
			v.normal.Set(0 + topoffset.x, height * 0.5 + topoffset.y, 0 + topoffset.z);
			v.color = color;
			vertex_buffer_data.push_back(v);
			index_buffer_data.push_back(idx++);
		}
	}


	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_MODE::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();
	return mesh;
}

Mesh* MeshBuilder::GenerateOBJ(const std::string& meshName, const std::string& file_path)
{
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
	if (!success)
	{
		return NULL;
	}
	else
	{
		//Index the vertices, texcoords & normals properly
		std::vector<Vertex> vertex_buffer_data;
		std::vector<GLuint> index_buffer_data;
		IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
		//Create the mesh and call glBindBuffer, glBufferData
		//Use triangle list and remember to set index size

		Mesh* mesh = new Mesh(meshName);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
		mesh->mode = Mesh::DRAW_MODE::DRAW_TRIANGLES;
		mesh->indexSize = index_buffer_data.size();
		return mesh;
	}
}

Mesh* MeshBuilder::GenerateText(const std::string& meshName, unsigned numRow, unsigned numCol, int TextDataArr[])
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	
	//16x16 Characters in 1 tga
	int idx = 0;
	float x = 0, y = 0;
	float width = 1.f / numCol;
	float height = 1.f / numRow;
	unsigned offset = 0;

	v.color.Set(0, 1, 0);

	for (unsigned row = 0; row < numRow; ++row)
	{
		y = 0.5f;
		for (unsigned col = 0; col < numCol; ++col)
		{
			//Task: Add 4 vertices into vertex_buffer_data
			x = TextDataArr[idx++] / 128.f;

			v.pos.Set(x, y, 0.f);//top right
			v.normal.Set(0, 0, 1);
			v.texCoord.Set(width * (col + x*2), height * (numRow - row));
			vertex_buffer_data.push_back(v);
			
			v.pos.Set(-x, y, 0.f); //top left
			v.normal.Set(0, 0, 1);
			v.texCoord.Set(width * col, height * (numRow - row));
			vertex_buffer_data.push_back(v);
			
			v.pos.Set(-x, -y, 0.f);//bot left
			v.normal.Set(0, 0, 1);
			v.texCoord.Set(width * col, height * (numRow - 1 - row));
			vertex_buffer_data.push_back(v);

			v.pos.Set(x, -y, 0.f);//bot right
			v.normal.Set(0, 0, 1);
			v.texCoord.Set(width * (col + x*2), height * (numRow - 1 - row));
			vertex_buffer_data.push_back(v);

			//Task: Add 6 indices into index_buffer_data
			index_buffer_data.push_back(0 + offset);
			index_buffer_data.push_back(1 + offset);
			index_buffer_data.push_back(2 + offset);
			index_buffer_data.push_back(0 + offset);
			index_buffer_data.push_back(2 + offset);
			index_buffer_data.push_back(3 + offset);

			offset += 4;
		}
	}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_MODE::DRAW_TRIANGLES;
	mesh->indexSize = index_buffer_data.size();
	return mesh;
}


Mesh* MeshBuilder::GenerateOBJMTL(const std::string& meshName, const std::string& file_path, const std::string& mtl_path)
{
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	std::vector<Material> materials;
	bool success = LoadOBJMTL(file_path.c_str(), mtl_path.c_str(), vertices, uvs, normals, materials);

	if (!success)
		return NULL;

	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
	Mesh* mesh = new Mesh(meshName);
	for (Material& material : materials)
		mesh->materials.push_back(material);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_MODE::DRAW_TRIANGLES;
	return mesh;
}
