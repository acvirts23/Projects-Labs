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
                $matches = $singles;
                $arraySize = sizeof($matches);
                for ($i=0; $i<$arraySize; $i++)
                {
                      $matchInfo = explode(",", $matches[$i]);
                      if ($matchInfo[1] != $userInfo[1]) //Removes matches if genders aren't opposite
                      {
                         if ($matchInfo[4] != $userInfo[4]) //Removes matches if they don't have the same favorite OS
                          {
                            if (($matchInfo[2] < $userInfo[5] || $matchInfo[2] > $userInfo[6]) || ($userInfo[2] < $matchInfo[5] || $userInfo[2] > $matchInfo[6])) //Removes people that aren't in the desired age range for the user
                              {
                                if (($matchInfo[2] < $userInfo[5] || $matchInfo[2] > $userInfo[6]) || ($userInfo[2] < $matchInfo[5] || $userInfo[2] > $matchInfo[6]))
                                  {
                                    //Removes people that aren't in the desired age range for the user
                                    if (checkPersonality(str_split($matchInfo[3]), str_split($userInfo[3]))==true)
                                      {
                                        //Removes people if the user and the match don't have at least 2 letters in their personality type in common
                                        $matches = array_values($matches);
                                        return $matches;

                                      }
                                  }
                              }
                          }
                      } 
                    
                      
                      
                }
                
            }


            //Displays the matches onto the screen
        
              <h1>Matches for <?=$userName?></h1>
              for ($i = 0; $i<$matches; $i++)
              {
            ?>

                <div class="match">
                    <p>
                        <img src="http://acvirts.millersville.edu/Lab7/user.jpg" alt="user icon" /> <?=  $matches[0]  ?>
                        <ul>
                            <li><strong>gender:</strong> <?=  $matches[1]  ?></li>
                            <li><strong>age:</strong> <?=  $matches[2]  ?></li>
                            <li><strong>type:</strong> <?=  $matches[3]  ?></li>
                            <li><strong>OS:</strong> <?=  $matches[4]  ?></li>                        
                        </ul>
                    </p>
                </div>
              
        <?php
            }
        ?>
        
        <!-- shared page bottom HTML -->
<?php include("bottom.html") ?>
