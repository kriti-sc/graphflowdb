#pragma once

#include "src/common/include/data_chunk/data_chunk.h"
#include "src/common/include/data_chunk/data_chunk_state.h"

using namespace graphflow::common;
using namespace std;

namespace graphflow {
namespace processor {

class FilteringOperator {
public:
    explicit FilteringOperator(uint64_t numStatesToSave) {
        for (auto i = 0u; i < numStatesToSave; ++i) {
            auto prevSelVector = make_unique<SelectionVector>(DEFAULT_VECTOR_CAPACITY);
            prevSelVector->selectedPositions = nullptr;
            prevSelVectors.push_back(move(prevSelVector));
        }
    }

protected:
    inline void reInitToRerunSubPlan() {
        for (auto& prevSelVector : prevSelVectors) {
            prevSelVector->selectedSize = 0;
            prevSelVector->selectedPositions = nullptr;
        }
    }

    inline void restoreSelVectors(vector<SelectionVector*>& selVectors) {
        for (auto i = 0u; i < selVectors.size(); ++i) {
            restoreSelVector(prevSelVectors[i].get(), selVectors[i]);
        }
    }
    inline void restoreSelVector(SelectionVector* selVector) {
        restoreSelVector(prevSelVectors[0].get(), selVector);
    }

    inline void saveSelVectors(vector<SelectionVector*>& selVectors) {
        for (auto i = 0u; i < selVectors.size(); ++i) {
            saveSelVector(prevSelVectors[i].get(), selVectors[i]);
        }
    }
    inline void saveSelVector(SelectionVector* selVector) {
        saveSelVector(prevSelVectors[0].get(), selVector);
    }

private:
    static void restoreSelVector(SelectionVector* prevSelVector, SelectionVector* selVector);
    static void saveSelVector(SelectionVector* prevSelVector, SelectionVector* selVector);

    vector<unique_ptr<SelectionVector>> prevSelVectors;
};
} // namespace processor
} // namespace graphflow
