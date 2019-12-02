libtomcrypt = {}

function libtomcrypt:include()
	includedirs {
		path.join(DependencyFolder(), "libtomcrypt/src/headers")
	}
end

function libtomcrypt:link()
	self:include()
	links {
		"libtomcrypt"
	}
end

function libtomcrypt:project()
	local folder = DependencyFolder();

	project "libtomcrypt"
	
		location "%{wks.location}/dep"
		kind "StaticLib"
		language "C"
		
		files {
			path.join(folder, "libtomcrypt/src/**.h"), 
			path.join(folder, "libtomcrypt/src/**.c") 
		}
		
		defines {
			"_CRT_SECURE_NO_WARNINGS",
			"_CRT_NONSTDC_NO_DEPRECATE",
			"LTC_SOURCE",
			"LTC_NO_TEST",
			"LTC_NO_PROTOTYPES"
		}
		
		self:include()
		libtommath:include()

		-- Disable warnings. They do not have any value to us since it is not our code.
		warnings "off"
end
