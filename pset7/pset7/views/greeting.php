<?php
    $userData = CS50::query("SELECT username, cash FROM users WHERE id = ?;", $_SESSION["id"]);
    $userName = $userData[0]["username"];
    $cash     = number_format($userData[0]["cash"], 2);
?>

    <div class="container bg-primary">
        <div class="page-header">
            <h4>Greetings, <span class="lead"><?= $userName; ?></span>, your cash: <span class="lead">$<?= $cash; ?></span></h4>
        </div>
    </div>