<?php $favs = CS50::query("SELECT * FROM favorites WHERE user_id = ?;", $_SESSION["id"]); ?>

<?php if (count($favs) > 0): ?>
    <div class="panel panel-default">
        <div class="row panel-header bg-primary">
            <div class="col-sm-3"><h4>Place Name</h4></div>
            <div class="col-sm-2"><h4>Admin Name</h4></div>
            <div class="col-sm-2"><h4>Country Code</h4></div>
            <div class="col-sm-2"></div>
            <div class="col-sm-2"></div>
            <div class="col-sm-1"></div>
        </div>
        
        <?php foreach ($favs as $row): ?>
        <div class="row panel-body">
            <div class="col-sm-12">
                <form action="favs.php" method="post">
                    <div class="col-sm-3 place_name"> <?= $row["place_name"]; ?> </div>
                    <div class="col-sm-2 admin_name"> <?= $row["admin_name1"]; ?> </div>
                    <div class="col-sm-2 country_code"> <?= $row["country_code"]; ?> </div>
                    <div class="col-sm-2">
                        <button class="btn btn-default" name="news_btn" type="submit">
                            <span aria-hidden="true" class="glyphicon glyphicon-list-alt"></span>
                            Local News
                        </button>
                    </div>
                    <div class="col-sm-2">
                        <button class="btn btn-default" name="search_btn" type="submit">
                            <span aria-hidden="true" class="glyphicon glyphicon-search"></span>
                            Locate on Map
                        </button>
                    </div>
                    <div class="col-sm-1">
                        <button class="btn btn-danger" name="remove_btn" type="submit">
                            <span aria-hidden="true" class="glyphicon glyphicon-remove"></span>
                        </button>
                    </div>
                    <input type="hidden" name="place_name" value="<?= $row["place_name"]; ?>"/>
                    <input type="hidden" name="admin_name1" value="<?= $row["admin_name1"]; ?>"/>
                    <input type="hidden" name="country_code" value="<?= $row["country_code"]; ?>"/>
                    <input type="hidden" name="lat" value="<?= $row["latitude"]; ?>"/>
                    <input type="hidden" name="lng" value="<?= $row["longitude"]; ?>"/>
                </form>
            </div>
        </div>
        <?php endforeach; ?>
        
    </div>
<?php else: ?>
    <div class="jumbotron">Looks like you have no favorite places yet! :(</div>
<?php endif; ?>