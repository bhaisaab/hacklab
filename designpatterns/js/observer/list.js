module.exports = {
    List: List
};

function List() {
    this.l = [];

    this.add = function(o) {
        this.l.push(o);
    };
    this.count = function() {
        return this.l.length;
    };
    this.get = function(idx) {
        if (idx > -1 && idx < this.l.length) {
            return this.l[idx];
        }
    };
    this.indexOf = function (obj) {
        for (var i = 0; i < this.l.length; i++) {
            if (this.l[i] === obj) {
                return i;
            }
        }
        return -1;
    };
    this.removeAt = function(idx) {
        this.l.splice(idx, 1);
    };
};
