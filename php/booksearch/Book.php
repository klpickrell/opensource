<?php

class Book
{
    var $url;
    var $title;
    var $price;
    var $price_value;
    var $image;
    var $rating;
    var $rating_value;

    function Book( $url, $title, $price, $price_value, $image, $rating='', $rating_value=0.0 ) {
        $this->url = $url;
        $this->title = $title;
        $this->price = $price;
        $this->price_value = $price_value;
        $this->image = $image;

	$this->rating=$rating;
	$this->rating_value = $rating_value;
    }

    function printRow( $heading, $trstyle = 'tr', $tdstyle = 'td' ) {
        return "<tr class=\"$trstyle\"><th>$heading</th><td class=\"$tdstyle\"><img src=\"$this->image\" alt=\"$this->title\"/></td><td class=\"$tdstyle\"><a href=\"$this->url\" title=\"$this->title\" target=\"_blank\">$this->title</a><div>Price: $this->price<br></div></td><td class=\"$tdstyle\">$this->rating</td></tr>";
    }

  function compareRatingHigh( $book1, $book2 ) {
    if( $book1->rating_value == $book2->rating_value ) {
      return 0;
    }
    return ($book1->rating_value < $book2->rating_value) ? 1 : -1;
  }

  function compareRatingLow( $book1, $book2 ) {
    if( $book1->rating_value == $book2->rating_value ) {
      return 0;
    }
    return ($book1->rating_value < $book2->rating_value) ? -1 : 1;
  }
}

?>