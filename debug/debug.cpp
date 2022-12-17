

#include "src/main/include/graphflowdb.h"

using namespace std;
using namespace graphflow::main;
// using namespace graphflow::common;


// void runQuery(const string& serializedPath, const string& queryPath, uint64_t numThreads,
//               bool executePlans = true) {
//     assert(numThreads <= 8);
//     // auto query = ReadFile(queryPath);
//     DatabaseConfig databaseConfig(serializedPath);
//     SystemConfig systemConfig;
//     systemConfig.maxNumThreads = 8;
//     systemConfig.defaultPageBufferPoolSize = 1ull << 30;
//     systemConfig.largePageBufferPoolSize = 1ull << 30;
//     auto database = make_unique<Database>(databaseConfig, systemConfig);
//     auto conn = make_unique<Connection>(database.get());
//     conn->setMaxNumThreadForExec(numThreads);
//     conn->query("");
// }

void print(unique_ptr<QueryResult> & result2) {
       if (!result2->isSuccess()) {
       cout << result2->getErrorMessage() << endl;
   }
   else {
    Value *resultVal;
    while (result2->hasNext()) {
        auto tuple = result2->getNext();
        resultVal = tuple->getValue(0);
        cout << tuple->toString() << endl;
        }
   }
}

int main() {
    string dbPath = "/Users/kriti/Projects/graphflowdb/dbFiles"; // specify a directory where you want to put db files
    DatabaseConfig databaseConfig(dbPath);
    SystemConfig systemConfig;
    systemConfig.maxNumThreads = 8;
    systemConfig.defaultPageBufferPoolSize = 1ull << 30;
    systemConfig.largePageBufferPoolSize = 1ull << 30;
    auto database = make_unique<Database>(databaseConfig, systemConfig);
    auto conn = make_unique<Connection>(database.get());
    // Put your create node table / copy queries here.
   // auto result = conn->query("create node table person (ID INT64, fName STRING, gender INT64, isStudent BOOLEAN, isWorker BOOLEAN, age INT64, eyeSight DOUBLE, birthdate DATE, registerTime TIMESTAMP, lastJobDuration INTERVAL, PRIMARY KEY (ID));");
//    auto result = conn->query("create node table person (ID INT64, randomString STRING, PRIMARY KEY (ID));");
//    result = conn->query("COPY person FROM \"/Users/kriti/Projects/graphflowdb/dataset/copy-csv-node-property-test/vPerson.csv\" (HEADER=true);");
//    if (!result->isSuccess()) {
//        cout << result->getErrorMessage() << endl;
//    }
// cout << "Querying the table";
//    auto result2 = conn->query("MATCH (p:person) WHERE p.randomString = \"lkkedqnjfeiazfhaiggzvamacqdzvjpmkdjslajqc\" RETURN p.doublePropKey1");
//    if (!result2->isSuccess()) {
//        cout << result2->getErrorMessage() << endl;
//    }
//    else {
//     Value *resultVal;
//     while (result2->hasNext()) {
//         auto tuple = result2->getNext();
//         resultVal = tuple->getValue(0);
//         cout << tuple->toString() << endl;
//         }
//    }

    
    // auto result = conn->query("create node table sample (ID INT64,randomString STRING, PRIMARY KEY (ID));");
    // result = conn->query("COPY sample FROM \"/Users/kriti/Projects/graphflowdb/dataset/copy-csv-node-property-test/vPersonTailored.csv\" (HEADER=false);");
    // auto finish = std::chrono::high_resolution_clock::now();
    

    // cout<<"The first set of experiments";

    // cout<< "Sorted Order Eval\n";
    // cout<<"Early in sort order\n";
    // auto result2 = conn->query("MATCH (p:sample) WHERE p.randomString = \"unsortedUnstrPropList100\" RETURN p.eius;");
    // print(result2);
    // result2 = conn->query("MATCH (p:sample) WHERE p.randomString = \"unsortedUnstrPropList1000\" RETURN p.aliquid;");
    // print(result2);

    // cout<<"Later in sort order\n";
    //  result2 = conn->query("MATCH (p:sample) WHERE p.randomString = \"unsortedUnstrPropList100\" RETURN p.perspiciatis;");
    //  print(result2);
    // result2 = conn->query("MATCH (p:sample) WHERE p.randomString = \"unsortedUnstrPropList1000\" RETURN p.voluptatibus;");
    // print(result2);

    // cout<<"Mixed bag\n";
    // result2 = conn->query("MATCH (p:sample) WHERE p.randomString = \"unsortedUnstrPropList100\" RETURN p.perspiciatis AND p.eius;");
    // print(result2);
    // result2 = conn->query("MATCH (p:sample) WHERE p.randomString = \"unsortedUnstrPropList1000\" RETURN p.voluptatibus AND p.aliquid;");
    // print(result2);

    cout<< "KV sep eval";

    // for optimized impl
    // cout<<"10";
    // auto result2 = conn->query("MATCH (p:sample) WHERE p.randomString = \"unsortedUnstrPropList10\" RETURN p.dolores;");
    // print(result2);
    // cout<<"10";
    // result2 = conn->query("MATCH (p:sample) WHERE p.randomString = \"unsortedUnstrPropList100\" RETURN p.aliquid;");
    // print(result2);
    // cout<<"10";
    // result2 = conn->query("MATCH (p:sample) WHERE p.randomString = \"unsortedUnstrPropList1000\" RETURN p.eius;");
    // print(result2);


    // for OG impl
    auto result2 = conn->query("MATCH (p:sample) WHERE p.randomString = \"sortedUnstrPropList10\" RETURN p.dolores;");
    print(result2);
    result2 = conn->query("MATCH (p:sample) WHERE p.randomString = \"sortedUnstrPropList100\" RETURN p.aliquid;");
    print(result2);
    result2 = conn->query("MATCH (p:sample) WHERE p.randomString = \"sortedUnstrPropList1000\" RETURN p.eius;");
    print(result2);
}
