#include "test/test_utility/include/test_helper.h"

using namespace std;
using namespace graphflow::common;
using namespace graphflow::storage;
using namespace graphflow::testing;

class TinySnbCopyCSVDateTest : public InMemoryDBTest {
    string getInputCSVDir() override { return "dataset/tinysnb/"; }
};

// Warning: This test assumes that each line in tinysnb's vPerson.csv gets
// the node offsets that start from 0 consecutively (so first line gets person ID 0, second person
// ID 1, so on and so forth).
TEST_F(TinySnbCopyCSVDateTest, NodePropertyColumnWithDate) {
    auto& catalog = *database->getCatalog();
    auto tableID = catalog.getReadOnlyVersion()->getNodeTableIDFromName("person");
    auto propertyIdx = catalog.getReadOnlyVersion()->getNodeProperty(tableID, "birthdate");
    auto col = database->getStorageManager()->getNodesStore().getNodePropertyColumn(
        tableID, propertyIdx.propertyID);
    ASSERT_FALSE(col->isNull(0));
    EXPECT_EQ(Date::FromDate(1900, 1, 1).days, col->readValue(0).val.dateVal.days);
    ASSERT_FALSE(col->isNull(1));
    EXPECT_EQ(Date::FromDate(1900, 1, 1).days, col->readValue(1).val.dateVal.days);
    ASSERT_FALSE(col->isNull(2));
    EXPECT_EQ(Date::FromDate(1940, 6, 22).days, col->readValue(2).val.dateVal.days);
    ASSERT_FALSE(col->isNull(3));
    EXPECT_EQ(Date::FromDate(1950, 7, 23).days, col->readValue(3).val.dateVal.days);
    ASSERT_FALSE(col->isNull(4));
    EXPECT_EQ(Date::FromDate(1980, 10, 26).days, col->readValue(4).val.dateVal.days);
    ASSERT_FALSE(col->isNull(5));
    EXPECT_EQ(Date::FromDate(1980, 10, 26).days, col->readValue(5).val.dateVal.days);
    ASSERT_FALSE(col->isNull(6));
    EXPECT_EQ(Date::FromDate(1980, 10, 26).days, col->readValue(6).val.dateVal.days);
    ASSERT_FALSE(col->isNull(7));
    EXPECT_EQ(Date::FromDate(1990, 11, 27).days, col->readValue(7).val.dateVal.days);
}
