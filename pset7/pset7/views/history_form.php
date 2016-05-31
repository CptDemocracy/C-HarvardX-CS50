<?php
    $history    = CS50::query("SELECT * FROM history WHERE user_id = ?;", $_SESSION["id"]);
?>

<?php 
      if(!array_key_exists("symbol",       $history[0]) &&
         !array_key_exists("shares",       $history[0]) && 
         !array_key_exists("operation_id", $history[0]) && 
         !array_key_exists("price",        $history[0]) && 
         !array_key_exists("timestamp",    $history[0])): 
?>
    <div class="panel panel-info">
          <div class="panel-heading">Uh-oh.</div>
          <div class="panel-body">Looks like you haven't made any transactions yet!</div>
    </div>
<?php else: ?>
    <ul class="list-group">
        <li class="list-group-item list-group-item-info">
                <div class="row">
                    <div class="col-sm-3">
                        <h4>Symbol</h4>
                    </div>
                    <div class="col-sm-3">
                        <h4>Number of shares</h4>
                    </div>
                    <div class="col-sm-2">
                        <h4>Operation</h4>
                    </div>
                    <div class="col-sm-2">
                        <h4>Share price</h4>
                    </div>    
                    <div class="col-sm-2">
                        <h4>Date</h4>
                    </div> 
                </div>
            </li>
        <?php foreach ($history as $row): ?>
            <li class="list-group-item">
                <div class="row">
                    <div class="col-sm-3">
                        <p><?= $row["symbol"]; ?></p>
                    </div>
                    <div class="col-sm-3">
                        <p><?= $row["shares"]; ?></p>
                    </div>
                    <div class="col-sm-2">
                        <p>
                            <?php 
                                $operation = CS50::query("SELECT meaning FROM operations WHERE id = ?;", $row["operation_id"])[0]["meaning"];
                                printf(mb_strtoupper($operation));
                            ?>
                        </p>
                    </div>
                    <div class="col-sm-2">
                        <p><?= number_format($row["price"], 2); ?></p>
                    </div>    
                    <div class="col-sm-2">
                        <p><?= $row["timestamp"]; ?></p>
                    </div> 
                </div>
            </li>
        <?php endforeach; ?>
    </ul>
<?php endif; ?>