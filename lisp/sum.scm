(define (sum a b F next)
    (if
        (> a b) 0
        (+ (F a) (sum (next a) b F next))))

(sum 1 10 (lambda (x) x) 1+)
