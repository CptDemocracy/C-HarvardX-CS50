<div class="list-group">
    <?php foreach ($articles as $article): ?>
          <a href="<?=$article["link"];?>" class="list-group-item"><?=$article["title"];?></a>
    <?php endforeach; ?>
</div>