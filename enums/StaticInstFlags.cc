/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   /home/workspace/gem5/build/RISCV/SConscript:781
 */

#include "base/compiler.hh"
#include "enums/StaticInstFlags.hh"

namespace gem5
{

const char *StaticInstFlags::FlagsStrings[Num_Flags] =
{
    "IsNop",
    "IsInteger",
    "IsFloating",
    "IsVector",
    "IsVectorElem",
    "IsLoad",
    "IsStore",
    "IsAtomic",
    "IsStoreConditional",
    "IsInstPrefetch",
    "IsDataPrefetch",
    "IsControl",
    "IsDirectControl",
    "IsIndirectControl",
    "IsCondControl",
    "IsUncondControl",
    "IsCall",
    "IsReturn",
    "IsSerializing",
    "IsSerializeBefore",
    "IsSerializeAfter",
    "IsWriteBarrier",
    "IsReadBarrier",
    "IsNonSpeculative",
    "IsQuiesce",
    "IsUnverifiable",
    "IsSyscall",
    "IsMacroop",
    "IsMicroop",
    "IsDelayedCommit",
    "IsLastMicroop",
    "IsFirstMicroop",
    "IsSquashAfter",
    "IsHtmStart",
    "IsHtmStop",
    "IsHtmCancel",
};
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
    py::module_ m = m_internal.def_submodule("enum_StaticInstFlags");

py::enum_<StaticInstFlags::Flags>(m, "enum_StaticInstFlags")
        .value("IsNop", StaticInstFlags::IsNop)
        .value("IsInteger", StaticInstFlags::IsInteger)
        .value("IsFloating", StaticInstFlags::IsFloating)
        .value("IsVector", StaticInstFlags::IsVector)
        .value("IsVectorElem", StaticInstFlags::IsVectorElem)
        .value("IsLoad", StaticInstFlags::IsLoad)
        .value("IsStore", StaticInstFlags::IsStore)
        .value("IsAtomic", StaticInstFlags::IsAtomic)
        .value("IsStoreConditional", StaticInstFlags::IsStoreConditional)
        .value("IsInstPrefetch", StaticInstFlags::IsInstPrefetch)
        .value("IsDataPrefetch", StaticInstFlags::IsDataPrefetch)
        .value("IsControl", StaticInstFlags::IsControl)
        .value("IsDirectControl", StaticInstFlags::IsDirectControl)
        .value("IsIndirectControl", StaticInstFlags::IsIndirectControl)
        .value("IsCondControl", StaticInstFlags::IsCondControl)
        .value("IsUncondControl", StaticInstFlags::IsUncondControl)
        .value("IsCall", StaticInstFlags::IsCall)
        .value("IsReturn", StaticInstFlags::IsReturn)
        .value("IsSerializing", StaticInstFlags::IsSerializing)
        .value("IsSerializeBefore", StaticInstFlags::IsSerializeBefore)
        .value("IsSerializeAfter", StaticInstFlags::IsSerializeAfter)
        .value("IsWriteBarrier", StaticInstFlags::IsWriteBarrier)
        .value("IsReadBarrier", StaticInstFlags::IsReadBarrier)
        .value("IsNonSpeculative", StaticInstFlags::IsNonSpeculative)
        .value("IsQuiesce", StaticInstFlags::IsQuiesce)
        .value("IsUnverifiable", StaticInstFlags::IsUnverifiable)
        .value("IsSyscall", StaticInstFlags::IsSyscall)
        .value("IsMacroop", StaticInstFlags::IsMacroop)
        .value("IsMicroop", StaticInstFlags::IsMicroop)
        .value("IsDelayedCommit", StaticInstFlags::IsDelayedCommit)
        .value("IsLastMicroop", StaticInstFlags::IsLastMicroop)
        .value("IsFirstMicroop", StaticInstFlags::IsFirstMicroop)
        .value("IsSquashAfter", StaticInstFlags::IsSquashAfter)
        .value("IsHtmStart", StaticInstFlags::IsHtmStart)
        .value("IsHtmStop", StaticInstFlags::IsHtmStop)
        .value("IsHtmCancel", StaticInstFlags::IsHtmCancel)
        .value("Num_StaticInstFlags", StaticInstFlags::Num_Flags)
        .export_values()
        ;
    }

static EmbeddedPyBind embed_enum("enum_StaticInstFlags", module_init);

} // namespace gem5
