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
#include <ray/light_component.h>
#include <ray/game_server.h>
#include <ray/render_features.h>

_NAME_BEGIN

__ImplementSubClass(LightComponent, GameComponent)

LightComponent::LightComponent() noexcept
{
    _light = std::make_shared<Light>();
}

LightComponent::~LightComponent() noexcept
{
}

void
LightComponent::setRange(float range) noexcept
{
    _light->setRange(range);
}

void
LightComponent::setIntensity(float intensity) noexcept
{
    _light->setIntensity(intensity);
}

void
LightComponent::setExponent(float value) noexcept
{
    _light->setExponent(value);
}

void
LightComponent::setSpotAngle(float value) noexcept
{
    _light->setSpotAngle(value);
}

void
LightComponent::setSpotInnerCone(float value) noexcept
{
    _light->setSpotInnerCone(value);
}

void
LightComponent::setSpotOuterCone(float value) noexcept
{
    _light->setSpotOuterCone(value);
}

float
LightComponent::getRange() const noexcept
{
    return _light->getRange();
}

float
LightComponent::getIntensity() const noexcept
{
    return _light->getIntensity();
}

float
LightComponent::getExponent() const noexcept
{
    return _light->getExponent();
}

float
LightComponent::getSpotAngle() const noexcept
{
    return _light->getSpotAngle();
}

float
LightComponent::getSpotInnerCone() const noexcept
{
    return _light->getSpotInnerCone();
}

float
LightComponent::getSpotOuterCone() const noexcept
{
    return _light->getSpotOuterCone();
}

void
LightComponent::setShadow(bool shadow) noexcept
{
    _light->setShadow(shadow);
}

bool
LightComponent::getShadow() const noexcept
{
    return _light->getShadow();
}

void
LightComponent::setLightColor(const Vector3& color) noexcept
{
    _light->setLightColor(color);
}

const Vector3&
LightComponent::getLightColor() const noexcept
{
    return _light->getLightColor();
}

void
LightComponent::setLightType(LightType type) noexcept
{
    _light->setLightType(type);
}

LightType
LightComponent::getLightType() const noexcept
{
    return _light->getLightType();
}

void
LightComponent::onActivate() noexcept
{
    auto renderer = this->getGameObject()->getGameServer()->getFeature<RenderFeatures>();
    if (renderer)
    {
        auto renderScene = renderer->getRenderScene(this->getGameObject()->getGameScene());
        if (renderScene)
        {
            auto dir = this->getGameObject()->getTranslate() - this->getGameObject()->getLookAt();
            _light->setup();
            _light->setLightDirection(~dir);
            _light->setTransform(this->getGameObject()->getTransform());
            _light->setRenderScene(renderScene.get());
        }
    }
}

void
LightComponent::onDeactivate() noexcept
{
    _light->close();
}

void
LightComponent::onMoveAfter() noexcept
{
    auto dir = getGameObject()->getTranslate() - getGameObject()->getLookAt();
    _light->setLightDirection(dir);
    _light->setTransform(this->getGameObject()->getTransform());
}

GameComponentPtr
LightComponent::clone() const noexcept
{
    auto instance = std::make_shared<LightComponent>();
    instance->_light = _light->clone();
    return instance;
}

_NAME_END