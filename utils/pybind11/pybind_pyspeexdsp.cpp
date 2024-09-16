#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>  // For py::bytes

#include "echo_canceller.h"

namespace py = pybind11;

PYBIND11_MODULE(pyspeexdsp, m) {
    py::class_<EchoCanceller>(m, "EchoCanceller", "EchoCanceller class for acoustic echo cancellation.")
        .def(py::init<int, int, int, int, int>(), 
             py::arg("frame_size") = 256,
             py::arg("filter_length") = 2048,
             py::arg("sample_rate") = 16000,
             py::arg("mics") = 1,
             py::arg("speakers") = 1,
             "Constructor for the EchoCanceller class.")
        .def("process", 
             [](EchoCanceller &self, const py::bytes &near, const py::bytes &far) -> py::bytes {
                 std::string near_data = near;
                 std::string far_data = far;
                 std::string result = self.process(near_data, far_data);
                 return py::bytes(result);
             }, 
             py::arg("near"), py::arg("far"), 
             "Processes audio data for echo cancellation.")
        .def("set_echo_suppress", &EchoCanceller::set_echo_suppress, py::arg("level"),
             "Sets the echo suppression level.")
        .def("enable_echo_suppression", &EchoCanceller::enable_echo_suppression, py::arg("enable"),
             "Enables or disables echo suppression.");
}