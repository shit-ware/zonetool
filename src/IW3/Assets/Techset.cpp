// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#include "stdafx.hpp"

#include "../IW4/Assets/VertexDecl.hpp"
#include "../IW4/Assets/VertexShader.hpp"
#include "../IW4/Assets/PixelShader.hpp"
#include "IW4/Assets/Techset.hpp"

static const unsigned int crcTable[] =
{
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
	0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
	0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
	0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
	0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
	0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
	0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
	0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
	0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
	0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
	0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
	0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
	0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
	0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
	0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
	0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
	0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
	0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
	0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
	0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
	0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
	0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

std::uint32_t Crc32(void* buffer, const std::size_t size, const std::uint32_t initialCrc)
{
	auto curPtr = reinterpret_cast<std::uint8_t*>(buffer);
	auto remaining = size;
	auto crc = ~initialCrc;

	for (; remaining--; ++curPtr)
	{
		crc = (crc >> 8) ^ crcTable[(crc ^ *curPtr) & 0xFF];
	}

	return (~crc);
}

namespace ZoneTool
{
	namespace IW3
	{		
		std::string GenerateNameForVertexDecl(MaterialVertexDeclaration* vertexDecl)
		{
			// base name + crc32
			auto name = "iw3_vertexdecl_"s;
			auto crc32 = Crc32(vertexDecl->routing.data, sizeof MaterialVertexDeclaration, 0);

			// append crc32 to vertexdecl name
			name += std::to_string(crc32);

			// return generated name
			return name;
		}

		IW4::VertexDecl* ITechset::dump_vertex_decl(const std::string& name, MaterialVertexDeclaration* vertex, ZoneMemory* mem)
		{
			// convert to IW4
			const auto asset = mem->Alloc<IW4::VertexDecl>();
			
			asset->name = mem->StrDup(name);

			asset->hasOptionalSource = vertex->hasOptionalSource;
			asset->streamCount = vertex->streamCount;

			memcpy(asset->streams, vertex->routing.data, sizeof asset->streams);
			memcpy(asset->declarations, vertex->routing.decl, sizeof(void*) * 16);

			for (int i = 0; i < asset->streamCount; i++)
			{
				if (asset->streams[i].dest >= 4)
				{
					asset->streams[i].dest += 1;
				}
			}

			// shit out a warning
			if (asset->streamCount > 13)
			{
				ZONETOOL_ERROR("Vertexdecl %s has more than 13 streams.", name.data());
			}

			// lets pray it works
			IW4::IVertexDecl::dump(asset);

			return asset;
		}

		IW4::VertexShader* ITechset::dump_vertex_shader(MaterialVertexShader* shader, ZoneMemory* mem)
		{
			// convert to IW4
			const auto asset = mem->Alloc<IW4::VertexShader>();

			asset->name = shader->name;
			asset->shader = shader->prog.vs;
			asset->codeLen = shader->prog.loadDef.programSize;
			asset->bytecode = PDWORD(shader->prog.loadDef.program);

			// dump shader
			IW4::IVertexShader::dump(asset);

			return asset;
		}

		IW4::PixelShader* ITechset::dump_pixel_shader(MaterialPixelShader* shader, ZoneMemory* mem)
		{
			// convert to IW4
			const auto asset = mem->Alloc<IW4::PixelShader>();

			asset->name = shader->name;
			asset->shader = shader->prog.ps;
			asset->codeLen = shader->prog.loadDef.programSize;
			asset->bytecode = PDWORD(shader->prog.loadDef.program);

			// dump shader
			IW4::IPixelShader::dump(asset);

			return asset;
		}

		std::unordered_map<std::int32_t, std::int32_t> iw3_technique_map =
		{
			{IW3::TECHNIQUE_DEPTH_PREPASS, IW4::TECHNIQUE_DEPTH_PREPASS},
			{IW3::TECHNIQUE_BUILD_FLOAT_Z, IW4::TECHNIQUE_BUILD_FLOAT_Z},
			{IW3::TECHNIQUE_BUILD_SHADOWMAP_DEPTH, IW4::TECHNIQUE_BUILD_SHADOWMAP_DEPTH},
			{IW3::TECHNIQUE_BUILD_SHADOWMAP_COLOR, IW4::TECHNIQUE_BUILD_SHADOWMAP_COLOR},
			{IW3::TECHNIQUE_UNLIT, IW4::TECHNIQUE_UNLIT},
			{IW3::TECHNIQUE_EMISSIVE, IW4::TECHNIQUE_EMISSIVE},
			{IW3::TECHNIQUE_EMISSIVE_SHADOW, IW4::TECHNIQUE_EMISSIVE_SHADOW},
			{IW3::TECHNIQUE_LIT_BEGIN, IW4::TECHNIQUE_LIT_BEGIN},
			{IW3::TECHNIQUE_LIT, IW4::TECHNIQUE_LIT},
			{IW3::TECHNIQUE_LIT_SUN, IW4::TECHNIQUE_LIT_SUN},
			{IW3::TECHNIQUE_LIT_SUN_SHADOW, IW4::TECHNIQUE_LIT_SUN_SHADOW},
			{IW3::TECHNIQUE_LIT_SPOT, IW4::TECHNIQUE_LIT_SPOT},
			{IW3::TECHNIQUE_LIT_SPOT_SHADOW, IW4::TECHNIQUE_LIT_SPOT_SHADOW},
			{IW3::TECHNIQUE_LIT_OMNI, IW4::TECHNIQUE_LIT_OMNI},
			{IW3::TECHNIQUE_LIT_OMNI_SHADOW, IW4::TECHNIQUE_LIT_OMNI_SHADOW},
			{IW3::TECHNIQUE_LIT_INSTANCED, IW4::TECHNIQUE_LIT_INSTANCED},
			{IW3::TECHNIQUE_LIT_INSTANCED_SUN, IW4::TECHNIQUE_LIT_INSTANCED_SUN},
			{IW3::TECHNIQUE_LIT_INSTANCED_SUN_SHADOW, IW4::TECHNIQUE_LIT_INSTANCED_SUN_SHADOW},
			{IW3::TECHNIQUE_LIT_INSTANCED_SPOT, IW4::TECHNIQUE_LIT_INSTANCED_SPOT},
			{IW3::TECHNIQUE_LIT_INSTANCED_OMNI, IW4::TECHNIQUE_LIT_INSTANCED_OMNI},
			{IW3::TECHNIQUE_LIT_END, IW4::TECHNIQUE_LIT_END},
			{IW3::TECHNIQUE_LIGHT_SPOT, IW4::TECHNIQUE_LIGHT_SPOT},
			{IW3::TECHNIQUE_LIGHT_OMNI, IW4::TECHNIQUE_LIGHT_OMNI},
			{IW3::TECHNIQUE_LIGHT_SPOT_SHADOW, IW4::TECHNIQUE_LIGHT_SPOT_SHADOW},
			{IW3::TECHNIQUE_FAKELIGHT_NORMAL, IW4::TECHNIQUE_FAKELIGHT_NORMAL},
			{IW3::TECHNIQUE_FAKELIGHT_VIEW, IW4::TECHNIQUE_FAKELIGHT_VIEW},
			{IW3::TECHNIQUE_SUNLIGHT_PREVIEW, IW4::TECHNIQUE_SUNLIGHT_PREVIEW},
			{IW3::TECHNIQUE_CASE_TEXTURE, IW4::TECHNIQUE_CASE_TEXTURE},
			{IW3::TECHNIQUE_WIREFRAME_SOLID, IW4::TECHNIQUE_WIREFRAME_SOLID},
			{IW3::TECHNIQUE_WIREFRAME_SHADED, IW4::TECHNIQUE_WIREFRAME_SHADED},
			{IW3::TECHNIQUE_SHADOWCOOKIE_CASTER, 0xFFFFFFFF},
			{IW3::TECHNIQUE_SHADOWCOOKIE_RECEIVER, 0xFFFFFFFF},
			{IW3::TECHNIQUE_DEBUG_BUMPMAP, IW4::TECHNIQUE_DEBUG_BUMPMAP},
			{IW3::TECHNIQUE_DEBUG_BUMPMAP_INSTANCED, IW4::TECHNIQUE_DEBUG_BUMPMAP_INSTANCED},
			{IW3::TECHNIQUE_COUNT, IW4::TECHNIQUE_COUNT},
			{IW3::TECHNIQUE_TOTAL_COUNT, IW4::TECHNIQUE_TOTAL_COUNT},
			{IW3::TECHNIQUE_NONE, IW4::TECHNIQUE_NONE},
		};

		std::unordered_map<std::int32_t, std::int32_t> iw3_code_const_map =
		{
			{IW3::CONST_SRC_CODE_MAYBE_DIRTY_PS_BEGIN, IW4::CONST_SRC_CODE_MAYBE_DIRTY_PS_BEGIN},
			{IW3::CONST_SRC_CODE_LIGHT_POSITION, IW4::CONST_SRC_CODE_LIGHT_POSITION},
			{IW3::CONST_SRC_CODE_LIGHT_DIFFUSE, IW4::CONST_SRC_CODE_LIGHT_DIFFUSE},
			{IW3::CONST_SRC_CODE_LIGHT_SPECULAR, IW4::CONST_SRC_CODE_LIGHT_SPECULAR},
			{IW3::CONST_SRC_CODE_LIGHT_SPOTDIR, IW4::CONST_SRC_CODE_LIGHT_SPOTDIR},
			{IW3::CONST_SRC_CODE_LIGHT_SPOTFACTORS, IW4::CONST_SRC_CODE_LIGHT_SPOTFACTORS},
			{IW3::CONST_SRC_CODE_NEARPLANE_ORG, IW4::CONST_SRC_CODE_NEARPLANE_ORG},
			{IW3::CONST_SRC_CODE_NEARPLANE_DX, IW4::CONST_SRC_CODE_NEARPLANE_DX},
			{IW3::CONST_SRC_CODE_NEARPLANE_DY, IW4::CONST_SRC_CODE_NEARPLANE_DY},
			// { IW3::CONST_SRC_CODE_SHADOW_PARMS, IW4::CONST_SRC_CODE_SHADOW_PARAMS },
			{IW3::CONST_SRC_CODE_SHADOWMAP_POLYGON_OFFSET, IW4::CONST_SRC_CODE_SHADOWMAP_POLYGON_OFFSET},
			{IW3::CONST_SRC_CODE_RENDER_TARGET_SIZE, IW4::CONST_SRC_CODE_RENDER_TARGET_SIZE},
			{IW3::CONST_SRC_CODE_LIGHT_FALLOFF_PLACEMENT, IW4::CONST_SRC_CODE_LIGHT_FALLOFF_PLACEMENT},
			{
				IW3::CONST_SRC_CODE_DOF_EQUATION_VIEWMODEL_AND_FAR_BLUR,
				IW4::CONST_SRC_CODE_DOF_EQUATION_VIEWMODEL_AND_FAR_BLUR
			},
			{IW3::CONST_SRC_CODE_DOF_EQUATION_SCENE, IW4::CONST_SRC_CODE_DOF_EQUATION_SCENE},
			{IW3::CONST_SRC_CODE_DOF_LERP_SCALE, IW4::CONST_SRC_CODE_DOF_LERP_SCALE},
			{IW3::CONST_SRC_CODE_DOF_LERP_BIAS, IW4::CONST_SRC_CODE_DOF_LERP_BIAS},
			{IW3::CONST_SRC_CODE_DOF_ROW_DELTA, IW4::CONST_SRC_CODE_DOF_ROW_DELTA},
			{IW3::CONST_SRC_CODE_PARTICLE_CLOUD_COLOR, IW4::CONST_SRC_CODE_PARTICLE_CLOUD_COLOR},
			{IW3::CONST_SRC_CODE_GAMETIME, IW4::CONST_SRC_CODE_GAMETIME},
			{IW3::CONST_SRC_CODE_MAYBE_DIRTY_PS_END, IW4::CONST_SRC_CODE_MAYBE_DIRTY_PS_END},
			{IW3::CONST_SRC_CODE_ALWAYS_DIRTY_PS_BEGIN, IW4::CONST_SRC_CODE_ALWAYS_DIRTY_PS_BEGIN},
			{IW3::CONST_SRC_CODE_PIXEL_COST_FRACS, IW4::CONST_SRC_CODE_PIXEL_COST_FRACS},
			{IW3::CONST_SRC_CODE_PIXEL_COST_DECODE, IW4::CONST_SRC_CODE_PIXEL_COST_DECODE},
			{IW3::CONST_SRC_CODE_FILTER_TAP_0, IW4::CONST_SRC_CODE_FILTER_TAP_0},
			{IW3::CONST_SRC_CODE_FILTER_TAP_1, IW4::CONST_SRC_CODE_FILTER_TAP_1},
			{IW3::CONST_SRC_CODE_FILTER_TAP_2, IW4::CONST_SRC_CODE_FILTER_TAP_2},
			{IW3::CONST_SRC_CODE_FILTER_TAP_3, IW4::CONST_SRC_CODE_FILTER_TAP_3},
			{IW3::CONST_SRC_CODE_FILTER_TAP_4, IW4::CONST_SRC_CODE_FILTER_TAP_4},
			{IW3::CONST_SRC_CODE_FILTER_TAP_5, IW4::CONST_SRC_CODE_FILTER_TAP_5},
			{IW3::CONST_SRC_CODE_FILTER_TAP_6, IW4::CONST_SRC_CODE_FILTER_TAP_6},
			{IW3::CONST_SRC_CODE_FILTER_TAP_7, IW4::CONST_SRC_CODE_FILTER_TAP_7},
			{IW3::CONST_SRC_CODE_COLOR_MATRIX_R, IW4::CONST_SRC_CODE_COLOR_MATRIX_R},
			{IW3::CONST_SRC_CODE_COLOR_MATRIX_G, IW4::CONST_SRC_CODE_COLOR_MATRIX_G},
			{IW3::CONST_SRC_CODE_COLOR_MATRIX_B, IW4::CONST_SRC_CODE_COLOR_MATRIX_B},
			{IW3::CONST_SRC_CODE_ALWAYS_DIRTY_PS_END, IW4::CONST_SRC_CODE_ALWAYS_DIRTY_PS_END},
			// { IW3::CONST_SRC_CODE_NEVER_DIRTY_PS_BEGIN, IW4::CONST_SRC_CODE_ },
			{IW3::CONST_SRC_CODE_SHADOWMAP_SWITCH_PARTITION, IW4::CONST_SRC_CODE_SHADOWMAP_SWITCH_PARTITION},
			{IW3::CONST_SRC_CODE_SHADOWMAP_SCALE, IW4::CONST_SRC_CODE_SHADOWMAP_SCALE},
			{IW3::CONST_SRC_CODE_ZNEAR, IW4::CONST_SRC_CODE_ZNEAR},
			{IW3::CONST_SRC_CODE_SUN_POSITION, IW4::CONST_SRC_CODE_LIGHT_POSITION},
			{IW3::CONST_SRC_CODE_SUN_DIFFUSE, IW4::CONST_SRC_CODE_LIGHT_DIFFUSE},
			{IW3::CONST_SRC_CODE_SUN_SPECULAR, IW4::CONST_SRC_CODE_LIGHT_SPECULAR},
			{IW3::CONST_SRC_CODE_LIGHTING_LOOKUP_SCALE, IW4::CONST_SRC_CODE_LIGHTING_LOOKUP_SCALE},
			{IW3::CONST_SRC_CODE_DEBUG_BUMPMAP, IW4::CONST_SRC_CODE_DEBUG_BUMPMAP},
			{IW3::CONST_SRC_CODE_MATERIAL_COLOR, IW4::CONST_SRC_CODE_MATERIAL_COLOR},
			{IW3::CONST_SRC_CODE_FOG, IW4::CONST_SRC_CODE_FOG},
			{IW3::CONST_SRC_CODE_FOG_COLOR, IW4::CONST_SRC_CODE_FOG_COLOR_LINEAR},
			{IW3::CONST_SRC_CODE_GLOW_SETUP, IW4::CONST_SRC_CODE_GLOW_SETUP},
			{IW3::CONST_SRC_CODE_GLOW_APPLY, IW4::CONST_SRC_CODE_GLOW_APPLY},
			{IW3::CONST_SRC_CODE_COLOR_BIAS, IW4::CONST_SRC_CODE_COLOR_BIAS},
			{IW3::CONST_SRC_CODE_COLOR_TINT_BASE, IW4::CONST_SRC_CODE_COLOR_TINT_BASE},
			{IW3::CONST_SRC_CODE_COLOR_TINT_DELTA, IW4::CONST_SRC_CODE_COLOR_TINT_DELTA},
			{IW3::CONST_SRC_CODE_OUTDOOR_FEATHER_PARMS, IW4::CONST_SRC_CODE_OUTDOOR_FEATHER_PARMS},
			{IW3::CONST_SRC_CODE_ENVMAP_PARMS, IW4::CONST_SRC_CODE_ENVMAP_PARMS},
			{IW3::CONST_SRC_CODE_SPOT_SHADOWMAP_PIXEL_ADJUST, IW4::CONST_SRC_CODE_SPOT_SHADOWMAP_PIXEL_ADJUST},
			{IW3::CONST_SRC_CODE_CLIP_SPACE_LOOKUP_SCALE, IW4::CONST_SRC_CODE_CLIP_SPACE_LOOKUP_SCALE},
			{IW3::CONST_SRC_CODE_CLIP_SPACE_LOOKUP_OFFSET, IW4::CONST_SRC_CODE_CLIP_SPACE_LOOKUP_OFFSET},
			{IW3::CONST_SRC_CODE_PARTICLE_CLOUD_MATRIX, IW4::CONST_SRC_CODE_PARTICLE_CLOUD_MATRIX0},
			{IW3::CONST_SRC_CODE_DEPTH_FROM_CLIP, IW4::CONST_SRC_CODE_DEPTH_FROM_CLIP},
			{IW3::CONST_SRC_CODE_CODE_MESH_ARG_0, IW4::CONST_SRC_CODE_CODE_MESH_ARG_0},
			{IW3::CONST_SRC_CODE_CODE_MESH_ARG_1, IW4::CONST_SRC_CODE_CODE_MESH_ARG_1},
			{IW3::CONST_SRC_CODE_CODE_MESH_ARG_LAST, IW4::CONST_SRC_CODE_CODE_MESH_ARG_LAST},
			{IW3::CONST_SRC_CODE_BASE_LIGHTING_COORDS, IW4::CONST_SRC_CODE_BASE_LIGHTING_COORDS},
			// { IW3::CONST_SRC_CODE_NEVER_DIRTY_PS_END, IW4::CONST_SRC_CODE_NEVER_DIRTY_PS },
			{IW3::CONST_SRC_CODE_COUNT_FLOAT4, IW4::CONST_SRC_CODE_COUNT_FLOAT4},
			{IW3::CONST_SRC_FIRST_CODE_MATRIX, IW4::CONST_SRC_FIRST_CODE_MATRIX},
			{IW3::CONST_SRC_CODE_WORLD_MATRIX, IW4::CONST_SRC_CODE_WORLD_MATRIX0},
			{IW3::CONST_SRC_CODE_INVERSE_WORLD_MATRIX, IW4::CONST_SRC_CODE_INVERSE_WORLD_MATRIX0},
			{IW3::CONST_SRC_CODE_TRANSPOSE_WORLD_MATRIX, IW4::CONST_SRC_CODE_TRANSPOSE_WORLD_MATRIX0},
			{IW3::CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_MATRIX, IW4::CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_MATRIX0},
			{IW3::CONST_SRC_CODE_VIEW_MATRIX, IW4::CONST_SRC_CODE_VIEW_MATRIX},
			{IW3::CONST_SRC_CODE_INVERSE_VIEW_MATRIX, IW4::CONST_SRC_CODE_INVERSE_VIEW_MATRIX},
			{IW3::CONST_SRC_CODE_TRANSPOSE_VIEW_MATRIX, IW4::CONST_SRC_CODE_TRANSPOSE_VIEW_MATRIX},
			{IW3::CONST_SRC_CODE_INVERSE_TRANSPOSE_VIEW_MATRIX, IW4::CONST_SRC_CODE_INVERSE_TRANSPOSE_VIEW_MATRIX},
			{IW3::CONST_SRC_CODE_PROJECTION_MATRIX, IW4::CONST_SRC_CODE_PROJECTION_MATRIX},
			{IW3::CONST_SRC_CODE_INVERSE_PROJECTION_MATRIX, IW4::CONST_SRC_CODE_INVERSE_PROJECTION_MATRIX},
			{IW3::CONST_SRC_CODE_TRANSPOSE_PROJECTION_MATRIX, IW4::CONST_SRC_CODE_TRANSPOSE_PROJECTION_MATRIX},
			{
				IW3::CONST_SRC_CODE_INVERSE_TRANSPOSE_PROJECTION_MATRIX,
				IW4::CONST_SRC_CODE_INVERSE_TRANSPOSE_PROJECTION_MATRIX
			},
			{IW3::CONST_SRC_CODE_WORLD_VIEW_MATRIX, IW4::CONST_SRC_CODE_WORLD_VIEW_MATRIX0},
			{IW3::CONST_SRC_CODE_INVERSE_WORLD_VIEW_MATRIX, IW4::CONST_SRC_CODE_INVERSE_WORLD_VIEW_MATRIX0},
			{IW3::CONST_SRC_CODE_TRANSPOSE_WORLD_VIEW_MATRIX, IW4::CONST_SRC_CODE_TRANSPOSE_WORLD_VIEW_MATRIX0},
			{
				IW3::CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX,
				IW4::CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX0
			},
			{IW3::CONST_SRC_CODE_VIEW_PROJECTION_MATRIX, IW4::CONST_SRC_CODE_VIEW_PROJECTION_MATRIX},
			{IW3::CONST_SRC_CODE_INVERSE_VIEW_PROJECTION_MATRIX, IW4::CONST_SRC_CODE_INVERSE_VIEW_PROJECTION_MATRIX},
			{
				IW3::CONST_SRC_CODE_TRANSPOSE_VIEW_PROJECTION_MATRIX,
				IW4::CONST_SRC_CODE_TRANSPOSE_VIEW_PROJECTION_MATRIX
			},
			{
				IW3::CONST_SRC_CODE_INVERSE_TRANSPOSE_VIEW_PROJECTION_MATRIX,
				IW4::CONST_SRC_CODE_INVERSE_TRANSPOSE_VIEW_PROJECTION_MATRIX
			},
			{IW3::CONST_SRC_CODE_WORLD_VIEW_PROJECTION_MATRIX, IW4::CONST_SRC_CODE_WORLD_VIEW_PROJECTION_MATRIX0},
			{
				IW3::CONST_SRC_CODE_INVERSE_WORLD_VIEW_PROJECTION_MATRIX,
				IW4::CONST_SRC_CODE_INVERSE_WORLD_VIEW_PROJECTION_MATRIX0
			},
			{
				IW3::CONST_SRC_CODE_TRANSPOSE_WORLD_VIEW_PROJECTION_MATRIX,
				IW4::CONST_SRC_CODE_TRANSPOSE_WORLD_VIEW_PROJECTION_MATRIX0
			},
			{
				IW3::CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_VIEW_PROJECTION_MATRIX,
				IW4::CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_VIEW_PROJECTION_MATRIX0
			},
			{IW3::CONST_SRC_CODE_SHADOW_LOOKUP_MATRIX, IW4::CONST_SRC_CODE_SHADOW_LOOKUP_MATRIX},
			{IW3::CONST_SRC_CODE_INVERSE_SHADOW_LOOKUP_MATRIX, IW4::CONST_SRC_CODE_INVERSE_SHADOW_LOOKUP_MATRIX},
			{IW3::CONST_SRC_CODE_TRANSPOSE_SHADOW_LOOKUP_MATRIX, IW4::CONST_SRC_CODE_TRANSPOSE_SHADOW_LOOKUP_MATRIX},
			{
				IW3::CONST_SRC_CODE_INVERSE_TRANSPOSE_SHADOW_LOOKUP_MATRIX,
				IW4::CONST_SRC_CODE_INVERSE_TRANSPOSE_SHADOW_LOOKUP_MATRIX
			},
			{IW3::CONST_SRC_CODE_WORLD_OUTDOOR_LOOKUP_MATRIX, IW4::CONST_SRC_CODE_WORLD_OUTDOOR_LOOKUP_MATRIX},
			{
				IW3::CONST_SRC_CODE_INVERSE_WORLD_OUTDOOR_LOOKUP_MATRIX,
				IW4::CONST_SRC_CODE_INVERSE_WORLD_OUTDOOR_LOOKUP_MATRIX
			},
			{
				IW3::CONST_SRC_CODE_TRANSPOSE_WORLD_OUTDOOR_LOOKUP_MATRIX,
				IW4::CONST_SRC_CODE_TRANSPOSE_WORLD_OUTDOOR_LOOKUP_MATRIX
			},
			{
				IW3::CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_OUTDOOR_LOOKUP_MATRIX,
				IW4::CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_OUTDOOR_LOOKUP_MATRIX
			},
			{IW3::CONST_SRC_TOTAL_COUNT, IW4::CONST_SRC_TOTAL_COUNT},
			{IW3::CONST_SRC_NONE, IW4::CONST_SRC_NONE},
		};

		void ITechset::dump_statebits(const std::string& techset, char* statebits)
		{
			char iw4_statebits[48];
			memset(iw4_statebits, 0xFF, sizeof iw4_statebits);

			for (int i = 0; i < 34; i++)
			{
				const auto itr = iw3_technique_map.find(i);
				if (itr != iw3_technique_map.end())
				{
					if (itr->second >= 0)
					{
						iw4_statebits[itr->second] = statebits[i];

						if (iw4_statebits[itr->second] >= 7)
						{
							iw4_statebits[itr->second] += 1;
						}
						
						if (itr->second >= 5 && itr->second <= 36)
						{
							iw4_statebits[itr->second + 1] = iw4_statebits[itr->second];
						}
					}
				}
			}
			
			IW4::ITechset::dump_statebits(techset, iw4_statebits);
		}
		
		void ITechset::dump(MaterialTechniqueSet* asset, ZoneMemory* mem)
		{
			auto iw4_techset = mem->Alloc<IW4::MaterialTechniqueSet>();

			iw4_techset->name = asset->name;
			iw4_techset->pad = asset->pad;
			
			for (int i = 0; i < 34; i++)
			{
				const auto itr = iw3_technique_map.find(i);
				if (itr != iw3_technique_map.end())
				{
					if (asset->techniques[i] && itr->second >= 0)
					{
						const auto size = sizeof(IW4::MaterialTechniqueHeader) + (sizeof(IW4::MaterialPass) * asset->techniques[i]->hdr.numPasses);
						iw4_techset->techniques[itr->second] = reinterpret_cast<IW4::MaterialTechnique*>(
							new char[size]);

						if (itr->second >= 5 && itr->second <= 36)
						{
							iw4_techset->techniques[itr->second + 1] = iw4_techset->techniques[itr->second];
						}
						
						memcpy(iw4_techset->techniques[itr->second], asset->techniques[i], size);

						auto& iw3_technique = asset->techniques[i];
						auto& technique = iw4_techset->techniques[itr->second];
						
						for (short pass = 0; pass < technique->hdr.numPasses; pass++)
						{
							const auto iw3_pass_def = &iw3_technique->pass[pass];
							const auto pass_def = &technique->pass[pass];

							auto vertex_decl_name = GenerateNameForVertexDecl(iw3_pass_def->vertexDecl);

							if (iw3_pass_def->pixelShader) pass_def->pixelShader = dump_pixel_shader(iw3_pass_def->pixelShader, mem);
							if (iw3_pass_def->vertexDecl) pass_def->vertexDecl = dump_vertex_decl(vertex_decl_name, iw3_pass_def->vertexDecl, mem);
							if (iw3_pass_def->vertexShader) pass_def->vertexShader = dump_vertex_shader(iw3_pass_def->vertexShader, mem);

							const auto arg_count = pass_def->perPrimArgCount + pass_def->perObjArgCount + pass_def->stableArgCount;
							if (arg_count > 0)
							{
								pass_def->argumentDef = mem->Alloc<IW4::ShaderArgumentDef>(arg_count);
								memcpy(pass_def->argumentDef, iw3_pass_def->args, sizeof(IW4::ShaderArgumentDef) * arg_count);
							}
							
							for (auto arg = 0; arg < pass_def->perPrimArgCount + pass_def->perObjArgCount + pass_def->stableArgCount; arg++)
							{
								const auto arg_def = &pass_def->argumentDef[arg];
								if (arg_def->type == 3 || arg_def->type == 5)
								{
									if (iw3_code_const_map.find(arg_def->u.codeConst.index) != iw3_code_const_map.end())
									{
										arg_def->u.codeConst.index = iw3_code_const_map[arg_def->u.codeConst.index];
									}
								}
							}
						}
					}
				}
			}

			IW4::ITechset::dump(iw4_techset);
		}
	}
}
