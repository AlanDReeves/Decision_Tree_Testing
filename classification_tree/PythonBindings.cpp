# include <pybind11/pybind11.h>
# include <pybind11/stl.h>
# include "ClassificationTree.h"

namespace py = pybind11;

PYBIND11_MODULE(Classification_Tree, m) {
    py::class_<ClassificationTree>(m, "ClassificationTree")
        .def(py::init<std::vector<std::vector<int>>, std::vector<int>>());
}

