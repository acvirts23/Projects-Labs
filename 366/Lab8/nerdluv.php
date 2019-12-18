<?php
header("Content-type: application/json");
/* This web service should handle two types of requests:
	1) a GET request with a name parameter 
	2) a POST request with the following parameters:
		- name
		- gender
		- age
		- ptype
		- os
		- minAge
		- maxAge
	You do not need to do validation checking on the values of the parameters.
	For this lab, we'll assume the values are all valid (no weird OS spellings, etc.)
	
	There are no results from the POST request. However, if a failure occurs, your
	page should return an HTTP error code of 400.
	
	The results of the GET request should be a json object named data with the set
	of matches as an array. For example:
	{"data":[{"name":"Dana Scully",
			  "gender":"F",
			  "age":"41",
			  "ptype":"ISTJ",
			  "os":"Mac OS X",
			  "minAge":"36",
			  "maxAge":"54"},
	         {"name":"Jadzia Dax",
			  "gender":"F",
			  "age":"46",
			  "ptype":"ENFJ",
			  "os":"Mac OS X",
			  "minAge":"18",
			  "maxAge":"32"}
			 ]
	}
	
	If no matches are found, return an empty data array (as follows):
	{"data":[]
	}
	If a failure occurs, your page should return an HTTP error code of 400.


/* Your db.txt file should contain two variable initializations:
	$username (probably "admin", your db username)
	$login (the password for your db login) */
include("/var/db.php");

/* You should put logic here to handle the POST request to add a new 
user and the GET request to get matches for a user */

/*

if ($_SERVER["REQUEST_METHOD"] == "GET") {
	try {
		$dbconn = getConnection($username, $login);
		$row = getRow($dbconn, $_GET["name"]); ?>
		//<?= "user: " . $username ?>
		<strong> The resulting row is: <strong> <br/>
		<?php
		print_r($row); 
	} catch (PDOEXception $ex) {
		header("HTTP/1.1 400 Invalid Request");
		print "big problem";
	}
}

if ($_SERVER["REQUEST_METHOD"] == "POST")
{
	addUser();
}
*/


/* This function should take in the $username and $login that were initialized
	in the db.txt file and it should use PDO to connect to the database.
	The database connection should be returned. */
function getConnection($username, $login) {
	try {
		$connection = new PDO("mysql:host=acvirts.millersville.edu:12322; dbname=nerdluv", $username, $login);
		$connection->setAttribute(PDO::ATTR_ERRMODE, PDO:ERRMODE_EXCEPTION);
		}
	catch(PDOException $e) {
		"Connection failed: Please try again";
	}
	return $connection;
}

/* This function takes in a PDO object that should already be connected to 
	the database and a variable $name that contains the user name. $name is the
	user for whom we want to find matches. This function should do a query (using 
	a prepared statement) and get the row that matches the $name as a *numerically
	indexed* array. This array should be returned. */
function getUser($dbconn,$name) {
	$statement = $dbconn->prepare("SELECT * FROM users WHERE name = :name");
	$statement->execute(array(":name" => $name));
	return $statement->fetch(PDO::FETCH_ASSOC);
}

/* Given a PDO object (already connected to DB) and a numerically indexed array of data
	representing the row in the db for a user, return a result set of data that has
	1) the opposite gender from $user, 2) matching os, 3) an age between the minage of $user
	and maxage of $user and where the age of $user is between the minage and maxage of the
    record. (Ignore the personality type for now). Getting these results should be
	done by a prepared statement with parameters. Return the rows in a multi-dimensional 
	*associative* array (unless there are no results) */
function getBasicMatches($dbconn,$user) {
	//name = [0], gender = [1] age = [2] ptype = [3] os = [4] minAge=[5] maxAge=[6]

}

/* Given the string representing the user's personality type and the result set from
	getting the user's basic matches (getBasicMatches), return an array containing only those
	matches that have at least one personality type letter in common with $usertype The $matches
	should be multi-dimensional associative array when passed in, and the return value should
	also be a multi-dimensional associative array (unless there are no results) */
function getMatches($usertype, $matches) {
}

/* Given a PDO object (already connected to DB) and all of the information necessary for
	a new user, this function should add the new user to the database. Return value should be
	true or false */
function addUser($dbconn, $name, $gender, $age, $type, $os, $minage, $maxage) {
}





?>
