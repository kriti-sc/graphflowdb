#include "src/parser/antlr_parser/include/graphflow_cypher_parser.h"

#include <string>

using namespace std;

namespace graphflow {
namespace parser {

void GraphflowCypherParser::notifyQueryNotConcludeWithReturn(antlr4::Token* startToken) {
    auto errorMsg = "Query must conclude with RETURN clause";
    notifyErrorListeners(startToken, errorMsg, nullptr);
}

void GraphflowCypherParser::notifyNodePatternWithoutParentheses(
    std::string nodeName, antlr4::Token* startToken) {
    auto errorMsg =
        "Parentheses are required to identify nodes in patterns, i.e. (" + nodeName + ")";
    notifyErrorListeners(startToken, errorMsg, nullptr);
}

void GraphflowCypherParser::notifyInvalidNotEqualOperator(antlr4::Token* startToken) {
    auto errorMsg = "Unknown operation '!=' (you probably meant to use '<>', which is the operator "
                    "for inequality testing.)";
    notifyErrorListeners(startToken, errorMsg, nullptr);
}

void GraphflowCypherParser::notifyEmptyToken(antlr4::Token* startToken) {
    auto errorMsg =
        "'' is not a valid token name. Token names cannot be empty or contain any null-bytes";
    notifyErrorListeners(startToken, errorMsg, nullptr);
}

void GraphflowCypherParser::notifyReturnNotAtEnd(antlr4::Token* startToken) {
    auto errorMsg = "RETURN can only be used at the end of the query";
    notifyErrorListeners(startToken, errorMsg, nullptr);
}

void GraphflowCypherParser::notifyNonBinaryComparison(antlr4::Token* startToken) {
    auto errorMsg = "Non-binary comparison (e.g. a=b=c) is not supported";
    notifyErrorListeners(startToken, errorMsg, nullptr);
}

} // namespace parser
} // namespace graphflow
