/**
 * @constructor
 */
var Queue = function() {
    this.inStk = [];
    this.outStk = [];
};

/**
 * @param {number} x
 * @returns {void}
 */
Queue.prototype.push = function(x) {
    while (this.outStk.length)
        this.inStk.push(this.outStk.pop());
    this.inStk.push(x);
    while (this.inStk.length)
        this.outStk.push(this.inStk.pop());
};

/**
 * @returns {void}
 */
Queue.prototype.pop = function() {
    this.outStk.pop();
};

/**
 * @returns {number}
 */
Queue.prototype.peek = function() {
    return this.outStk[this.outStk.length-1];
};

/**
 * @returns {boolean}
 */
Queue.prototype.empty = function() {
    return this.outStk.length === 0 ? true : false;
};
