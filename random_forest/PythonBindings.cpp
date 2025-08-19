# include <pybind11/pybind11.h>
# include <pybind11/stl.h>
# include "Randomforest.h"

namespace py = pybind11;

PYBIND11_MODULE(RandomForest, m) {
    py::class_<RandomForest>(m, "RandomForest")
        .def(py::init<std::vector<std::vector<int>>, std::vector<int>>())
        .def("predict", &RandomForest::predict)
        .def("predictmany", &RandomForest::predictMany);

}
