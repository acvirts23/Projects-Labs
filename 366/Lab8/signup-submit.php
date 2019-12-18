<!--
  Name; Andrew Virts
  Assignment: Lab 7-Nerdluv
  Course: 366
-->

<?php include("top.html");
		$name = trim($_POST["name"]);
		$singles = "singles.txt";
		
		function writeInfo($singles) {
			foreach ($_POST as $key => $value)
			{
				if ($key == 'maxAge')
				{
					file_put_contents($singles, $value, FILE_APPEND);
				}
				else
				{
					file_put_contents($singles, $value.",", FILE_APPEND);
				}
			}	
			file_put_contents($singles, "".PHP_EOL, FILE_APPEND);
		}	
	?>

<?= writeInfo($singles) ?>

			<div>
				<h1>Thank you!</h1>
				<p>
					Welcome to NerdLuv, <?= $name ?>!<br /> <br />
					Now <a href="matches.php">log in to see your matches!</a>
				</p>
			</div>	
			<!-- shared page bottom HTML -->
<?php include("bottom.html") ?>