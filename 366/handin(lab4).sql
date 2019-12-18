/* PROBLEM 1 BEGIN */
SELECT empno, empfname FROM emp
WHERE bossno IS NULL;
/* PROBLEM 1 END */

/* PROBLEM 2 BEGIN */
SELECT wrk.empno, wrk.empfname, boss.empno AS mgrno, boss.empfname AS mgrfname
FROM emp wrk JOIN emp boss
ON wrk.bossno = boss.empno
ORDER BY wrk.empfname ASC;
/* PROBLEM 2 END */

/* PROBLEM 3 BEGIN */
SELECT deptname FROM emp
WHERE empno NOT IN(SELECT empno FROM dept)
GROUP BY deptname HAVING AVG(empsalary) > 25000;
/* PROBLEM 3 END */

/* PROBLEM 4 BEGIN */
SELECT empno, empfname FROM emp
WHERE bossno IN (SELECT bossno FROM emp WHERE empfname ='Andrew');
/* PROBLEM 4 END */

/* PROBLEM 5 BEGIN */
SELECT empno, empfname, empsalary FROM emp
WHERE empsalary =
(SELECT MAX(empsalary) FROM emp WHERE bossno IN(SELECT bossno FROM emp WHERE empfname ='Andrew'));
/* PROBLEM 5 END */

/* PROBLEM 6 BEGIN */
SELECT empno, empfname FROM emp WHERE empno IN (SELECT bossno from emp)
AND empno NOT IN (SELECT empno FROM dept);
/* PROBLEM 6 END */

/* PROBLEM 7 BEGIN */
SELECT prodid, proddesc, prodprice FROM product
WHERE prodprice = (SELECT MAX(prodprice) FROM product WHERE prodid IN
(SELECT subprodid FROM product, assembly WHERE proddesc ='Animal Photography Kit' AND product.prodid = assembly.prodid));
/* PROBLEM 7 END */
