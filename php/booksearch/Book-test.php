<?php

require( "Book.php" );

$book = new Book( "http://www.thebook.com",
                  "The Title",
                  "$24.99",
                  "The Image" );

print $book->printRow();

?>