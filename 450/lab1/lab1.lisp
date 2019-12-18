(defun my-rotate (lst)
	(cond
		((null lst) nil)
		(T (append)(cdr lst) (list(car lst)))))