<ul class="nav nav-tabs">
    <li>
        <a href="index.php">
                <span aria-hidden="true" class="glyphicon glyphicon-home"></span>
                Home
        </a>
    </li>
    <li>
        <a href="<?php 
                    if (isset($_SESSION["id"])) 
                        echo("logout.php");
                    else
                        echo("login.php"); 
                ?>">
                <span aria-hidden="true" class="glyphicon <?php 
                    if (isset($_SESSION["id"])) 
                        echo("glyphicon-log-out");
                    else
                        echo("glyphicon-log-in"); ?>"
                ></span>
                <?php
                    if (isset($_SESSION["id"]))
                        echo("Log Out");
                    else
                        echo("Log In");
                ?>
        </a>
    </li>
    <?php if (!isset($_SESSION["id"])): ?>
    <li>
        <a href="register.php">
            Register
        </a>
    </li>
    <?php endif; ?>
    <?php if (isset($_SESSION["id"])): ?>
    <li>
        <a href="change_password.php">
            Change Password
        </a>
    </li>
    <?php endif; ?>
    <?php if (isset($_SESSION["id"])): ?>
    <li class="bg-info">
        <a href="favs.php">
            <span aria-hidden="true" class="glyphicon glyphicon-heart"></span>
            My Places
        </a>
    </li>
    <?php endif; ?>   
</ul>