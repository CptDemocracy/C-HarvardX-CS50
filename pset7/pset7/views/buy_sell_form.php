<?php
    $portfolio = buildPortfolio($_SESSION["id"]);
    $action = ( mb_strtolower($operation) === "sell") ? "sell.php" : "buy.php";
?>

<?php 
    if (mb_strtolower($operation) === "buy"):
?>
    <form action="buy.php" method="post">
        <div class="form-group">
            <input autofocus autocomplete="off" type="text" placeholder="Symbol" name="symbol" />
        </div>
        <div class="form-group">
            <input autocomplete="off" type="text" placeholder="Amount" name="count" />
        </div>
        <div class="form-group">
       	    <button class="btn btn-default" type="submit">Buy</button>
       	</div>
    </form>
<?php endif; ?>

    <ul class="list-group">
        <li class="list-group-item list-group-item-info">
            <div class="row">
                <div class="col-sm-7">
                    <div class="col-sm-3">
                        <h4>Symbol</h4>
                    </div>
                    <div class="col-sm-3">
                        <h4>Name</h4>
                    </div>
                    <div class="col-sm-2">
                        <h4>Price</h4>
                    </div>
                    <div class="col-sm-2">
                        <h4>You own</h4>
                    </div>    
                    <div class="col-sm-2">
                        <h4>Total worth</h4>
                    </div> 
                </div>
                <div class="col-sm-5">
                    <div class="col-sm-6">
                        
                    </div>
                    <div class="col-sm-6">
                        
                    </div>
                </div>
            </div>
        </li>
        <?php foreach ($portfolio as $row):?>
                <li class="list-group-item">
                    <div class="row">
                        <div class="col-sm-7">
                            <div class="col-sm-3">
                                <p><?= $row["symbol"]; ?></p> 
                            </div>
                            <div class="col-sm-3">
                                <p><?= $row["name"]; ?></p>  
                            </div>
                            <div class="col-sm-2">
                                <p><?= $row["price"]; ?></p>  
                            </div>
                            <div class="col-sm-2">
                                <p><?= $row["shares"]; ?></p>  
                            </div>
                            <div class="col-sm-2">
                                <p><?= $row["shares"] * $row["price"]; ?></p>
                            </div>
                        </div>
                        <div class="col-sm-5">
                            <form action="<?= $action; ?>" method="post">
                                <div class="row">
                                    <div class="col-sm-6">
                                        <button class="btn btn-default" type="submit"><?= ucfirst($operation); ?></button>
                                        <input type="hidden" name="symbol" value="<?= $row["symbol"]; ?>"/>
                                        <input type="hidden" name="name" value="<?= $row["name"]; ?>"/>
                                        <input type="hidden" name="price" value="<?= $row["price"]; ?>"/>
                                        <input type="hidden" name="shares" value="<?= $row["shares"]; ?>"/>
                                        <input type="hidden" name="worth" value="<?= $row["shares"] * $row["price"]; ?>"/>
                                    </div>
                                    <div class="col-sm-6">
                                        <input type="text" name="count" placeholder="Amount"/>
                                    </div>
                                </div>
                            </form>
                        </div>
                    </div>
                </li>
        <?php endforeach; ?>
    </ul>
        