#pragma once
#include "src/common/include/statement_type.h"

using namespace graphflow::common;

namespace graphflow {
namespace parser {

class Statement {
public:
    explicit Statement(StatementType statementType) : statementType{statementType} {}

    inline StatementType getStatementType() const { return statementType; }

private:
    StatementType statementType;
};

} // namespace parser
} // namespace graphflow
