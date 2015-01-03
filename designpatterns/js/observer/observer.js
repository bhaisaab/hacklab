var list = require('./list');

function Subject() {
    this.observerList = new list.List();
    this.addObserver = function(o) {
        this.observerList.add(o);
    };
    this.removeObserver = function(o) {
        this.observerList.removeAt(this.observerList.indexOf(o));
    };
    this.notify = function(context) {
        for (var i=0; i < this.observerList.count(); i++) {
            this.observerList.get(i).update(context);
        }
    };
}

function Observer(name) {
    this.name = name;
    this.whoami = function() {
        return this.name;
    };
    this.update = function(ctx) {
        console.log(this.whoami() + " update = " + ctx);
    }
};

var p1 = new Observer("mambo");
var p2 = new Observer("rambo");
var p3 = new Observer("mugambo");

var time = new Subject();
time.showTime = function() {
    var date = new Date().getTime();
    this.notify(date);
};

time.addObserver(p1);
time.addObserver(p2);
time.addObserver(p3);
time.showTime();

console.log("Removing rambo");
time.removeObserver(p2);
time.showTime();
