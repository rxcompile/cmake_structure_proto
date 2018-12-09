from conans import ConanFile, CMake, tools

class EncoreCommonConan(ConanFile):
    name = "encore_common"
    version = "1.0.0"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"
    exports_sources = "src/*", "cmake/*", "CMakeLists.txt", "!*/test/*"

    def _configure_cmake(self):
        cmake = CMake(self)
        # pass generation definitions and options
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
