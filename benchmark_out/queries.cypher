

// Queries for testing padding

// this query should implement the changes
MATCH (p:person) WHERE p.randomString = \"unsortedUnstrPropList10\" RETURN p.dolores;
// numbers tested against pre sorted order
MATCH (p:person) WHERE p.randomString = \"sortedUnstrPropList10\" RETURN p.dolores;

MATCH (p:person) WHERE p.randomString = \"unsortedUnstrPropList100\" RETURN p.aliquid;
MATCH (p:person) WHERE p.randomString = \"sortedUnstrPropList100\" RETURN p.aliquid;

MATCH (p:person) WHERE p.randomString = \"unsortedUnstrPropList10\" RETURN p.eius;
MATCH (p:person) WHERE p.randomString = \"sortedUnstrPropList10\" RETURN p.eius;


// Queries to test scans and sorting
// purposely selected something that would be to the front


MATCH (p:person) WHERE p.randomString = \"unsortedUnstrPropList100\" RETURN p.eius;
MATCH (p:person) WHERE p.randomString = \"unsortedUnstrPropList1000\" RETURN p.aliquid;


// Queries that do not see benefit because of sorted storage

MATCH (p:person) WHERE p.randomString = \"unsortedUnstrPropList100\" RETURN p.perspiciatis;
MATCH (p:person) WHERE p.randomString = \"unsortedUnstrPropList1000\" RETURN p.voluptatibus;

// Mixed set queries
MATCH (p:person) WHERE p.randomString = \"unsortedUnstrPropList100\" RETURN p.perspiciatis AND p.eius;
MATCH (p:person) WHERE p.randomString = \"unsortedUnstrPropList1000\" RETURN p.voluptatibus AND p.aliquid;
