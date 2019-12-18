<!--
  Name; Andrew Virts
  Assignment: Lab 7-Nerdluv
  Course: 366
-->

<?php 
  include("top.html");
  ?>
        
        <!-- your HTML output follows -->
        <?php
            $file =file_get_contents("singles.txt");
            $singles = explode("\n", $file);
            $match;

            $userName = $_GET["name"];
            $userInfo = array();
            foreach ($singles as $people) 
            {
                $userInfo = explode(",", $people);
                if($userInfo[0] == $userName)
                {
                    break;
                }
            }

            //Checks the personality of the user and the match to ensure atleast 1 letter in common
           function checkPersonality($matchPersonality, $userPersonality)
            {
              $letterNum = 0;
                  for ($i=0; $i<4; $i++)
                  {
                        if (substr($matchPersonality, $i, 1) == substr($userPersonality, $i, 1))
                        {
                              $letterNum++;
                        }
                  }
                  if ($letterNum > 0)
                  {
                      return true;
                  } 
            }
            
            //Creates the matches
            function createMatches()
            {
                global $singles;
                global $userInfo;
                $matches = $singles;
                $arraySize = sizeof($matches);
                for ($i=0; $i<$arraySize; $i++)
                {
                      $matchInfo = explode(",", $matches[$i]);
                      if ($matchInfo[1] == $userInfo[1])
                      {
                          unset($matches[$i]); //Removes matches if genders aren't opposite
                      } 
                      else if ($matchInfo[4] != $userInfo[4])
                      {
                          unset($matches[$i]); //Removes matches if they don't have the same favorite OS
                      }
                      else if (($matchInfo[2] < $userInfo[5] || $matchInfo[2] > $userInfo[6]) || ($userInfo[2] < $matchInfo[5] || $userInfo[2] > $matchInfo[6]))
                      {
                          unset($matches[$i]); //Removes people that aren't in the desired age range for the user
                      }
                      else if (checkPersonality(str_split($matchInfo[3]), str_split($userInfo[3]))==false)
                      {
                          unset($matches[$i]); //Removes people if the user and the match don't have at least 2 letters in their personality type in common
                      }
                }
                $matches = array_values($matches);
                return $matches;
            }


            //Prints out each match
            function getMatches()
            {
                $matches = createMatches();
                for ($i=0; $i<sizeof($matches); $i++)
                {
                    $match = explode(",", $matches[$i]);
                    printMatches($match);
                }
            }

            //Displays the matches onto the screen
            function printMatches($match)
            {
        ?>
                <div class="match">
                    <p>
                        <img src="http://acvirts.millersville.edu/Lab7/user.jpg" alt="user icon" /> <?=  $match[0]  ?>
                        <ul>
                            <li><strong>gender:</strong> <?=  $match[1]  ?></li>
                            <li><strong>age:</strong> <?=  $match[2]  ?></li>
                            <li><strong>type:</strong> <?=  $match[3]  ?></li>
                            <li><strong>OS:</strong> <?=  $match[4]  ?></li>                        
                        </ul>
                    </p>
                </div>
        <?php
            }
        ?>

        <h1>Matches for <?=$userName?></h1>
        <?php 
            getMatches();
        ?>
        
        <!-- shared page bottom HTML -->
<?php include("bottom.html") ?>
