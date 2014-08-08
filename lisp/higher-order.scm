(define (sum a b F next)
    (if
        (> a b) 0
        (+ (F a) (sum (next a) b F next))))

(sum 1 10 (lambda (x) x) 1+)
(sum 1 10 (lambda (x) (* x x)) 1+)

(define tolerance 0.0000001)

;; f(x) = x for some x
(define (fixed-point f initial_guess)

    (define (isClose? a b)
        (< (abs (- a b)) tolerance))

    (newline)
    (define (try guess)
        (let ((next (f guess)))
          (display guess)
          (newline)
          (if (isClose? guess next)
              guess
              (try next))))
    (try initial_guess))


(fixed-point cos 1.0)

(define (average a b)
    (/ (+ a b) 2.0))

(average 1 3)

(define (sqrt x)
    (fixed-point (lambda (y) (average y (/ x y))) 1.0))

(sqrt 2)

(define (phi)
    (fixed-point (lambda (y) (average y (+ 1 (/ 1 y)))) 1.0))

(phi)

(define (xtox)
    (fixed-point (lambda (x) (average x (/ (log 1000) (log x)))) 2.0))
(xtox)

(define (cont-frac N D k)
    (define (recur n d i)
        (display i)
        (newline)
        (if (> i k)
            0
            (/ (n i)
               (+ (d i) (recur n d (+ i 1))))))

    (recur N D 1))

(define (cont-frac-iter n d k)
    (define acc (/ (n k) (d k)))
    (define i 1)
    (do ((i 1 (1+ i)))
        ((> i k))
        (display acc)
        (newline)
        (set! acc (/ (n (- k i)) (+ (d (- k i)) acc))))
    acc)

;; 1/phi?
(cont-frac (lambda (i) 1.0)
           (lambda (i) 1.0)
                        10)

(cont-frac-iter (lambda (i) 1.0)
                (lambda (i) 1.0)
                             10)

