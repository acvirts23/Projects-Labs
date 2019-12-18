<!--
  Name; Andrew Virts
  Assignment: Lab 7-Nerdluv
  Course: 366
-->

<?php include("top.html") ?>
		<!-- your HTML output follows -->
	<form action="matches-submit.php" method="GET">
		<fieldset>
			<legend>Returning User:</legend>
			<ul>
				<li>
					<strong>Name:</strong>
					<input type="text" size="16" name="name"/>
				</li>
			</ul>
			<input type ="submit" value="View My Matches">
		</fieldset>
		<!-- shared page bottom HTML -->
<?php include("bottom.html") ?>