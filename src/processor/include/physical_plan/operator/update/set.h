#pragma once

#include "src/expression_evaluator/include/base_evaluator.h"
#include "src/processor/include/physical_plan/operator/physical_operator.h"
#include "src/storage/storage_structure/include/column.h"

using namespace graphflow::evaluator;

namespace graphflow {
namespace processor {

class SetNodeStructuredProperty : public PhysicalOperator {

public:
    SetNodeStructuredProperty(vector<DataPos> nodeIDVectorPositions, vector<Column*> columns,
        vector<unique_ptr<BaseExpressionEvaluator>> expressionEvaluators,
        unique_ptr<PhysicalOperator> child, uint32_t id, const string& paramsString)
        : PhysicalOperator{move(child), id, paramsString}, nodeIDVectorPositions{move(
                                                               nodeIDVectorPositions)},
          columns{move(columns)}, expressionEvaluators{move(expressionEvaluators)} {}

    inline PhysicalOperatorType getOperatorType() override { return PhysicalOperatorType::SET; }

    shared_ptr<ResultSet> init(ExecutionContext* context) override;

    bool getNextTuples() override;

    unique_ptr<PhysicalOperator> clone() override;

private:
    vector<DataPos> nodeIDVectorPositions;
    vector<shared_ptr<ValueVector>> nodeIDVectors;
    vector<Column*> columns;
    vector<unique_ptr<BaseExpressionEvaluator>> expressionEvaluators;
};

} // namespace processor
} // namespace graphflow
