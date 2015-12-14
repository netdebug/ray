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
#ifndef _H_OGL_SHADER_H_
#define _H_OGL_SHADER_H_

#include "ogl_canvas.h"

_NAME_BEGIN

class OGLShaderVariant final : public ShaderVariant
{
public:
	OGLShaderVariant() noexcept;
	virtual ~OGLShaderVariant() noexcept;

	void setLocation(GLint location) noexcept;
	GLint getLocation() const noexcept;

	void setBindingProgram(GLuint program) noexcept;
	GLuint getBindingProgram() const noexcept;

	void assign(bool value) noexcept;
	void assign(int value) noexcept;
	void assign(const int2& value) noexcept;
	void assign(float value) noexcept;
	void assign(const float2& value) noexcept;
	void assign(const float3& value) noexcept;
	void assign(const float4& value) noexcept;
	void assign(const float3x3& value) noexcept;
	void assign(const float4x4& value) noexcept;
	void assign(const std::vector<float>& value) noexcept;
	void assign(const std::vector<float2>& value) noexcept;
	void assign(const std::vector<float3>& value) noexcept;
	void assign(const std::vector<float4>& value) noexcept;

private:
	OGLShaderVariant(const OGLShaderVariant&) noexcept = delete;
	OGLShaderVariant& operator=(const OGLShaderVariant&) noexcept = delete;

private:
	GLint _location;
	GLuint _bindingProgram;
};

class OGLShaderUniform final : public ShaderUniform
{
public:
	OGLShaderUniform() noexcept;
	~OGLShaderUniform() noexcept;

	void setType(ShaderVariantType type) noexcept;

	void setLocation(GLint location) noexcept;
	GLint getLocation() const noexcept;

	void setBindingProgram(GLuint program) noexcept;
	GLuint getBindingProgram() const noexcept;

private:
	OGLShaderUniform(const OGLShaderUniform&) noexcept = delete;
	OGLShaderUniform& operator=(const OGLShaderUniform&) noexcept = delete;

private:
	OGLShaderVariant _value;
};

class OGLShader final : public Shader
{
public:
	OGLShader() noexcept;
	~OGLShader() noexcept;

	virtual bool setup() except;
	virtual void close() noexcept;

	virtual std::size_t getInstanceID() const noexcept;

private:

	GLuint _instance;
};

class OGLShaderObject final : public ShaderObject
{
public:
	OGLShaderObject() noexcept;
	~OGLShaderObject() noexcept;

	virtual bool setup() except;
	virtual void close() noexcept;

	void setActive(bool active) noexcept;
	bool getActive() noexcept;

	virtual void addShader(ShaderPtr shader) noexcept;
	virtual void removeShader(ShaderPtr shader) noexcept;

	virtual const Shaders& getShaders() const noexcept;

	virtual std::size_t getInstanceID() noexcept;

	virtual ShaderAttributes&  getActiveAttributes() noexcept;
	virtual ShaderUniforms&    getActiveUniforms() noexcept;

private:

	void _initActiveAttribute() noexcept;
	void _initActiveUniform() noexcept;
	void _initActiveUniformBlock() noexcept;

private:

	bool _isActive;

	GLuint _program;

	Shaders _shaders;

	ShaderUniforms    _activeUniforms;
	ShaderAttributes  _activeAttributes;
};

_NAME_END

#endif