<?php

// print out a similar page to the previous

$header = <<<HEREDOC
<html>
<head>
  <link rel='stylesheet' type='text/css' href='styles/project_style.css' />
  <title>Book Search</title>
  <center>
  <h1>Book Search</h1>
  </center>
</head>

<body>

<form method="POST" action="search.php">
<p>
   <input type="text" size="50" maxlength="200" name="searchtext">
   Rating Scheme:
   <select name="ratingtype">
     <option value="default" selected="selected">default</option>
     <option value="price">max price</option>
   </select>
   Max Price:<input type="text" size="6" maxlength="10" name="searchprice">
</p>
<p>
   <input type="submit" value="Search">
</p>

</form>
<hr>
HEREDOC;

print( $header );

// start the script searching

error_reporting( E_ALL );

require( "search_request.php" );

if( empty( $_POST[ 'searchtext' ] ) ) {
    return;
} else {
    $searchtext = $_POST[ 'searchtext' ];
    $ratingtype = "default";
    if( !empty( $_POST[ 'ratingtype' ] ) ) {
        $ratingtype = $_POST[ 'ratingtype' ];
    }

    $price = 0;
    if( $ratingtype == 'price' ) {
      if( empty( $_POST[ 'searchprice' ] ) ) {
	print( "<h3>ERROR: Must enter max price when rating by price<h3>" );
      } else {
	$pricestring = $_POST[ 'searchprice' ];
	$price = priceValueFromString( $pricestring );
	if( $price == null ) {
	  print( "<h3>ERROR: Invalid value for max price<h3>" );
	  print( "<br><h3>You can enter values such as 10, $10, or $10.00</h3>" );
	} else {
	  $results = SearchRequest( $searchtext, $ratingtype, $price );
	  print( "$results<hr>" );
	}
      }
    } else {
      $results = SearchRequest( $searchtext, $ratingtype );
      print( "$results<hr>" );
    }
}





print( "</body></html>" );

?>