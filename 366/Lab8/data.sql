create database nerdluv;
use nerdluv;
create table users (
name varchar(40),
gender char(1),
age integer,
ptype char(4),
os varchar(10),
minAge integer,
maxAge integer,
	primary key (name));

insert into users values ('Ada Lovelace','F',96,'ISTJ','Linux',24,99);
insert into users values ('Adele Goldberg','F',65,'ENFJ','Windows',50,70);
insert into users values('Alan Turing','M',41,'ESTP','Mac OS X',31,50);
insert into users values('Anakin Skywalker','M',27,'INTJ','Linux',15,30);
insert into users values('Angry Video Game Nerd','M',29,'ISTJ','Mac OS X',1,99);
insert into users values('Anita Borg','F',54,'ISFP','Windows',41,55);
insert into users values('Barbara Liskov','F',71,'ESFJ','Mac OS X',41,76);
insert into users values('Bill Gates','M',52,'INTJ','Windows',2,99);
insert into users values('Bill Joy','M',54,'ENFP','Linux',50,70);
insert into users values('Bjarne Stroustroup','M',59,'INFJ','Windows',40,62);
insert into users values('Buffy Summers','F',27,'INTP','Windows',18,49);
insert into users values('Charles Babbage','M',79,'ESFP','Linux',30,82);
insert into users values('Dana Scully','F',41,'ISTJ','Mac OS X',36,54);
insert into users values('Deanna Troi','F',53,'ENFJ','Mac OS X',32,48);
insert into users values('Donald Knuth','M',70,'INTJ','Linux',12,17);
insert into users values('Edsger Dijkstra','M',72,'ISTP','Linux',16,58);
insert into users values('Ellen Ripley','F',35,'ESFJ','Linux',20,40);
insert into users values('Frances Allen','F',78,'ESTP','Linux',67,78);
insert into users values('Gordon Moore','M',81,'ENFP','Windows',60,99);
insert into users values('Grace Hopper','F',87,'ISFP','Windows',47,80);
insert into users values('Jadzia Dax','F',46,'ENFJ','Mac OS X',18,32);
insert into users values('James Gosling','M',55,'ESFJ','Linux',18,40);
insert into users values('Jeannette Wing','F',38,'INTP','Mac OS X',45,60);
insert into users values('Kathryn Janeway','F',49,'ESTJ','Windows',30,55);
insert into users values('Lara Croft','F',23,'ENTP','Linux',18,30);
insert into users values('Leeloo','F',19,'ISTJ','Linux',1,99);
insert into users values('Leia Organa','F',53,'ISFJ','Windows',20,60);
insert into users values('Lenore Blum','F',70,'INTP','Mac OS X',66,99);
insert into users values('Marissa Mayer','F',35,'ENTP','Linux',20,40);
insert into users values('Mary Lou Jepsen','F',45,'ISTJ','Windows',10,80);
insert into users values('Ms Frizzle','F',39,'ENTP','Mac OS X',19,49);
insert into users values('Natalie Portman','F',26,'INFJ','Mac OS X',20,39);
insert into users values('Niklaus Wirth','M',76,'ENFJ','Windows',50,77);
insert into users values('Nostalgia Critic','M',28,'ENTJ','Linux',12,79);
insert into users values('Nyota Uhura','F',77,'ENFP','Mac OS X',70,99);
insert into users values('Oldspice Guy','M',36,'ENTJ','Windows',1,99);
insert into users values('Rasmus Lerdorf','M',41,'ENTP','Linux',15,35);
insert into users values('Richard Stallman','M',57,'ISFJ','Linux',46,56);
insert into users values('River Tam','F',26,'ENTJ','Linux',18,25);
insert into users values('Roberta Williams','F',57,'ENFP','Windows',54,67);
insert into users values('Rosie O Donnell','F',46,'ENFJ','Windows',30,50);
insert into users values('Sarah Connor','F',53,'ISFP','Windows',49,67);
insert into users values('Seven of Nine','F',40,'ISTJ','Windows',12,50);
insert into users values('Stewie Griffin','M',1,'INTP','Mac OS X',1,59);
insert into users values('Stuart Reges','M',48,'INFP','Mac OS X',18,35);
insert into users values('Tpol','F',35,'ISTJ','Windows',30,39);
insert into users values('Trinity','F',42,'ESFP','Linux',35,55);
insert into users values('Tyler Durden','M',46,'ENFP','Mac OS X',20,39);
insert into users values('Valentina Tereshkova','F',71,'ENTJ','Mac OS X',55,65);
insert into users values('Vint Cerf','M',67,'ISFP','Mac OS X',28,55);
insert into users values('Yukihiro Matsumoto','M',45,'ENTP','Mac OS X',10,25);
insert into users values('Zelda','F',59,'ESTP','Windows',40,62);
