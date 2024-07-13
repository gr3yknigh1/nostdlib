from os.path import join

from conan import ConanFile
from conan.tools.files import copy
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps

class NoStdLibRecipe(ConanFile):
    name = "nostdlib"
    version = "0.0.1"

    # Optional metadata
    license = "Copyright (c) 2024, Ilya Akkuzin, all rights reserved"
    author = "Ilya Akkuzin <gr3yknigh1@gmail.com>"
    url = "https://github.com/gr3yknigh1/nostdlib"
    description = "Say no to libc"
    topics = ("std", "libc")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "with_tests": [True, False],
    }

    default_options = {
        "shared": False,
        "fPIC": True,
        "with_tests": True
    }

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "include/*"

    def requirements(self):
        if self.options.with_tests:
            self.requires("nocheck/0.0.1")

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.includedirs = ["include"]
        self.cpp_info.libdirs = ["lib"]
        self.cpp_info.libs = ["noc"]
