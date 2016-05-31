<?php

    // configuration
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] === "GET")
    {
        render("change_password_form.php", [ "title" => "Reset password" ]);
    }
    else if ($_SERVER["REQUEST_METHOD"] === "POST")
    {
        if (empty($_POST["old_password"]))
        {
            apologize("You must provide your current password.");
        }
        else if (empty($_POST["new_password"]))
        {
            apologize("You must provide a new password you want to change to.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("Please re-enter your new password.");
        }
        else if (htmlspecialchars($_POST["new_password"]) != htmlspecialchars($_POST["confirmation"]))
        {
            apologize("Uh-oh. Looks like the password you have re-entered and your new password do not match.");
        }
        else if (htmlspecialchars($_POST["old_password"]) == htmlspecialchars($_POST["new_password"])) 
        {
            apologize("Uh-oh. Looks like your new password is the same as your old one.");
        }
    }
    
    $rows = CS50::query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);

    $row = $rows[0];

    if (!password_verify(htmlspecialchars($_POST["old_password"]), $row["hash"]))
    {
        apologize("Uh-oh. Looks like you have mistyped your password.");
    }
    CS50::query("UPDATE users SET hash = ? WHERE id = ?;", password_hash(htmlspecialchars($_POST["new_password"]), PASSWORD_DEFAULT), $_SESSION["id"]);

    success("Your password has been changed successfully.");
    
?>