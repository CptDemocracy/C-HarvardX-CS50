<?php

    if ($_SERVER["REQUEST_METHOD"] === "POST") 
    {

        require("../includes/config.php");
    
                                        
        $result = CS50::query("SELECT * FROM favorites WHERE user_id = ?"
                                    ."AND place_name = ?"
                                    ."AND admin_name1 = ?"
                                    ."AND country_code = ?;", 
                                $_SESSION["id"], $_POST["place_name"], $_POST["admin_name1"], $_POST["country_code"]);
            
        if (count($result) === 0) 
        {
            $result = CS50::query("INSERT INTO favorites (user_id, place_name, admin_name1, country_code, latitude, longitude) "
                                    ."VALUES(?, ?, ?, ?, ?, ?);",   $_SESSION["id"],        $_POST["place_name"], 
                                                                    $_POST["admin_name1"],  $_POST["country_code"],
                                                                    $_POST["lat"],          $_POST["lng"]);
                            
            success($_POST["place_name"]." ".$_POST["admin_name1"]." ".$_POST["country_code"]
                                        ." "." has been added to your My Places collection.");
        }
        else 
        {
            apologize($_POST["place_name"]." ".$_POST["admin_name1"]." ".$_POST["country_code"]
                                        ." "." is already in your My Places collection.");
        }
    
    }
?>