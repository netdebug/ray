// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2015.
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
#include <ray/fog.h>

_NAME_BEGIN

Fog::Fog() noexcept
{
}

Fog::~Fog() noexcept
{
}

void
Fog::onActivate(RenderPipeline& pipeline) except
{
	_material = pipeline.createMaterial("sys:fx/fog.glsl");
	_fog = _material->getTech(RenderQueue::RQ_POSTPROCESS)->getPass("fog");
	_fogFalloff = _material->getParameter("fogFalloff");
	_fogDensity = _material->getParameter("fogDensity");
	_fogColor = _material->getParameter("fogColor");

	_fogFalloff->assign(10.0f);
	_fogDensity->assign(0.0001f);
	_fogColor->assign(Vector3(0.0, 0.3, 0.99));
}

void
Fog::onDeactivate(RenderPipeline& pipeline) except
{
}

void
Fog::onRender(RenderPipeline& pipeline, RenderTexturePtr texture) except
{
	pipeline.setRenderTexture(texture);
	pipeline.drawSceneQuad(_fog);
}

_NAME_END