(define tree '( "R" 100 999 (
                             ("R" 100 199 (
                                           ("L" 170 172 173 192)
                                           ))       
                             ("R" 200 299 (
                                           ("L" 220 240 260 280))))))

(define (search tree value)
  (Node tree value))

(define (List list value)
  (if (not (null? list))
      (if (list? (car list))
          (begin
            (List (car list) value)
            (List (cdr list) value))
          (Node list value))))

(define (Node node value)
  (if (equal? (car node) "R")
      (if (and (<= (list-ref root 1) value) (>= (list-ref root 2) value))
          (List (car (cdr (cdr (cdr node)))) value))
      (iterate node value)))

(define (iterate node value)
  (let ((list (cdr node)))
               (if (not (null? list))
                   (if (= (car list) value)
                       (begin 
                         (display node)
                         (display " Find value. \n"))
                       (let ((node1 (cdr list)))
                         (loop node1))))))



  



  

