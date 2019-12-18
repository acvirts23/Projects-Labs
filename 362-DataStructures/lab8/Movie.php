<html>
    <head>
        <title>Rancid Tomatoes</title>

        <meta charset="utf-8" />
        <link href="movie.css" type="text/css" rel="stylesheet" />
        <link href="http://cs.millersville.edu/~sschwartz/366/HTML_CSS_Lab/Images/rotten.gif" type ="image/gif" rel="favicon" />
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

                <img src="<?= $movieOverview ?>"/>
        
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

                <dd>

                </dd>
            </dl>
        </div> <!--End right-->

    <div id ="left">    <!--Start left-->

        <div id="left-top">        <!--Start left-top div-->
            <?php
                if ($info[2] >= 60)
                {
                    $fresh = "http://cs.millersville.edu/~sschwartz/366/HTML_CSS_Lab/Images/freshbig.png";
                }
                else
                {
                    $fresh = "http://cs.millersville.edu/~sschwartz/366/HTML_CSS_Lab/Images/rottenbig.png";
                }
            ?>
            <span class = "rating"> <?= $info[2] ?>%</span>
            <img src=" <?=$fresh?> "/>

        </div>        <!--End left-top div-->

        <div class="column"> <!--Start column1-->
            <?php
                $reviews = glob("$movie/review*.txt");
                $a = count($reviews);
                $half=((int)($a/2)+ $a % 2);
                for ($i = 0; $i<$a; $i++){
                    if($i==$half or $i==0) { ?>
                        <div class=column>
                    <?php } ?>
                    <?php
                        $review=file($reviews[$i], FILE_IGNORE_NEW_LINES);
                    ?>
                    <p>
                    <?php
                    if($review[1] == "FRESH")
                        { ?>
                            <img src="http://cs.millersville.edu/~sschwartz/366/HTML_CSS_Lab/Images/fresh.gif"
                            alt="Fresh" />
                          <?php
                        }
                        else{ ?>
                            <img src="http://cs.millersville.edu/~sschwartz/366/HTML_CSS_Lab/Images/rotten.gif"
                            alt="Rotten" />
                              <?php
                    }
                    ?>
                    <q><?= $review[0] ?></q>
                    </p>
                    <p>
                    <img src="http://cs.millersville.edu/~sschwartz/366/HTML_CSS_Lab/Images/critic.gif"
                    alt="Critic" />
                    <?= "$review[2]" ?> <br />
                    <?= "$review[3]" ?>
                    </p>
                    <?php
                        if($i == ($half-1) || $i==$a) { ?>
                                </div>
                    <?php } ?>
                <?php
                    }
                    ?>

        </div>    <!--End column1 div--->
                                                  

    </div> <!--End left-->

        <div id="bottom">    <!--Start bottom div-->
            <p>(1-10) of 88</p>
        </div>                <!--End bottom div-->

    </div> <!--End content-->

        <div id ="validator"> <!--Start validators-->
            <a href="http://validator.w3.org/check/referer"><img class="val" src="http://cs.millersville.edu/~sschwartz/366/Images/w3c-html.png" alt="Valid HTML5" /></a> <br />
            <a href="http://jigsaw.w3.org/css-validator/check/referer"><img class= "val" src="http://cs.millersville.edu/~sschwartz/366/Images/w3c-css.png" alt="Valid CSS" /></a>
        </div> <!--End validators-->
    </body>
</html>
