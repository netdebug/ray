// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2017-2018.
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
#include "UITexts.h"
#include <ray/string.h>
#include <ray/utf8.h>

const char* en_lang[] = {
	" File ",
	" Edit ",
	" Open ",
	" Save ",
	" Save as ",
	" Choose File ",
	" Import Model ",
	" Export Model ",
	" Exit ",
	" GameObject ",
	" Window ",
	"Setting",
	"Language",
	"English",
	"Chinese",
	"Light Mass",
	"Style Editor",
	"Help",
	"About",
	"Error?",
	"Ok",
	"Cancel",
	"Don't ask me next time?",
	" Revert ",
	"Non readable PMX file.",
	"Output UV size:",
	"Output UV slot:",
	"Input UV slot:",
	"Output image size:",
	"Uv Mapper",
	"margin:",
	"stretch:",
	"chart:",
	" Start mapper ",
	"Enable GI",
	"Enable IBL",
	"Sample Count:",
	"Environment Color:",
	"Environment Intensity:",
	"Ray tracing znear:",
	"Ray tracing zfar:",
	"Interpolation Passes:",
	"Interpolation Threshold:",
	" Start Baking ",
	"Unsupported Model",
	"Process",
	"Succeeded",
	"Please load a model before start baking.",
	"Camera",
	"Asset",
	"Material",
	"Inspector",
	"Lights",
	"LightProbes",
	"Meshes",
	"Import...",
	"Export...",
	"Texture from:",
	"Texture Flip:",
	"Texture loop:",
	"Texture (sRGB):",
	"Texture type:",
	"Texture swizzle:",
	"Color:",
	"Color (sRGB):",
	"Strength:",
	"Albedo",
	"AlbedoSub",
	"Normal",
	"NormalSub",
	"Smoothness:",
	"Metalness:",
	"Specular",
	"Occlusion:",
	"Emissive:",
	"Intensity:",
	"ShadingModel",
	"CustomA:",
	"CustomB:",
	"Summary: %s",
	"Transform",
	"Position",
	"Rotation",
	"Scaling",
	"Light Probe"
};

const wchar_t* cn_lang[] = {
	L" 文件 ",
	L" 编辑 ",
	L"打开",
	L"保存",
	L"另存为",
	L"选择文件",
	L"导入模型",
	L"导出模型",
	L"退出",
	L" 游戏对象 ",
	L" 窗体 ",
	L"设置",
	L"语言",
	L"英文",
	L"中文",
	L"光照烘培",
	L"界面设置",
	L" 帮助 ",
	L"关于",
	L"错误?",
	L"确认",
	L"取消",
	L"下一次不再显示?",
	L" 重置 ",
	L"不可读的PMX文件",
	L"展开的UV大小:",
	L"输出的UV插槽:",
	L"输入的UV插槽:",
	L"输出的图像大小:",
	L"纹理坐标全展开",
	L"展开间隔:",
	L"合并UV最小阈值:",
	L"展开三角最大数量:",
	L" 开始展开 ",
	L"使用全局光",
	L"使用HDR光源",
	L"采样数:",
	L"环境光颜色:",
	L"环境光强:",
	L"追踪的最小范围",
	L"追踪的最大范围",
	L"插值次数",
	L"插值阈值",
	L" 开始烘培 ",
	L"不支持的模型",
	L"处理中",
	L"提示",
	L"请先载入一个模型",
	L"相机",
	L"资源",
	L"材质",
	L"监视",
	L"光源",
	L"光源探针",
	L"模型",
	L"导入...",
	L"导出...",
	L"纹理模式:",
	L"纹理坐标翻转:",
	L"纹理迭代:",
	L"纹理 (sRGB):",
	L"纹理类型:",
	L"纹理频道:",
	L"颜色:",
	L"颜色 (sRGB):",
	L"强度:",
	L"主固有色",
	L"次固有色",
	L"主法线",
	L"次法线",
	L"光滑度:",
	L"金属性:",
	L"高光",
	L"环境光遮蔽:",
	L"自发光",
	L"强度:",
	L"着色模型",
	L"CustomA:",
	L"CustomB:",
	L"概要 %s",
	L"变换",
	L"坐标",
	L"旋转",
	L"缩放",
	L"环境探针"
};

std::vector<std::string> cn_lang_utf8;

void GetLangPackage(UILang::Lang type, std::vector<std::string>& langs) noexcept
{
	static_assert(sizeof(cn_lang) == sizeof(en_lang));

	langs.clear();

	if (type == UILang::Lang::English)
	{
		for (auto& it : en_lang)
			langs.push_back(it);
	}
	else
	{
		char buffer[MAX_PATH];

		if (cn_lang_utf8.empty())
		{
			for (auto& it : cn_lang)
			{
				if (ray::utf16_to_utf8(it, ray::util::strlen(it), buffer, MAX_PATH))
					cn_lang_utf8.push_back(buffer);
			}
		}

		for (auto& it : cn_lang_utf8)
			langs.push_back(it);
	}
}