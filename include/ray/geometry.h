// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2016.
// +----------------------------------------------------------------------
// | * Redistribution and use of this software in source and binary forms,
// |   with or without modification, are permitted provided that the following
// |   conditions are met:
// |
// | * Redistributions of source code must retain the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer.
// |
// | * Redistributions in binary form must reproduce the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer in the documentation and/or other
// |   materials provided with the distribution.
// |
// | * Neither the name of the ray team, nor the names of its
// |   contributors may be used to endorse or promote products
// |   derived from this software without specific prior
// |   written permission of the ray team.
// |
// | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// | "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// | LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// | A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// | OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// | SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// | LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// | DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// | THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// | (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// | OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// +----------------------------------------------------------------------
#ifndef _H_GEOMETRY_H_
#define _H_GEOMETRY_H_

#include <ray/render_object.h>

_NAME_BEGIN

class EXPORT Geometry final : public RenderObject
{
	__DeclareSubClass(Geometry, RenderObject)
public:
	Geometry() noexcept;
	~Geometry() noexcept;

	void setMaterial(MaterialPtr material) noexcept;
	MaterialPtr getMaterial() noexcept;

	void setRenderMesh(RenderMeshPtr mesh) noexcept;
	RenderMeshPtr getRenderMesh() noexcept;

	void setGraphicsIndirect(GraphicsIndirectPtr renderable) noexcept;
	GraphicsIndirectPtr getGraphicsIndirect() noexcept;

private:
	void _updatePipeline() noexcept;

private:
	void onAddRenderData(RenderDataManager& manager) noexcept;
	void onRenderObject(RenderPipeline& pipelineContext, RenderQueue queue, MaterialTechPtr tech) noexcept;

private:
	static RenderQueue stringToRenderQueue(const std::string& techName) noexcept;

private:
	MaterialPtr _material;
	RenderMeshPtr _mesh;
	MaterialTechPtr _techniques[RenderQueue::RenderQueueRangeSize];
	GraphicsIndirectPtr _renderable;
	GraphicsPipelinePtr _pipeline;
};

_NAME_END

#endif