var singleton = (function() {
    var instance;
    function init() {
        //Declare class and obj here
        var privateV = 10;
        function privateM() {
            console.log("I'm private");
        };
        function publicM() {
            console.log("I'm public");
        };
        return {
            pub: publicM,
            get: function() {
                console.log(privateV++);
                privateM();
            }
        };
    };
    return {
        getInstance: function() {
            if (!instance) {
                instance = init();
            }
            return instance;
        }
    };
})();

var s1 = singleton.getInstance();
var s2 = singleton.getInstance();
s1.pub();
s2.pub();
s1.get();
s2.get();
