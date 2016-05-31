<?php
    $portfolio = buildPortfolio($_SESSION["id"]);
?>

<div id="portfolio" class="panel panel-default">

<?php foreach ($portfolio as $row): ?>
    <div class="row panel-body">
        <div class="col-sm-3 symbol"> <?= $row["symbol"]; ?> </div>
        <div class="col-sm-2 name"> <?= $row["name"]; ?> </div>
        <div class="col-sm-2 price"> <?= $row["price"]; ?> </div>
        <div class="col-sm-2 shares"> <?= $row["shares"]; ?> </div>
        <div class="col-sm-3 worth"> <?= $row["shares"] * $row["price"]; ?> </div>
    </div>
<?php endforeach; ?>

</div>