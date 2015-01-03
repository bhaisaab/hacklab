
// defineProperty can be used to extend an object
var defineProperty = function (object, key, value) {
    var config = {
        value: value,
        writable: true,
        enumerable: true,
        configurable: true
    };
    Object.defineProperty(object, key, config);
};

var person = Object.create(Object.prototype); // or {} or new Object()
defineProperty(person, "dateOfBirth", "1000");
console.log(person.dateOfBirth);

var driver = Object.create(person);
defineProperty(driver, "car", "BMW");
console.log(driver.car);

// Basic constructor
function Car(model, year, miles) {
    this.model = model;
    this.year = year;
    this.miles = miles;

    this.toString = function() {
        return this.model + " of year " + this.year + " has run " + this.miles + " miles";
    };
}

Car.prototype.fuelEfficiency = function() {
    console.log("Car consumes 1 litre diesel per 25 kms");
};

var amaze = new Car('amaze', 2014, 12323);
console.log(amaze.toString());
amaze.fuelEfficiency();
