#pragma once

#include <thread>

#include "src/common/include/task_system/task_scheduler.h"
#include "src/processor/include/physical_plan/physical_plan.h"
#include "src/processor/include/physical_plan/result/factorized_table.h"
#include "src/storage/buffer_manager/include/memory_manager.h"

using namespace graphflow::storage;

namespace graphflow {
namespace processor {

class QueryProcessor {

public:
    explicit QueryProcessor(uint64_t numThreads);

    shared_ptr<FactorizedTable> execute(PhysicalPlan* physicalPlan, ExecutionContext* context);

private:
    void decomposePlanIntoTasks(PhysicalOperator* op, PhysicalOperator* parent, Task* parentTask,
        ExecutionContext* context);

private:
    unique_ptr<TaskScheduler> taskScheduler;
};

} // namespace processor
} // namespace graphflow
