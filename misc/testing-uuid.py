import uuid

print "uuid1::UUID based on host ID and time: ", uuid.uuid1()
print "uuid3::UUID based on a MD5 hash of namespace and a name: ", uuid.uuid3(uuid.NAMESPACE_DNS, 'rohityadav.in')
print "uuid4::Random UUID: ", uuid.uuid4()
print "uuid5::UUID based on SHA-1 hash of namespace UUID and a name: ", uuid.uuid5(uuid.NAMESPACE_DNS, 'rohityadav.in')

