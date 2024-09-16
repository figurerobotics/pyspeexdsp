# PySpeexDSP

Python bindings for the SpeexDSP library\
[git repo](https://github.com/xiph/speexdsp)\
[home page](https://www.speex.org/)

## Installation

1. Clone this repo.

2. Install libspeexdsp-dev
```bash
sudo apt update
sudo apt install libspeexdsp-dev
```

3. Run setup.py
```bash
pip install .
```

## Alternate installation method
tasks.py is included to build locally without installing it in your python environment.\
To utilize this build method, install the optional dev dependency with `pip install .[dev]`\
Once the dev dependencies are installed, build the package locally with:
```bash
invoke build-pybind11
```
If you want to start over, you can clean the generated file with `invoke clean`

## Usage
Currently, only the Echo Canceller and Echo Suppressor are implemented.  See `examples` directory for Jupyter notebook example.
