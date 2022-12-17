
from lorem_text import lorem

set10 = lorem.words(10).split()
set100 = lorem.words(100).split()
set1000 = lorem.words(1000).split()

unstrPropList10 = []
unstrPropList100 = []
unstrPropList1000 = []


for word in set10:
    unstrPropList10.append(word+":INT64:2385")

print(','.join(unstrPropList10))
print()
unstrPropList10.sort()

print(','.join(unstrPropList10))
print()


for word in set100:
    unstrPropList100.append(word+":INT64:2385")

print(','.join(unstrPropList100))
print()
unstrPropList100.sort()

print(','.join(unstrPropList100))
print()


for word in set1000:
    unstrPropList1000.append(word+":INT64:2385")

print(','.join(unstrPropList1000))
print()
unstrPropList1000.sort()

print(','.join(unstrPropList1000))
print()
