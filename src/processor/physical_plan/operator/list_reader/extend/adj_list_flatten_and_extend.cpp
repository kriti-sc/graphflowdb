#include "src/processor/include/physical_plan/operator/list_reader/extend/adj_list_flatten_and_extend.h"

namespace graphflow {
namespace processor {

bool AdjListFlattenAndExtend::hasNextMorsel() {
    return (inDataChunk->size > 0ul && inDataChunk->size > inDataChunk->currPos + 1l) ||
           handle->hasMoreToRead() || prevOperator->hasNextMorsel();
}

void AdjListFlattenAndExtend::getNextTuples() {
    if (handle->hasMoreToRead()) {
        readValuesFromList();
        return;
    }
    if (inDataChunk->size == 0ul || inDataChunk->size == inDataChunk->currPos + 1ul) {
        inDataChunk->currPos = -1;
        prevOperator->getNextTuples();
        if (inDataChunk->size == 0) {
            outDataChunk->size = 0;
            return;
        }
    }
    inDataChunk->currPos++;
    readValuesFromList();
}

} // namespace processor
} // namespace graphflow