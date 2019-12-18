<!--
  Name; Andrew Virts
  Assignment: Lab 7-Nerdluv
  Course: 366
-->

<?php include("top.html") ?>
		<!-- your HTML output follows -->
	<form action="signup-submit.php" method="post">
		<fieldset>
			<legend>New User Signup:</legend>
			<ul>
				<li>
					<strong>Name:</strong>
					<input type ="text" size="16" name="name" />
				</li>

				<li>
					<strong>Gender:</strong>
					<input type ="radio" name ="gender" value="M"/> Male
					<input type ="radio" name ="gender" value="F" checked = "checked"/> Female
				</li>

				<li>
					<strong>Age:</strong>
					<input type ="text" size="6" maxlength="2" name="age"> 
				</li>

				<li>
					<strong>Personality Type:</strong>
					<input type="text" size="6" maxlength="4" name="ptype"> <a href="http://www.humanmetrics.com/cgi-win/JTypes2.asp"> (Don't know your type?)</a>
				</li>

				<li>
					<strong>Favorite OS</strong>
					<select name = "os">
						<option selected="selected">Windows</option>
						<option>Mac OS X</option>
						<option>Linux</option>
					</select>
				</li>

				<li>
					<strong>Seeking Age</strong>
					<input type ="text" size="6" maxlength="2" name="minAge" placeholder="Min"> to <input type ="text" size="6" maxlength="2" name="maxAge" placeholder="Max">
				</li>	
			</ul>
			<input type="submit" value="Sign Up">
		</fieldset>
	</form>
		
		<!-- shared page bottom HTML -->
<?php include("bottom.html") ?>