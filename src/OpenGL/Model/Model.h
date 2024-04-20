#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "../Renderer/OGLRenderData.h"

class Model
{
public:
	void Init();
	OGLMesh GetVertexData();

private:
	OGLMesh m_VertexData{};
};