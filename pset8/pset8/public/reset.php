<?php
    // configuration
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] === "GET")
    {
        render("reset_form.php", [ "title" => "Reset password" ]);
    }
    else if ($_SERVER["REQUEST_METHOD"] === "POST")
    {
        $result = CS50::query("SELECT email FROM users WHERE email = ?;", htmlspecialchars($_POST["email"]));
        if (!$result) 
        {
            apologize("Uh-oh. Looks like this e-mail is not registered.");
        }
        $email = $result[0]["email"];
        
        $username = CS50::query("SELECT username FROM users WHERE email = ?;", htmlspecialchars($_POST["email"]))[0]["username"];
        
        $newPassword = generateRandomString(12);
        CS50::query("UPDATE users SET hash = ? WHERE email = ?;", password_hash($newPassword, PASSWORD_DEFAULT), $email);
        
        $msg = "Hey, it looks like you forgot your password but don't worry! CS50 Maps Bot (hey, that's me) "
                    ."has reset your old password and generated a new one for you:\n\n"
                    ."Username: "
                    .$username
                    ."\nPassword: "
                    .$newPassword
                    ."\n\nYou can change it anytime once you login by clicking on \"Change password\" at the "
                    ."bottom of the page."
                    ."\n\n<3 CS50 Maps Bot";
        
        if (sendMail($email, "CS50 Maps Password Reset", $msg))
        {
            success("A message with further instructions to reset your password has been sent to your e-mail address.");
        }
        else
        {
            apologize("Uh-oh. Something went wrong. Please try again.");
        }
        
    }
?>