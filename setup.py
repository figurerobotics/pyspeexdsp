import pybind11
from setuptools import Extension, find_packages, setup

pybind11_include = pybind11.get_include()

# Read the requirements from requirements.txt
with open("requirements.txt") as f:
    requirements = f.read().splitlines()

ext_modules = [
    Extension(
        "pyspeexdsp.pyspeexdsp",
        sources=[
            "src/pyspeexdsp/echo_canceller.cpp",
            "utils/pybind11/pybind_pyspeexdsp.cpp",
        ],
        include_dirs=[
            pybind11_include,
            "src/pyspeexdsp",
            "/usr/include",
        ],
        library_dirs=["/usr/lib"],
        libraries=["speexdsp"],
        extra_compile_args=[
            "-O3",
            "-Wall",
            "-shared",
            "-std=c++11",
            "-fPIC",
        ],
        language="c++",
    ),
]

setup(
    name="pyspeexdsp",
    version="1.0.0",
    author="Stephen Sherbrook",
    author_email="stephen.sherbrook@figure.ai",
    description="Python bindings to SpeexDSP",
    package_dir={"": "src"},
    packages=find_packages(where="src"),
    ext_modules=ext_modules,
    install_requires=requirements,
    extras_require={
        "dev": ["invoke"],  # Optional development dependencies
    },
    zip_safe=False,
    include_package_data=True,
    classifiers=[
        "Programming Language :: Python :: 3",
        "Programming Language :: C++",
        "Operating System :: POSIX :: Linux",
    ],
    platforms=["Linux"],
)
