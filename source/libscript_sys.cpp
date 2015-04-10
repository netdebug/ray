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

#include <ray/script/libscript.h>
#include <ray/script/libscript_luaapi.h>

#include <ray/platform/memory.h>
#include <ray/platform/isystem.h>

_NAME_BEGIN

Script::Script(MemAllocFunc alloc, void* ud) : Stack(nullptr)
{
    RawInterface raw = nullptr;

    if (alloc == nullptr)
        raw = Stack::newstate_L();
    else
        raw = Stack::newstate(alloc, ud);

    _c_state = raw;

    openlibs_L();
}

static void *l_alloc(void *ud, void *ptr, size_t osize, size_t nsize) 
{
    MemAlloc* alloc = (MemAlloc*)ud;

    if (nsize == 0) {
        alloc->free(ptr, osize);
        return nullptr;
    }
    else
        return alloc->alloc(nsize);
}

Script::Script(MemAlloc* alloc) : Stack(nullptr)
{
    RawInterface raw = nullptr;

    if (alloc == nullptr)
        raw = Stack::newstate_L();
    else
        raw = Stack::newstate(l_alloc, alloc);

    _c_state = raw;

    openlibs_L();
}

Script::~Script()
{
    Value::endOfHandlerRefBuffer();
    Stack::close(_c_state);
}


void Script::exec(const std::string& fileName)
{
    isystem system(isystem::instance());

    if (!system.open(fileName))
    {
        SCRIPT_EXCEPTION("Failed to open file:" + fileName);
    }

    istream* stream = system.stream();

    stream->seekg(0, ios_base::end);

    auto size = (std::size_t)stream->tellg();

    stream->seekg(0, ios_base::beg);

    std::unique_ptr<char[]> buff(new char[size]);

    stream->read(buff.get(), size);

    if (loadbuffer_L(buff.get(), size, fileName.c_str()) ||
        pcall(0, 0, 0))
    {
        std::string errorInfo = tostring(-1); 
        pop(1);
        SCRIPT_EXCEPTION(errorInfo);
    }
}

void Script::execString(const std::string& str)
{
    if (loadbuffer_L(str.c_str(), str.size(), (str.substr(0, 20) + "...").c_str()) ||
        pcall(0, 0, 0))
    {
        std::string errorInfo = tostring(-1);
        pop(1);
        SCRIPT_EXCEPTION(errorInfo);
    }
}

Value Script::newFunction(const std::string& script)
{
    if (loadbuffer_L(script.c_str(), script.size(), (script.substr(0, 20) + "...").c_str()))
    {
        std::string errorInfo = tostring(-1);
        pop(1);
        SCRIPT_EXCEPTION(errorInfo);
    }

    return *this;
}

Value Script::newFunction(CFunction function)
{
    pushcfunction(function);
    return *this;
}

Value Script::newTable()
{
    newtable();
    return *this;
}

Value Script::newThread()
{
    Stack::newthread();
    return *this;
}

Value Script::newThread(Function function)
{
    Stack NL = Stack::newthread();
    function.pushRef(T_Function);
    xmove(NL, 1);
    return *this;
}

Value Script::getGlobal(const std::string& name)
{
    getglobal(name.c_str());
    return *this;
}

Table Script::getGlobalTable()
{
    pushglobaltable();
    return *this;
}

Value Script::getNil()
{
    pushnil();
    return *this;
}

_NAME_END