<html>
<head>
  <link rel='stylesheet' type='text/css' href='styles/project_style.css' />
  <title>Book Search</title>
  <center>
  <h1>Book Search</h1>
  </center>
</head>

<body>

<!-- <hr> -->
<!-- <p><b>Enter Search Query</b></p> -->
<form method="POST" action="search.php">
<p>
   <input type="text" size="50" maxlength="200" name="searchtext">
   Rating Scheme:
   <select name="ratingtype">
     <option value="default" selected="selected">default</option>
     <option value="price">price</option>
   </select>
   Price:<input type="text" size="6" maxlength="10" name="searchprice">
</p>
<p>
   <input type="submit" value="Search">
</p>

</form>

<hr>

<!-- start the php script -->
<?php

function hr() {
  print( "<hr>" );
}

function br() {
  print( "<br>" );
}

?>

</body>
</html>