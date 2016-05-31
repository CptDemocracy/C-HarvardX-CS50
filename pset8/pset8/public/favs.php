<?php

    // configuration
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] === "POST")
    {
        if (isset($_POST["remove_btn"])) 
        {
            $result = CS50::query("DELETE FROM favorites WHERE place_name = ? AND admin_name1 = ? AND country_code = ?;",
                $_POST["place_name"], $_POST["admin_name1"], $_POST["country_code"]);
            render("../views/favs_form.php");
        }
        else 
        {
            if (isset($_POST["news_btn"])) 
            {
                $params = [ "geo" => 
                                $_POST["place_name"]
                                    .",".$_POST["admin_name1"]
                                    .",".$_POST["country_code"] ];
                $_GET["geo"] = json_encode($params);
                $articles = lookup($_GET["geo"]);
                
                render("news_form.php", [ "articles" => $articles ]);
                
            }
            else if (isset($_POST["search_btn"])) 
            {
                $params = [ "lat" => $_POST["lat"],
                            "lng" => $_POST["lng"] ];
                            
                header("Location: index.php?"."lat=".$params["lat"]."&lng=".$params["lng"]);
            }
        }
    }
    else if ($_SERVER["REQUEST_METHOD"] === "GET")
    {
        render("../views/favs_form.php");
    }
    
?>