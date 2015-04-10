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
#ifndef _H_COLLIDER_TERRAIN_H_
#define _H_COLLIDER_TERRAIN_H_

#include <ray/physics_shape.h>

class btHeightfieldTerrainShape;

_NAME_BEGIN

enum PHYDataType
{
    UCHAR,
    SHORT,
    INTEGER,
    FLOAT,
};

class EXPORT PhysicsShapeTerrain : public PhysicsShape
{
public:
    PhysicsShapeTerrain() noexcept;
    ~PhysicsShapeTerrain() noexcept;

    void setup() noexcept;
    void close() noexcept;

    void setHeightMap(std::size_t w, std::size_t z, PHYDataType type, const char* data) noexcept;

    void setSize(const Vector3& size) noexcept;
    const Vector3& getSize() const noexcept;

    void setMinHeight(float min);
    void setMaxHeight(float max);
    void setScaleHeight(float scale) noexcept;

    float getMinHeight() const noexcept;
    float getMaxHeight() const noexcept;
    float getScaleHeight() const noexcept;

protected:

    btCollisionShape* getCollisionShape() noexcept;

private:

    std::size_t _width;
    std::size_t _depth;

    Vector3 _size;

    float _minHeight;
    float _maxHeight;

    float _scaleHeight;

    bool _flipQuadEdges;

    PHYDataType _type;

    std::vector<char> _data;

    btHeightfieldTerrainShape* _shape;
};

_NAME_END

#endif