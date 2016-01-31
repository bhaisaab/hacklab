function MONAD() {
    var prototype = {};
    function unit(value) {
        var monad = Object.create(prototype);
        console.log(monad);
        monad.bind = function (func, args) {
            return func(value, args);
        };
        return monad;
    }
    unit.lift = function (name, func) {
        prototype[name] = function(args) {
            return unit(this.bind(func, args));
        };
        return unit;
    }
    return unit;
}

function alert(value) {
    console.log('alert: ' + value);
}

var ajax = MONAD().lift('alert', alert);
// AJAX monad
var monad = ajax('hello from monad');
monad.alert();
