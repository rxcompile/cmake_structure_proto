from conans import ConanFile, CMake, tools
import os

class encoreConan(ConanFile):
    name = "encore"
    version = "1.0.0"
    license = "<Put the package license here>"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "encore engine"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "use_nvapi": [True, False],
        "use_tcmalloc": [True, False],
        "enable_texture_streaming": [True, False],
        "enable_geometry_streaming": [True, False],
        "enable_reflection": [True, False],
        }
    default_options = {
        "shared": False,
        "use_nvapi": True,
        "use_tcmalloc": True,
        "enable_texture_streaming": True,
        "enable_geometry_streaming": True,
        "enable_reflection": False,

        "boost:header_only": True,
        }
    generators = "cmake"
    exports_sources = "src/*", "CMakeLists.txt"

    def requirements(self):
        self.requires.add("boost/1.68.0@conan/stable", private=True)
        self.requires.add("gtest/1.8.1@bincrafters/stable", private=True)
        self.requires.add("encore_common/1.0.0@company/stable", private=False)

    def build(self):
        cmake = CMake(self)
        definitions = dict()
        definitions["USE_NVAPI"] = "ON" if self.options.use_nvapi else "OFF"
        definitions["USE_TCMALLOC"] = "ON" if self.options.use_tcmalloc else "OFF"
        definitions["ENABLE_TEXTURE_STREAMING"] = "ON" if self.options.enable_texture_streaming else "OFF"
        definitions["ENABLE_GEOMETRY_STREAMING"] = "ON" if self.options.enable_geometry_streaming else "OFF"
        definitions["ENABLE_REFLECTION"] = "ON" if self.options.enable_reflection else "OFF"
        cmake.configure(defs=definitions)
        cmake.build()

    def package(self):
        for lib in os.listdir("src"):
            if os.path.isdir("src/"+ lib):
                src_path = "src/"+lib+"/include"
                self.copy("*.hpp", dst="include", src=src_path)

        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
