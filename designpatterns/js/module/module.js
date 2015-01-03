var module = {
    prop: "value",
    say: function() {
        console.log("saying somehting...");
    }
};
console.log(module.prop);
module.say();
module.newSay = function() {
    console.log("new saying");
};
module.newSay();


var m = (function(mixin) {
    var c = 0;

    return {
        inc: function() {
            c++;
        },
        decr: function() {
            c--;
        },
        print: function() {
            console.log("counter=" + c + " inject");
            mixin.say();
        }
    };
})(module);

m.inc();
m.print();
m.decr();
m.print();
console.log(typeof m.c === "undefined");
