import os
import sysconfig

import pybind11
from invoke import task


@task
def build_pybind11(ctx):
    python_include = sysconfig.get_paths()["include"]
    pybind11_include = pybind11.get_include()
    py_suffix = sysconfig.get_config_var(
        "EXT_SUFFIX"
    )  # Gets the extension suffix (e.g., .so, .pyd)
    speex_include = "/usr/include"  # Update this if needed
    speex_lib = "/usr/lib"  # Update this if needed

    source_files = (
        "utils/pybind11/pybind_pyspeexdsp.cpp src/pyspeexdsp/echo_canceller.cpp"
    )
    output_file = f"pyspeexdsp{py_suffix}"

    cmd = (
        f"c++ -O3 -Wall -shared -std=c++11 -fPIC "
        f"-I{python_include} -I{pybind11_include} -I{speex_include} "
        f"{source_files} -o {output_file} -L{speex_lib} -lspeexdsp"
    )

    print(f"Running command: {cmd}")

    ctx.run(cmd, pty=True)


@task
def clean(ctx):
    """
    Clean up generated files from the build process.
    """
    # Remove generated SWIG and build files
    files_to_remove = [
        f"pyspeexdsp{sysconfig.get_config_var('EXT_SUFFIX')}",
    ]
    for file in files_to_remove:
        if os.path.exists(file):
            print(f"Removing {file}")
            os.remove(file)
