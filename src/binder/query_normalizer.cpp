#include "include/query_normalizer.h"

#include "src/binder/expression/include/existential_subquery_expression.h"

namespace graphflow {
namespace binder {

unique_ptr<NormalizedSingleQuery> QueryNormalizer::normalizeQuery(
    const BoundSingleQuery& singleQuery) {
    auto normalizedQuery = make_unique<NormalizedSingleQuery>();
    for (auto i = 0u; i < singleQuery.getNumQueryParts(); ++i) {
        normalizedQuery->appendQueryPart(normalizeQueryPart(*singleQuery.getQueryPart(i)));
    }
    auto finalQueryPart = normalizeFinalMatchesAndReturnAsQueryPart(singleQuery);
    normalizedQuery->appendQueryPart(normalizeQueryPart(*finalQueryPart));
    return normalizedQuery;
}

unique_ptr<BoundQueryPart> QueryNormalizer::normalizeFinalMatchesAndReturnAsQueryPart(
    const BoundSingleQuery& singleQuery) {
    auto queryPart = make_unique<BoundQueryPart>();
    for (auto i = 0u; i < singleQuery.getNumReadingClauses(); i++) {
        queryPart->addReadingClause(singleQuery.getReadingClause(i)->copy());
    }
    for (auto i = 0u; i < singleQuery.getNumUpdatingClauses(); ++i) {
        queryPart->addUpdatingClause(singleQuery.getUpdatingClause(i)->copy());
    }
    if (singleQuery.hasReturnClause()) {
        queryPart->setWithClause(make_unique<BoundWithClause>(
            make_unique<BoundProjectionBody>(*singleQuery.getReturnClause()->getProjectionBody())));
    }
    return queryPart;
}

unique_ptr<NormalizedQueryPart> QueryNormalizer::normalizeQueryPart(
    const BoundQueryPart& queryPart) {
    auto normalizedQueryPart = make_unique<NormalizedQueryPart>();
    for (auto i = 0u; i < queryPart.getNumReadingClauses(); i++) {
        if (queryPart.getReadingClause(i)->getClauseType() == ClauseType::MATCH) {
            auto matchClause = (BoundMatchClause*)queryPart.getReadingClause(i);
            normalizedQueryPart->addQueryGraph(matchClause->getQueryGraph()->copy(),
                matchClause->hasWhereExpression() ? matchClause->getWhereExpression() : nullptr,
                matchClause->getIsOptional());
        } else {
            assert(queryPart.getReadingClause(i)->getClauseType() == ClauseType::UNWIND);
            auto unwindClause = (BoundUnwindClause*)queryPart.getReadingClause(i);
            normalizedQueryPart->addUnwindClauses(make_unique<BoundUnwindClause>(*unwindClause));
        }
    }
    for (auto i = 0u; i < queryPart.getNumUpdatingClauses(); ++i) {
        normalizedQueryPart->addUpdatingClause(queryPart.getUpdatingClause(i)->copy());
    }
    if (queryPart.hasWithClause()) {
        auto withClause = queryPart.getWithClause();
        normalizedQueryPart->setProjectionBody(withClause->getProjectionBody()->copy());
        if (withClause->hasWhereExpression()) {
            normalizedQueryPart->setProjectionBodyPredicate(withClause->getWhereExpression());
        }
    }
    return normalizedQueryPart;
}

} // namespace binder
} // namespace graphflow
