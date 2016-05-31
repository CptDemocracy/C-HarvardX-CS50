            </div>

            <div id="bottom">
                Brought to you by the number <a href="http://cdn.cs50.net/2015/fall/psets/7/pset7/pset7.html">7</a>.
            </div>
            <?php if (!empty($_SESSION["id"])): ?>
                <div>
                    <a href="change_password.php">
                        <p class="text-center small">Change password</p>
                    </a>
                </div>
            <?php endif; ?>
        </div>

    </body>

</html>
