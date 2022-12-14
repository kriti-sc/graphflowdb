#pragma once

#include "src/function/include/vector_operations.h"

namespace graphflow {
namespace function {
class VectorDateOperations : public VectorOperations {};

struct DayNameVectorOperation : public VectorDateOperations {
    static vector<unique_ptr<VectorOperationDefinition>> getDefinitions();
};

struct MonthNameVectorOperation : public VectorDateOperations {
    static vector<unique_ptr<VectorOperationDefinition>> getDefinitions();
};

struct LastDayVectorOperation : public VectorDateOperations {
    static vector<unique_ptr<VectorOperationDefinition>> getDefinitions();
};

struct DatePartVectorOperation : public VectorDateOperations {
    static vector<unique_ptr<VectorOperationDefinition>> getDefinitions();
};

struct DateTruncVectorOperation : public VectorDateOperations {
    static vector<unique_ptr<VectorOperationDefinition>> getDefinitions();
};

struct GreatestVectorOperation : public VectorDateOperations {
    static vector<unique_ptr<VectorOperationDefinition>> getDefinitions();
};

struct LeastVectorOperation : public VectorDateOperations {
    static vector<unique_ptr<VectorOperationDefinition>> getDefinitions();
};

struct MakeDateVectorOperation : public VectorDateOperations {
    static vector<unique_ptr<VectorOperationDefinition>> getDefinitions();
};

} // namespace function
} // namespace graphflow
