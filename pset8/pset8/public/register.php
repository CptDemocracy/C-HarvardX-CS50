<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // borrowed from login.php
        
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        else if (empty($_POST["email"]))
        {
            apologize("You must provide your email.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Your passwords do not match.");
        }
        
        $isInsertSuccessful = CS50::query("INSERT IGNORE INTO users (username, email, hash) VALUES(?, ?, ?)", 
                                    htmlspecialchars($_POST["username"]), 
                                    htmlspecialchars($_POST["email"]),
                                    password_hash($_POST["password"], PASSWORD_DEFAULT));
        if ($isInsertSuccessful == false) 
        {
            apologize("Uh-oh. Looks like this username has already been registered!");
        }
        
        $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
        $id = $rows[0]["id"];
        
        // remember that user's now logged in by storing user's ID in session
        $_SESSION["id"] = $id;
        
        redirect("/index.php");
    }

?>