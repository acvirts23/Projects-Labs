/* PROBLEM 1 BEGIN */

CREATE TABLE label (
lbltitle VARCHAR(20),
lblstreet VARCHAR(20),
lblcity VARCHAR(20),
lblstate VARCHAR(20),
lblpostcode VARCHAR(20),
lblnation VARCHAR(10),
PRIMARY KEY(lbltitle));

CREATE TABLE cd (
cdid INTEGER(15),
cdlblid VARCHAR(40),
cdtitle VARCHAR(40),
cdyear VARCHAR(20),
lbltitle VARCHAR(40),
PRIMARY KEY(cdid),
CONSTRAINT cd_has_label FOREIGN KEY (lbltitle) REFERENCES label(lbltitle));

CREATE TABLE track (
trkid INTEGER (15),
trknum INTEGER (15),
trktitle VARCHAR (40),
trklength DECIMAL (10,2),
cdid INTEGER (10),
PRIMARY KEY (trkid),
CONSTRAINT track_has_cd FOREIGN KEY (cdid) REFERENCES cd(cdid));


/* PROBLEM 1 END */

/* PROBLEM 2 BEGIN */
select trktitle, cdtitle, trklength from track, cd 
where track.cdid = cd.cdid ORDER BY cdtitle, trklength;
/* PROBLEM 2 END */

/* PROBLEM 3 BEGIN */
select trktitle, trklength from track where cdid IN
(select cdid from cd where cdtitle = 'Swing');
/* PROBLEM 3 END */

/* PROBLEM 4 BEGIN */
select cdtitle, trktitle, trklength from track, cd 
where track.cdid = cd.cdid
AND  trklength = (select max(trklength) from track where track.cdid = cd.cdid);
/* PROBLEM 4 END */

/* PROBLEM 5 BEGIN */
select cdtitle, count(*) as trkcount, SUM(trklength) AS cdlength 
from track, cd where track.cdid = cd.cdid
group by cd.cdid order by trkcount;
/* PROBLEM 5 END */

/* PROBLEM 6 BEGIN */
select label.lbltitle, lblnation, cdtitle, sum(trklength) as cdlength
FROM cd, label, track WHERE cd.cdid = track.cdid
AND cd.lbltitle = label.lbltitle GROUP BY cd.cdid HAVING cdlength > 40;
/* PROBLEM 6 END */

/* PROBLEM 7 BEGIN */
SELECT cdtitle, trktitle, trklength from cd, track
WHERE cd.cdid = track.cdid ORDER BY trklength LIMIT 3;
/* PROBLEM 7 END */

/* PROBLEM 8 BEGIN */
CREATE VIEW CDView AS SELECT cd.cdid, cdlblid, cdtitle, cdyear, SUM(trklength)
AS cdlength FROM cd, track WHERE cd.cdid = track.cdid GROUP BY cd.cdid;
/* PROBLEM 8 END */

/* PROBLEM 9 BEGIN */
SELECT trktitle, trklength, cdtitle FROM track, cd WHERE cd.cdid = track.cdid AND trktitle REGEXP '^C'; 
/* PROBLEM 9 END */
