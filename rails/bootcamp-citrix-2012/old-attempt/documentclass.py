from couchdb.mapping import TextField, IntegerField, DateTimeField, ListField

class Booking(Document):
  name = TextField()
  date = DateTimeField()
  time = DateTimeField()
  duration = IntergerField() # In minutes

class City(Document):
  name = TextField()
  #buildings = ListField()

class Building(Document):
  name = TextField()
  city = TextField()

class Room(Document):
  name = TextField()
  capacity = IntergerField()
  building = TextField()
