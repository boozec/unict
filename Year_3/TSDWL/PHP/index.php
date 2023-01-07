<?php
require 'json_fake_db.php';
?>
<html>
    <head>
    </head>
    <body>
        <h1>Movies JSON db</h1>
        <?php
            $movies = ReadAllFilms();
            echo $moviws;
        ?>
    </body>
</html>
