<?php
    /*
    
    index.html
    
    Computer Science 50
    Problem Set 8
    
    A mashup of Google Maps and Google News.
    
    */

    require("../includes/config.php");
    
    render("../views/home.php", [ "ENABLE_GOOGLE_MAPS" => true ] );
?>