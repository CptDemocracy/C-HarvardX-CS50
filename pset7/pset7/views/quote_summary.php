<?php 

    // test if everything's okay with $stock
    if (!isset($stock) || $stock === false) {
        trigger_error("Could not receive symbol data!", E_USER_ERROR);
    }

?>

<ul class="list-group summary">
    <li class="list-group-item header">
         <?= $stock["name"]." "; ?>
        (<?= $stock["symbol"];   ?>)
    </li>
    <li class="list-group-item price">
         <?= number_format($stock["price"], 2);    ?>
    </li>
</ul>