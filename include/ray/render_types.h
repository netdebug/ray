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
#ifndef _H_RENDER_TYPES_H_
#define _H_RENDER_TYPES_H_

#include <ray/graphics_types.h>
#include <ray/model.h>

_NAME_BEGIN

typedef std::shared_ptr<class Material> MaterialPtr;
typedef std::shared_ptr<class MaterialSemantic> MaterialSemanticPtr;
typedef std::shared_ptr<class MaterialPass> MaterialPassPtr;
typedef std::shared_ptr<class MaterialTech> MaterialTechPtr;
typedef std::shared_ptr<class MaterialParam> MaterialParamPtr;
typedef std::shared_ptr<class MaterialMacro> MaterialMacroPtr;
typedef std::shared_ptr<class MaterialSemantic> MaterialSemanticPtr;
typedef std::shared_ptr<class MaterialSemanticManager> MaterialSemanticManagerPtr;
typedef std::shared_ptr<class MaterialDesc> MaterialDescPtr;
typedef std::shared_ptr<class MaterialPassDesc> MaterialPassDescPtr;
typedef std::shared_ptr<class MaterialTechDesc> MaterialTechDescPtr;
typedef std::shared_ptr<class MaterialParamDesc> MaterialParamDescPtr;
typedef std::shared_ptr<class MaterialVariant> MaterialVariantPtr;
typedef std::shared_ptr<class MaterialLoader> MaterialLoaderPtr;
typedef std::shared_ptr<class MaterialManager> MaterialManagerPtr;
typedef std::shared_ptr<class RenderObject> RenderObjectPtr;
typedef std::shared_ptr<class RenderPostProcess> RenderPostProcessPtr;
typedef std::shared_ptr<class RenderDataManager> RenderDataManagerPtr;
typedef std::shared_ptr<class Geometry> GeometryPtr;
typedef std::shared_ptr<class RenderSystem> RenderSystemPtr;
typedef std::shared_ptr<class RenderPipelineStage> RenderPipelineStagePtr;
typedef std::shared_ptr<class RenderScene> RenderScenePtr;
typedef std::shared_ptr<class Camera> CameraPtr;
typedef std::shared_ptr<class Light> LightPtr;
typedef std::shared_ptr<class RenderPipeline> RenderPipelinePtr;
typedef std::shared_ptr<class RenderPipelineDevice> RenderPipelineDevicePtr;
typedef std::shared_ptr<class RenderPipelineController> RenderPipelineControllerPtr;
typedef std::shared_ptr<class RenderPipelineManager> RenderPipelineManagerPtr;

typedef std::weak_ptr<class Material> MaterialWeakPtr;
typedef std::weak_ptr<class MaterialPass> MaterialPassWeakPtr;
typedef std::weak_ptr<class MaterialTech> MaterialTechWeakPtr;
typedef std::weak_ptr<class MaterialParam> MaterialParamWeakPtr;
typedef std::weak_ptr<class MaterialVariant> MaterialVariantWeakPtr;
typedef std::weak_ptr<class MaterialLoader> MaterialLoaderWeakPtr;
typedef std::weak_ptr<class MaterialManager> MaterialManagerWeakPtr;
typedef std::weak_ptr<class RenderObject> RenderObjectWeakPtr;
typedef std::weak_ptr<class RenderPostProcess> RenderPostProcessWeakPtr;
typedef std::weak_ptr<class RenderPipelineController> RenderPipelineControllerWeakPtr;
typedef std::weak_ptr<class RenderPipelineDevice> RenderPipelineWeakPtr;
typedef std::weak_ptr<class RenderPipelineManager> RenderPipelineManagerWeakPtr;
typedef std::weak_ptr<class RenderDataManager> RenderDataManagerWeakPtr;
typedef std::weak_ptr<class Geometry> GeometryWeakPtr;
typedef std::weak_ptr<class RenderSystem> RenderSystemWeakPtr;
typedef std::weak_ptr<class RenderPipelineStage> RenderPipelineStageWeakPtr;
typedef std::weak_ptr<class RenderScene> RenderSceneWeakPtr;
typedef std::weak_ptr<class Camera> CameraWeakPtr;
typedef std::weak_ptr<class Light> LightWeakPtr;

typedef std::vector<RenderPipelineStagePtr> RenderPipelineStages;
typedef std::vector<GeometryPtr> Geometryes;
typedef std::vector<RenderObjectPtr> RenderObjects;
typedef std::vector<RenderScene*> RenderScenes;
typedef std::vector<RenderPostProcessPtr> RenderPostProcessor;
typedef std::vector<MaterialPtr> Materials;
typedef std::vector<MaterialPassPtr> MaterialPassList;
typedef std::vector<MaterialTechPtr> MaterialTechniques;
typedef std::vector<MaterialParamPtr> MaterialParams;
typedef std::vector<MaterialMacroPtr> MaterialMacros;
typedef std::vector<MaterialPassDescPtr> MaterialPassDescList;
typedef std::vector<MaterialTechDescPtr> MaterialTechniqueDescList;
typedef std::vector<MaterialVariantPtr> MaterialVariants;
typedef std::vector<CameraPtr> Cameras;
typedef std::vector<LightPtr> Lights;

typedef std::vector<RenderObject*> RenderObjectRaws;

enum CameraType
{
	CameraTypeOrtho,
	CameraTypePerspective,
	CameraTypeBeginRange = CameraTypeOrtho,
	CameraTypeEndRange = CameraTypePerspective,
	CameraTypeRangeSize = (CameraTypeEndRange - CameraTypeBeginRange + 1),
	CameraTypeMaxEnum = 0x7FFFFFFF
};

enum CameraOrder
{
	CameraOrderCustom,
	CameraOrderShadow,
	CameraOrder3D,
	CameraOrder2D,
	CameraOrderBeginRange = CameraOrderCustom,
	CameraOrderEndRange = CameraOrder2D,
	CameraOrderRangeSize = (CameraOrderEndRange - CameraOrderBeginRange + 1),
	CameraOrderMaxEnum = 0x7FFFFFFF
};

enum CameraClearFlagBits
{
	CameraClearColorBit   = 1 << 0,
	CameraClearDepthBit   = 1 << 1,
	CameraClearStencilBit = 1 << 2,
	CameraClearDepthStencilBit = CameraClearDepthBit | CameraClearStencilBit,
	CameraClearMaxBit = 0x7FFFFFFF
};

typedef std::uint32_t CameraClearFlags;

enum CameraRenderFlagBits
{
	CameraRenderScreenBit = 0x00000001,
	CameraRenderTextureBit = 0x00000002,
	CameraRenderGbuffer1Bit = 0x00000004,
	CameraRenderGbuffer2Bit = 0x0000008,
	CameraRenderGbuffer3Bit = 0x00000010,
	CameraRenderLightingBit = 0x00000020,
	CameraRenderShadingBit = 0x00000040,
	CameraRenderBeginBit = CameraRenderScreenBit,
	CameraRenderEndBit = CameraRenderShadingBit,
	CameraRenderMaxBit = 0x7FFFFFFF
};

typedef std::uint32_t CameraRenderFlags;

enum LightType
{
	LightTypeSun,
	LightTypeDirectional,
	LightTypeAmbient,
	LightTypePoint,
	LightTypeSpot,
	LightTypeRectangle,
	LightTypeDisk,
	LightTypeTube,
	LightTypeEnvironment,
	LightTypeBeginRange = LightTypeSun,
	LightTypeEndRange = LightTypeEnvironment,
	LightTypeRangeSize = (LightTypeEndRange - LightTypeBeginRange + 1),
	LightTypeMaxEnum = 0x7FFFFFFF
};

enum ShadowMode
{
	ShadowModeNone,
	ShadowModeHard,
	ShadowModeSoft,
	ShadowModeBeginRange = ShadowModeNone,
	ShadowModeEndRange = ShadowModeSoft,
	ShadowModeRangeSize = (ShadowModeEndRange - ShadowModeBeginRange + 1),
	ShadowModeMaxEnum = 0x7FFFFFFF
};

enum ShadowQuality
{
	ShadowQualityNone,
	ShadowQualityLow,
	ShadowQualityMedium,
	ShadowQualityHigh,
	ShadowQualityVeryHigh,
	ShadowQualityBeginRange = ShadowQualityNone,
	ShadowQualityEndRange = ShadowQualityVeryHigh,
	ShadowQualityRangeSize = (ShadowQualityEndRange - ShadowQualityBeginRange + 1),
	ShadowQualityMaxEnum = 0x7FFFFFFF
};

enum LightShadowSize
{
	LightShadowSizeLow = 256,
	LightShadowSizeMedium = 512,
	LightShadowSizeHigh = 1024,
	LightShadowSizeVeryHigh = 2048,
	LightShadowSizeEnumCount = 4
};

enum RenderPipelineType
{
	RenderPipelineTypeForward,
	RenderPipelineTypeForwardPlus,
	RenderPipelineTypeDeferredLighting,
	RenderPipelineTypeBeginRange = RenderPipelineTypeForward,
	RenderPipelineTypeEndRange = RenderPipelineTypeDeferredLighting,
	RenderPipelineTypeRangeSize = (RenderPipelineTypeEndRange - RenderPipelineTypeBeginRange + 1),
	RenderPipelineTypeMaxEnum = 0x7FFFFFFF
};

enum RenderQueue
{
	RenderQueueCustom,
	RenderQueueShadow,
	RenderQueueReflectiveShadow,
	RenderQueueOpaque,
	RenderQueueOpaqueBatch,
	RenderQueueOpaqueSpecific,
	RenderQueueOpaqueSpecificBatch,
	RenderQueueOpaqueShading,
	RenderQueueOpaqueLighting,
	RenderQueueTransparentBack,
	RenderQueueTransparentBatchBack,
	RenderQueueTransparentSpecificBack,
	RenderQueueTransparentSpecificBatchBack,
	RenderQueueTransparentShadingBack,
	RenderQueueTransparentFront,
	RenderQueueTransparentBatchFront,
	RenderQueueTransparentSpecificFront,
	RenderQueueTransparentSpecificBatchFront,
	RenderQueueTransparentShadingFront,
	RenderQueueLighting,
	RenderQueuePostprocess,
	RenderQueueBeginRange = RenderQueueCustom,
	RenderQueueEndRange = RenderQueuePostprocess,
	RenderQueueRangeSize = (RenderQueueEndRange - RenderQueueBeginRange + 1),
	RenderQueueMaxEnum = 0x7FFFFFFF
};

enum ModelMakerFlagBits
{
	ModelMakerFlagBitVertex = 0x00000001,
	ModelMakerFlagBitTexcoord = 0x00000002,
	ModelMakerFlagBitNormal = 0x00000004,
	ModelMakerFlagBitTangent = 0x00000008,
	ModelMakerFlagBitBitangent = 0x00000016,
	ModelMakerFlagBitWeight = 0x00000032,
	ModelMakerFlagBitColor = 0x00000064,
	ModelMakerFlagBit_VER_TEX = ModelMakerFlagBitVertex | ModelMakerFlagBitTexcoord,
	ModelMakerFlagBit_VER_TEX_NORMAL = ModelMakerFlagBitVertex | ModelMakerFlagBitTexcoord | ModelMakerFlagBitNormal,
	ModelMakerFlagBit_VER_TEX_NORMAL_WEIGHT = ModelMakerFlagBitVertex | ModelMakerFlagBitTexcoord | ModelMakerFlagBitNormal | ModelMakerFlagBitWeight,
	ModelMakerFlagBit_VER_NORMAL = ModelMakerFlagBitVertex | ModelMakerFlagBitNormal,
	ModelMakerFlagBit_VER_NORMAL_TANGENT = ModelMakerFlagBitVertex | ModelMakerFlagBitNormal | ModelMakerFlagBitTangent,
	ModelMakerFlagBit_VER_NORMAL_WEIGHT = ModelMakerFlagBitVertex | ModelMakerFlagBitTexcoord | ModelMakerFlagBitNormal | ModelMakerFlagBitWeight,
	ModelMakerFlagBit_VER_NORMAL_TANGENT_WEIGHT = ModelMakerFlagBitVertex | ModelMakerFlagBitTexcoord | ModelMakerFlagBitNormal | ModelMakerFlagBitTangent | ModelMakerFlagBitWeight,
	ModelMakerFlagBitALL = 0x7FFFFFFF,
};

typedef std::uint32_t ModelMakerFlags;

enum GlobalSemanticType
{
	GlobalSemanticTypeNone,
	GlobalSemanticTypeModel,
	GlobalSemanticTypeModelInverse,
	GlobalSemanticTypeView,
	GlobalSemanticTypeViewInverse,
	GlobalSemanticTypeProject,
	GlobalSemanticTypeProjectInverse,
	GlobalSemanticTypeViewProject,
	GlobalSemanticTypeViewProjectInverse,
	GlobalSemanticTypeModelView,
	GlobalSemanticTypeModelViewProject,
	GlobalSemanticTypeModelViewInverse,
	GlobalSemanticTypeCameraAperture,
	GlobalSemanticTypeCameraNear,
	GlobalSemanticTypeCameraFar,
	GlobalSemanticTypeCameraPosition,
	GlobalSemanticTypeCameraDirection,
	GlobalSemanticTypeDepthMap,
	GlobalSemanticTypeDepthLinearMap,
	GlobalSemanticTypeDiffuseMap,
	GlobalSemanticTypeNormalMap,
	GlobalSemanticTypeGbuffer3Map,
	GlobalSemanticTypeLightingMap,
	GlobalSemanticTypeOpaqueShadingMap,
	GlobalSemanticTypeBeginRange = GlobalSemanticTypeNone,
	GlobalSemanticTypeEndRange = GlobalSemanticTypeOpaqueShadingMap,
	GlobalSemanticTypeRangeSize = (GlobalSemanticTypeEndRange - GlobalSemanticTypeBeginRange + 1),
	GlobalSemanticTypeMaxEnum = 0x7FFFFFFF
};

_NAME_END

#endif