function debug(string) {
    console.log('[DEBUG] ' + string);
}

function alert(value) {
    console.log('[ALERT] alert: ' + value);
    console.log('');
}

function MONAD(modifier) {
    var prototype = {};
    function unit(value) {
        var monad = Object.create(prototype);
        monad.bind = function (func, args) {
            debug('Returned binded function call');
            return func(value, args);
        };
        if (typeof modifier === 'function') {
            modifier(monad, value);
            debug('Monadic modified called');
        }
        debug('Returned monad');
        return monad;
    }
    unit.lift = function (name, func) {
        prototype[name] = function(args) {
            return unit(this.bind(func, args));
        };
        debug('Returned lifted monadic unit');
        return unit;
    }
    debug('Returned monadic unit');
    return unit;
}


debug('Creating ajax monad and lifting with alert()');
var ajax = MONAD().lift('alert', alert);
debug('Ajax monad created with a string');
var monad = ajax('hello from monad');
debug('Ajax monad called with a string');
monad.alert();

debug('Creating a maybe monad')
var maybe = MONAD(function(monad, value) {
    if (value == null || value == undefined) {
        monad.is_null = true;
        monad.bind = function () {
            debug('Null bind called');
            return monad;
        }
    }
});

debug('Maybe monad lifted with alert');
var maybeMonad = maybe.lift('alert', alert);
//maybeMonad.bind(alert);
maybeMonad(null).alert();
maybeMonad('This should get printed').alert();
debug('Only one alert should be returned')
