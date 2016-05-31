<form action="change_password.php" method="post">
    <div class="form-group">
        <input class="form-control" name="old_password" placeholder="Current password" type="password"/>
    </div>
    <div class="form-group">
        <input class="form-control" name="new_password" placeholder="New password" type="password"/>
    </div>
    <div class="form-group">
        <input class="form-control" name="confirmation" placeholder="Re-enter password" type="password"/>
    </div>
    <button class="btn btn-default" type="submit">
        Change password
    </button>
</form>