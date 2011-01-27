(defun listlen (list)
    (if list 
        (1+ (listlen (cdr list)))
        0))

(princ (listlen '(list with four symbols)))
