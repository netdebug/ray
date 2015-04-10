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
#include <ray/render_buffer.h>

_NAME_BEGIN

VertexStreams::VertexStreams() noexcept
    : _data(nullptr)
    , _length(0)
{
}

VertexStreams::~VertexStreams() noexcept
{
    this->release();
}

void
VertexStreams::resize(std::size_t length) noexcept
{
    if (_length < length)
    {
        if (_data)
        {
            delete _data;
            _data = nullptr;
        }

        if (!_data)
        {
            _data = new char[length];
        }

        _length = length;
    }
}

void
VertexStreams::release() noexcept
{
    if (_data)
    {
        delete _data;
        _data = nullptr;
    }
}

char*
VertexStreams::data() const noexcept
{
    return _data;
}

VertexComponent::VertexComponent() noexcept
    : _attrib(VertexAttrib::GPU_ATTRIB_POSITION)
    , _format(VertexFormat::GPU_VERTEX_FLOAT)
{
}

VertexComponent::VertexComponent(VertexAttrib attrib, VertexFormat format) noexcept
    : _attrib(attrib)
    , _format(format)
{
}

VertexComponent::~VertexComponent() noexcept
{
}

VertexAttrib
VertexComponent::getVertexAttrib() const noexcept
{
    return _attrib;
}

VertexFormat
VertexComponent::getVertexFormat() const noexcept
{
    return _format;
}

int
VertexComponent::getVertexSize() const noexcept
{
    switch (_format)
    {
    case VertexFormat::GPU_VERTEX_FLOAT:
        return 1;
    case VertexFormat::GPU_VERTEX_FLOAT2:
        return 2;
    case VertexFormat::GPU_VERTEX_FLOAT3:
        return 3;
    case VertexFormat::GPU_VERTEX_FLOAT4:
        return 4;
    }

    assert(false);
    return 0;
}

int
VertexComponent::getVertexByteSize() const noexcept
{
    switch (_format)
    {
    case VertexFormat::GPU_VERTEX_FLOAT:
        return 4;
    case VertexFormat::GPU_VERTEX_FLOAT2:
        return 8;
    case VertexFormat::GPU_VERTEX_FLOAT3:
        return 12;
    case VertexFormat::GPU_VERTEX_FLOAT4:
        return 16;
    }

    assert(false);
    return 0;
}

void
VertexLayout::setVertexComponents(const VertexComponents& component) noexcept
{
    _components = component;

    _byteSize = 0;
    for (auto& it : _components)
    {
        _byteSize += it.getVertexByteSize();
    }
}

const VertexComponents&
VertexLayout::getVertexComponents() const noexcept
{
    return _components;
}

std::size_t
VertexLayout::getVertexByteSize() const noexcept
{
    return _byteSize;
}

VertexBuffer::VertexBuffer() noexcept
{
}

VertexBuffer::~VertexBuffer() noexcept
{
}

VertexLayout&
VertexBuffer::getVertexLayout() noexcept
{
    return _vertexLayout;
}

const VertexLayout&
VertexBuffer::getVertexLayout() const noexcept
{
    return _vertexLayout;
}

IndexBuffer::IndexBuffer() noexcept
{
}

IndexBuffer::~IndexBuffer() noexcept
{
}

void
IndexBuffer::setIndexType(IndexType type) noexcept
{
    _type = type;
}

IndexType
IndexBuffer::getIndexType() const noexcept
{
    return _type;
}

VertexBufferData::VertexBufferData() noexcept
    : _vertexCount(0)
    , _vertexSize(0)
    , _vertexUsage(VertexUsage::GPU_USAGE_STATIC)
{
}

VertexBufferData::~VertexBufferData() noexcept
{
    this->close();
}

void
VertexBufferData::setup(std::size_t count, std::size_t size, VertexUsage usage) noexcept
{
    assert(0 != count && 0 != size);
    _vertexCount = count;
    _vertexSize = size;
    _vertexUsage = usage;
    _vertexStreams.resize(count * size);
}

void
VertexBufferData::close() noexcept
{
    _vertexStreams.release();
}

void
VertexBufferData::resize(std::size_t count)
{
    _vertexStreams.resize(count * _vertexSize);
    _vertexCount = count;
}

std::size_t
VertexBufferData::getVertexCount() const noexcept
{
    return _vertexCount;
}

std::size_t
VertexBufferData::getVertexSize() const noexcept
{
    return _vertexSize;
}

std::size_t
VertexBufferData::getVertexByteSize() const noexcept
{
    return _vertexLayout.getVertexByteSize();
}

VertexUsage
VertexBufferData::getVertexUsage() const noexcept
{
    return _vertexUsage;
}

void*
VertexBufferData::data() noexcept
{
    return _vertexStreams.data();
}

const void*
VertexBufferData::data() const noexcept
{
    return _vertexStreams.data();
}

void
VertexBufferData::setVertexComponents(const VertexComponents& components) noexcept
{
    return _vertexLayout.setVertexComponents(components);;
}

const VertexComponents&
VertexBufferData::getVertexComponents() const noexcept
{
    return _vertexLayout.getVertexComponents();
}

IndexBufferData::IndexBufferData() noexcept
    : _indexCount(0)
    , _indexType(IndexType::GPU_UINT16)
    , _indexUsage(VertexUsage::GPU_USAGE_STATIC)
{
}

IndexBufferData::~IndexBufferData() noexcept
{
    this->close();
}

void
IndexBufferData::setup(std::size_t num, IndexType type, VertexUsage usage) noexcept
{
    assert(0 != num);

    _indexCount = num;
    _indexType = type;
    _indexUsage = usage;
    if (type == IndexType::GPU_UINT16)
        _indexStreams.resize(num * sizeof(std::int16_t));
    else if (type == IndexType::GPU_UINT32)
        _indexStreams.resize(num * sizeof(std::int32_t));
}

void
IndexBufferData::close() noexcept
{
    _indexStreams.release();
}

std::size_t
IndexBufferData::getIndexCount() const noexcept
{
    return _indexCount;
}

IndexType
IndexBufferData::getIndexType() const noexcept
{
    return _indexType;
}

VertexUsage
IndexBufferData::getIndexUsage() const noexcept
{
    return _indexUsage;
}

void*
IndexBufferData::data() noexcept
{
    return _indexStreams.data();
}

const void*
IndexBufferData::data() const noexcept
{
    return _indexStreams.data();
}

RenderBuffer::RenderBuffer() noexcept
{
}

RenderBuffer::~RenderBuffer() noexcept
{
}

void
RenderBuffer::bind() const noexcept
{
    assert(false);
}

void
RenderBuffer::unbind() const noexcept
{
    assert(false);
}

_NAME_END