(and (oddp 5) (oddp 7) (oddp 9))
(or (oddp 4) (oddp 7) (oddp 8))
(defparameter *is-it-even* nil)
(or (oddp 5) (setf *is-it-even* t))
*is-it-even*
