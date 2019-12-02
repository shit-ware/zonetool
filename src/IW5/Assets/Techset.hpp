// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#pragma once

namespace ZoneTool
{
	namespace IW5
	{
		class ITechset : public IAsset
		{
		private:
			std::string name_;
			MaterialTechniqueSet* asset_;
			bool m_parsed;
			
		public:
			static MaterialTechnique* parse_technique(const std::string& name, ZoneMemory* mem,
				std::uint32_t index);
			static MaterialTechniqueSet* parse(const std::string& name, ZoneMemory* mem);
			static char* parse_statebits(const std::string& techset, ZoneMemory* mem);
			
			void init(const std::string& name, ZoneMemory* mem) override;
			void prepare(ZoneBuffer* buf, ZoneMemory* mem) override;
			void load_depending(IZone* zone) override;

			std::string name() override;
			std::int32_t type() override;
			void write(IZone* zone, ZoneBuffer* buffer) override;

			static void dump_technique_data(MaterialTechniqueSet* asset, bool is_iw5 = true);
			static void dump_statebits(const std::string& techset, char* statebits);
			static void dump(MaterialTechniqueSet* asset);
			static void dump_technique(MaterialTechnique* asset);
		};
	}
}
