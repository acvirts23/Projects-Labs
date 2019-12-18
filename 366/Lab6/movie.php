<<!DOCTYPE html>
<html lang="en">
    <head>
        <title>Rancid Tomatoes</title>
        <link rel="shortcut icon" type="image/png" href="http://cs.millersville.edu/~sschwartz/366/HTML_CSS_Lab/Images/rotten.gif"/>
        <meta charset="utf-8" />
        <link href="movie.css" type="text/css" rel="stylesheet" />
        <?php $movie = $_GET["film"]; 
        $info = file("$movie/info.txt");
        $movieOverview = "$movie/overview.png";
        ?>

     </head>



    <body>
        <div id ="banner">
            <img src="http://cs.millersville.edu/~sschwartz/366/HTML_CSS_Lab/Images/banner.png" alt="Rancid Tomatoes" />
        </div>

        <h1 id ="header"> <?= $info[0] . "(" . $info[1] . ")" ?> </h1>

    <div id="content"> <!--Start content-->

        <div id="right"> <!--Start right-->

                <img src="<?= $movieOverview ?>" alt="general overview" />
        
            <dl>
                <?php
                foreach (file("$movie/overview.txt") as $overview)
                {
                    $explode = explode(":", $overview);
                ?>
                    <dt> <?= $explode[0]?> </dt>
                    <dd> <?= $explode[1]?> </dd>
                <?php
                }
                ?>
            </dl>

        </div> <!--End right-->

        <div id ="left">    <!--Start left-->

            <div id="left-top">        <!--Start left-top div-->
                <?php
                    if ($info[2] >= 60)
                    {
                        $fresh="http://cs.millersville.edu/~sschwartz/366/HTML_CSS_Lab/Images/freshbig.png";
                    }
                    else
                    {
                        $fresh="http://cs.millersville.edu/~sschwartz/366/HTML_CSS_Lab/Images/rottenbig.png";
                    }
                ?>
                <span class = "rating"> <?= $info[2] ?>%</span>
                <img src="<?=$fresh?>" alt = "fresh"/>

            </div>        <!--End left-top div-->

                <?php
                    $reviews = glob("$movie/review*.txt");
                    $reviewCount = count($reviews);
                    $half=ceil($reviewCount/2);
                    for ($i = 0; $i<$reviewCount; $i++){
                        if($i==$half || $i==0) { ?>
                            <div class="column"> <!--Start column 2 div-->
                        <?php } ?>
                        <?php
                            $review=file($reviews[$i], FILE_IGNORE_NEW_LINES);
                            $rating = trim(strtolower($review[1]))
                        ?> 

                <div class="review"> <!--review-->
                    <p class="reviewDiv"> <!--Start reviewdiv -->
                            <img src= "<?="http://cs.millersville.edu/~sschwartz/366/HTML_CSS_Lab/Images/" . $rating . ".gif"?>" alt="Fresh" />
                            <q><?=$review[0]?></q>
                    </p>
                    <p class="reviewer">
                            <img src="http://cs.millersville.edu/~sschwartz/366/HTML_CSS_Lab/Images/critic.gif" alt="Critic" />
                        <?= $review[2] ?> <br />
                        <?= $review[3] ?>
                    </p>
                </div> <!--End review div-->
                        <?php
                            if($i == ($half-1) || $i==$reviewCount) { ?>
                                    </div> <!--End column 2 div-->
                        <?php } ?>
                    <?php
                        }
                        ?>

            </div>    <!--End column div-->


        </div> <!--End left-->

           <div id="bottom">    <!--Start bottom div-->
            <?="(1-$reviewCount)"?> of <?= $reviewCount ?>
            </div>                <!--End bottom div-->


    </div> <!--End content-->

        <div id ="validator"> <!--Start validators-->
            <a href="http://validator.w3.org/check/referer"><img class="val" src="http://cs.millersville.edu/~sschwartz/366/Images/w3c-html.png" alt="Valid HTML5" /></a> <br />
            <a href="http://jigsaw.w3.org/css-validator/check/referer"><img class= "val" src="http://cs.millersville.edu/~sschwartz/366/Images/w3c-css.png" alt="Valid CSS" /></a>
        </div> <!--End validators-->
    </body>
</html>