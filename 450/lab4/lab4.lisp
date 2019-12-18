(defun goal-state (state)
 (equal state '(1 2 3 8 e 4 7 6 5)))

(defun get-state (move)
 (first (rest move)))

(defun get-direction (move)
 (first move))

(defun same-state (move1 move2)
 (equal (get-state move1) (get-state move2)))

(defun path (pathlist)
 (rest (reverse (mapcar 'get-direction pathlist))))

(defun remove-redundant (list1 list2)
 (cond 
   ((null list1) nil)
   ((member (first list1) list2 :test #'same-state)
      (remove-redundant (rest list1) list2))
   (t (cons (first list1) (remove-redundant (rest list1) list2)))))

; Gets position of e in a board configuration
(defun getepos (state)
  (position 'e state))

; Swaps e and whatever value is at position n in state
(defun swap-e-with-n (state n)
  (let ((val (nth n state)))
    (substitute 'e 'x (substitute val 'e (substitute 'x val state)))))

; If moving down is legal from state, this function returns the resulting
; move in a list.  If moving down is not legal, an empty list is returned.
(defun move-down (state)
  (let ((epos (getepos state)))
       (if (> epos 5) () (list (list 'D (swap-e-with-n state (+ epos 3)))))))

; If moving up is legal from state, this function returns the resulting
; move in a list.  If moving up is not legal, an empty list is returned.
(defun move-up (state)
  (let ((epos (getepos state)))
       (if (< epos 3) () (list (list 'U (swap-e-with-n state (- epos 3)))))))

; If moving left is legal from state, this function returns the resulting
; move in a list.  If moving left is not legal, an empty list is returned.
(defun move-left (state)
  (let ((epos (getepos state)))
       (if (eq (mod epos 3) 0) 
           () 
           (list (list 'L (swap-e-with-n state (- epos 1)))))))

; If moving right is legal from state, this function returns the resulting
; move in a list.  If moving right is not legal, an empty list is returned.
(defun move-right (state)
  (let ((epos (getepos state)))
       (if (eq (mod epos 3) 2) 
           () 
           (list (list 'R (swap-e-with-n state (+ epos 1)))))))

 
; This is the main function (the only one that you need to call
; from your code).  It returns a list of the legal moves from the
; given state 
(defun moves (state)
  (append (move-down state)
          (move-up state)
          (move-left state)
          (move-right state)))


;Takes a single list(the initial state) as input
;Returns an open list
;An open list is a list of paths, paths are a list of moves, 
;and moves are lists containing a direction and a state

(defun make-open-init(lst)
	(list(list(cons nil (list lst))))
)

;Takes a single argument, that is a path
;Returns a list of all possible extensions to this path
(defun extend-path(l)
	(extend-path-helper (remove-redundant (moves (get-state (car l))) l) l)
)

;Helper function for extend-path
(defun extend-path-helper (l1 l2)
	(cond
		((null l1) '() )
		(T(cons (cons (car l1) l2)(extend-path-helper (cdr l1) l2)))
	)
)

(defun search-bfs(lst)
	(cond
		((null lst) 
			nil)
		((goal-state (get-state (car (car lst))))
			(path (car lst)))
		(t 
			(search-bfs (append (cdr lst) (extend-path (car lst)))))
	)
)	

(defun search-dfs-fd(lst depth)
	(cond
		((null lst) 
			nil)
		((goal-state (get-state (car (car lst))))
			(path (car lst)))
		((> (length(car lst)) depth)
			(search-dfs-fd (cdr lst) depth))
		(t 
			(search-dfs-fd (append (extend-path (car lst)) (cdr lst)) depth))
	)
)


(defun search-id (lst &optional (depth 1))
	(cond
		((search-dfs-fd lst depth)
			(search-dfs-fd lst depth))
		(t
			(search-id lst (+ depth 1)))
	)
)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
									;Start of lab 4;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


(defun out-of-place(s &optional(goal '(1 2 3 8 e 4 7 6 5)) (count 0))
	(cond 
		((null s) count)
		((goal-state s) 0)
		((equal (car s) (car '(e))) (out-of-place(cdr s)(cdr goal)(+ count 0)))
		((equal (car s) (car goal)) (out-of-place (cdr s)(cdr goal) (+ count 0)))
		(t (out-of-place(cdr s)(cdr goal)(+ count 1)))
	)
)

(defun out-of-place-f(p)
	(+ (out-of-place(get-state (car p))) (-(length p) 1))
)

;Helper function for manhattan
;Modding returns the x coordinate index of the value
;Subtracting returns the y coordinate index of the value 
(defun manhattan-helper(index1 index2)
	(+( abs(- (mod index1 3) (mod index2 3))) (abs(- (floor index1 3) (floor index2 3))))
)

;
(defun manhattan (s &optional (count 0) (index 0))
	(cond
		((null s) count)
		((equal (car s) 1) ((manhattan (cdr s)(manhattan-helper(+ index 1) 0))))
		((equal (car s) 2) ((manhattan(cdr s)(+(manhattan-helper(+ index 1) 1) count))))
		((equal (car s) 3) ((manhattan(cdr s)(+(manhattan-helper(+ index 1) 2) count))))
		((equal (car s) 4) ((manhattan(cdr s)(+(manhattan-helper(+ index 1) 3) count))))
		((equal (car s) 5) ((manhattan(cdr s)(+(manhattan-helper(+ index 1) 4) count))))
		((equal (car s) "e") ((manhattan(cdr s)(+ count 0))))
		((equal (car s) 6) ((manhattan(cdr s)(+(manhattan-helper(+ index 1) 5) count))))
		((equal (car s) 7) ((manhattan(cdr s)(+(manhattan-helper(+ index 1) 6) count))))
		((equal (car s) 8) ((manhattan(cdr s)(+(manhattan-helper(+ index 1) 7) count))))
		((equal (car s) 9) ((manhattan(cdr s)(+(manhattan-helper(+ index 1) 8) count))))
	)
)












