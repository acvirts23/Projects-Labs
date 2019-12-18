;Returns T if the arguments is the goal state, otherwise retuns NIL
(defun goal-state(lst)
	(cond
		((equal lst '(1 2 3 8 e 4 7 6 5)))
	)
)

;Takes a list as input
;Returns the direction of the move in the list
(defun get-direction(lst)
	(cond
		((null lst) nil)
		(T (car lst))
	)
)

;Takes a single list as input 
;Returns the state of the move
(defun get-state(lst)
	(cond
		((null lst) nil)
		(T (car (cdr lst)))
	)
)

;Takes two lists as arguments
;Returns T if the two lists(states) are the same, otherwise returns NIL
(defun same-state(lst1 lst2)
	(cond
		((equal (cdr lst1) (cdr lst2)))
	)
)


;Helper function to reverse a list
;Used to make path function correctly
(defun rev (lst)
	(cond
		((null lst) nil)
		(T(append (rev(cdr lst)) (list (car lst))))))


;Returns a list of the moves taken in the input
(defun path (lst)
	(cond
		((null lst) nil)
		((cdr(rev(mapcar #'get-direction lst)))) 	
	)
)



;Checks to see if the states are the same using the member function, if they are it skips over them
;Otherwise it cons's the list to the first list
;Returns a list with all redundant lists from the second list removed
(defun remove-redundant (lst1 lst2)
	(cond
		((null lst1) nil)
		((member (car lst1) lst2 :test #'same-state)(remove-redundant (cdr lst1) lst2))
		((not (member (car lst1) lst2 :test #'same-state)) (cons (car lst1) (remove-redundant (cdr lst1) lst2)))
	)
)




