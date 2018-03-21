; this function counts from 1 to 10 and then calls finalize
; when it reaches 11.  Finalize is a lambda function that 
; multiplies value by 10

(defun testfunc(value finalize)
  (let (if (leq 10 value)
           (finalize value) 
           (testfunc (add value 1) (lambda (c) (mul c 10)))) .(value . 1)))
