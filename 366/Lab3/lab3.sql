/* PROBLEM 1 BEGIN */
create table label (
    lbltitle varchar(20),
    lblstreet varchar(30),
    lblcity  varchar(20),
    lblstate char(2),
    lblpostcode smallint,
    lblnation varchar(5),
    primary key (lbltitle));

create table cd (
  cdid    smallint,
    cdlblid  varchar(10),
    cdtitle  varchar(20),
    cdyear  smallint,
    lbltitle varchar(20),
    primary key (cdid),
    constraint fk_has_label foreign key(lbltitle)
 references label(lbltitle));

create table person (
psnid  smallint,
    psnfname varchar(10),
    psnlname varchar(20),
    primary key (psnid));

create table composition (
compid  smallint,
    comptitle varchar(30),
    compyear smallint,
    primary key (compid));

create table person_cd (
psncdorder smallint,
    psnid  smallint,
    cdid  smallint,
    primary key (psnid, cdid),
    constraint fk_has_psnid foreign key (psnid) references person (psnid),
    constraint fk_has_cdid foreign key (cdid) references cd (cdid));

create table person_composition (
psncomprole  varchar(10),
    psncomporder smallint,
    psnid   smallint,
    compid   smallint,
    primary key (psncomprole, psnid, compid),
    constraint fk_has_personid foreign key (psnid) references person (psnid),
    constraint fk_has_compid foreign key (compid) references composition (compid));

create table recording (
rcdid  smallint,
    rcdlength decimal(4,2),
    rcddate  date,
    compid  smallint,
    primary key (rcdid, compid),
    constraint fk_has_composition foreign key (compid) references composition (compid));

create table track (
cdid  smallint,
trknum  smallint,
    rcdid  smallint,
    compid  smallint,
    primary key (trknum, rcdid, cdid),
    constraint fk_has_recording foreign key (rcdid, compid) references recording (rcdid, compid),
    constraint fk_has_cd foreign key (cdid) references cd (cdid));

create table person_recording (
psnrcdrole varchar(10),
psnid  smallint,
rcdid  smallint,
    compid  smallint,
    primary key (psnrcdrole, psnid, rcdid, compid),
    constraint fk_has_person foreign key (psnid) references person (psnid),
    constraint fk_has_recordingid foreign key (rcdid, compid) references recording (rcdid, compid));
/* PROBLEM 1 END */

/* PROBLEM 2 BEGIN */
SELECT trknum, comptitle FROM track
JOIN composition on composition.compid = track.compid
JOIN cd on cd.cdid = track.cdid
WHERE cd.cdtitle = 'Giant Steps';
/* PROBLEM 2 END */

/* PROBLEM 3 BEGIN */
SELECT psnfname, psnlname, psnrcdrole FROM person JOIN person_recording
ON person.psnid = person_recording.psnid
JOIN recording on recording.rcdid = person_recording.rcdid
WHERE rcddate = '1959-05-04' AND recording.rcdid = (select cdid from cd where cdtitle = 'Giant Steps');
/* PROBLEM 3 END */

/* PROBLEM 4 BEGIN */
SELECT psnfname, psnlname FROM person JOIN person_composition
ON person.psnid = person_composition.psnid
JOIN person_recording on person.psnid = person_recording.psnid
WHERE person_recording.psnrcdrole = 'tenor sax' AND person_composition.psncomprole = 'music' group by person.psnid;
/* PROBLEM 4 END */

/* PROBLEM 5 BEGIN */
SELECT comptitle, trknum, cdtitle FROM composition
JOIN track ON composition.compid = track.compid
JOIN cd ON cd.cdid = track.cdid
WHERE(track.compid, track.cdid) IN (SELECT compid, cdid FROM track GROUP BY compid, cdid HAVING COUNT(*) > 1)
ORDER BY composition.comptitle, track.trknum;
/* PROBLEM 5 END */

/* PROBLEM 6 BEGIN */
SELECT rcdid, rcddate FROM recording
WHERE NOT EXISTS (SELECT * FROM cd WHERE NOT EXISTS(SELECT * FROM track WHERE track.cdid = cd.cdid AND recording.rcdid = track.rcdid));
/* PROBLEM 6 END */

/* PROBLEM 7 BEGIN */
SELECT track.rcdid, rcddate from recording 
JOIN track ON track.rcdid = recording.rcdid
JOIN cd on track.cdid = cd.cdid
GROUP BY recording.rcdid, rcddate
HAVING COUNT(DISTINCT cd.cdid) = (SELECT COUNT(DISTINCT cdid) from cd);
/* PROBLEM 7 END */