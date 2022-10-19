/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   /home/workspace/gem5/build/ARM/SConscript:781
 */

#include "base/compiler.hh"
#include "enums/ArmMachineType.hh"

namespace gem5
{

GEM5_DEPRECATED_NAMESPACE(Enums, enums);
namespace enums
{
    const char *ArmMachineTypeStrings[Num_ArmMachineType] =
    {
        "DTOnly",
        "VExpress_EMM",
        "VExpress_EMM64",
    };
} // namespace enums
} // namespace gem5
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include <sim/init.hh>

namespace py = pybind11;

namespace gem5
{

static void
module_init(py::module_ &m_internal)
{
    py::module_ m = m_internal.def_submodule("enum_ArmMachineType");

py::enum_<enums::ArmMachineType>(m, "enum_ArmMachineType")
        .value("DTOnly", enums::DTOnly)
        .value("VExpress_EMM", enums::VExpress_EMM)
        .value("VExpress_EMM64", enums::VExpress_EMM64)
        .value("Num_ArmMachineType", enums::Num_ArmMachineType)
        .export_values()
        ;
    }

static EmbeddedPyBind embed_enum("enum_ArmMachineType", module_init);

} // namespace gem5