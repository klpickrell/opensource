<?php

require_once( "ContentRetriever.php" );
require_once( "XMLParser.php" );
require_once( "HTMLScanner.php" );
require_once( "Book.php" );

define('VERSION','2005-02-23');
define('SUBSCRIPTION_ID', '1A7XKHR5BYD0WPJVQEG2');
define('ASSOCIATE_TAG','ws');

function SearchRequest( $searchtext, $ratingtype, $price = 0 ) {

    $results = '';

    $amazon_url = 'http://webservices.amazon.com/onca/xml?Service=AWSECommerceService&AssociateTag='. ASSOCIATE_TAG.'&SubscriptionId='.SUBSCRIPTION_ID.'&Operation=ItemSearch&ItemSearch.Shared.Keywords=' . urlencode($searchtext) . '&ItemSearch.Shared.MerchantId=All&ItemSearch.Shared.SearchIndex=Books&ItemSearch.Shared.ResponseGroup=Medium,VariationSummary&ItemSearch.1.ItemPage=1&ItemSearch.2.ItemPage=2&Version='.VERSION;

    $pb_url = 'http://www.powells.com/s?header=Search+Form&kw=' . urlencode( $searchtext );
    $overstock_url = 'http://www.overstock.com/search?taxonomy=dep9&SearchType=bookspage&keywords=' . urlencode( $searchtext ) . '&x=0&y=0';

    $retriever = new ContentRetriever();

    $retriever->addURL( $amazon_url );
    $retriever->addURL( $pb_url );
    $retriever->addURL( $overstock_url );

    $retriever->retrieveAll();

    $response = $retriever->getResponse( $amazon_url );
    $amazonBooks = processAmazonResponse( $response );

    if( rateBooks( $amazonBooks, $ratingtype, $price ) ) { // returns true if rating was performed
      sortBooks( $amazonBooks );
    }

    $results .= generateBooksTable( $amazonBooks, 'Results provided by Amazon.com' );

    $response = $retriever->getResponse( $pb_url );
    $pBooks= processPBooksResponse( $response );

    if( rateBooks( $pBooks, $ratingtype, $price ) ) {
      sortBooks( $pBooks );
    }

    $results .= '<hr>';
    $results .= generateBooksTable( $pBooks, 'Results provided by Powells.com' );

    $response = $retriever->getResponse( $overstock_url );
    $osBooks = processOverstockBooksResponse( $response );

    if( rateBooks( $osBooks, $ratingtype, $price ) ) {
      sortBooks( $osBooks );
    }
    
    $results .= '<hr>';
    $results .= generateBooksTable( $osBooks, 'Results provided by Overstock.com' );

    return $results;
}

function rateBooks( &$books, $ratingtype, $price ) {

  if( empty( $books ) ) {
    return false;
  }

  if( $ratingtype == "default" || $price <= 0 ) {
    foreach( $books as $i=>$book ) {
      $books[$i]->rating = "N/A";
    }

    return false;

  } else {
    foreach( $books as $i=>$book ) {
      if( $book->price_value <= $price ) {
	$books[$i]->rating = "<img src=\"images/5star.gif\" alt=\"5 stars\" />";
	$books[$i]->rating_value = 100.0;
      } else {
	$difference_ratio = ($book->price_value - $price)/$price;
	if( $difference_ratio >= 1 ) {
	  // anything greater than 2x price is 1 star
	  $books[$i]->rating = "<img src=\"images/1star.gif\" alt=\"1 star\" />";
	  $books[$i]->rating_value = 20.0;
	} else {

	  // the lower the difference ratio, the lower the book price and
	  // the higher the rating up to 4.5 stars
	  if( $difference_ratio > 0 &&
	      $difference_ratio <= 0.14 ) {
	    $books[$i]->rating = "<img src=\"images/4.5star.gif\" alt=\"4.5 stars\" />";
	    $books[$i]->rating_value = 90.0;
	  } else if( $difference_ratio > 0.14 &&
		     $difference_ratio <= 0.28 ) {
	    $books[$i]->rating = "<img src=\"images/4star.gif\" alt=\"4 stars\" />";
	    $books[$i]->rating_value = 80.0;
	  } else if( $difference_ratio > 0.28 &&
		     $difference_ratio <= 0.42 ) {
	    $books[$i]->rating = "<img src=\"images/3.5star.gif\" alt=\"3.5 stars\" />";
	    $books[$i]->rating_value = 70.0;
	  } else if( $difference_ratio > 0.42 &&
		     $difference_ratio <= 0.56 ) {
	    $books[$i]->rating = "<img src=\"images/3star.gif\" alt=\"3 stars\" />";
	    $books[$i]->rating_value = 60.0;
	  } else if( $difference_ratio > 0.56 &&
		     $difference_ratio <= 0.70 ) {
	    $books[$i]->rating = "<img src=\"images/2.5star.gif\" alt=\"2.5 stars\" />";
	    $books[$i]->rating_value = 50.0;
	  } else if( $difference_ratio > 0.70 &&
		     $difference_ratio <= 0.84 ) {
	    $books[$i]->rating = "<img src=\"images/2star.gif\" alt=\"2 stars\" />";
	    $books[$i]->rating_value = 40.0;
	  } else if( $difference_ratio > 0.84 &&
		     $difference_ratio < 1 ) {
	    $books[$i]->rating = "<img src=\"images/1.5star.gif\" alt=\"1.5 star\" />";
	    $books[$i]->rating_value = 30.0;
	  }
	}
      }
    }
  }

  return true;
}

function sortBooks( &$amazonBooks, $whence='high' ) {
  
  if( $whence == 'high' ) { // sort high to low
    usort( $amazonBooks, array( "Book", "compareRatingHigh" ) );
  } else {  // sort low to high
    usort( $amazonBooks, array( "Book", "compareRatingLow" ) );
  }
}

function priceValueFromString( $pricestring ) {

  $price_pattern = '/\b\$?(\d+(\.\d{1,2})?)/';
  $price = null;
  if( preg_match( $price_pattern, $pricestring, $matches ) ) {
    $price = $matches[0];
  }

  if( $price )
    return (float)$price;
  else
    return null;
}

function processAmazonResponse( $xml ) {

    $parser = new XMLParser();
    $response = $parser->parse( $xml );

    if( !$response ) {
        return "unable to retrieve request from Amazon<br>";
    }

    if( isset($response['ItemSearchResponse']['Items'][0]['Request']['Errors']) ) {
        $err = $response['ItemSearchResponse']['Items'][0]['Request']['Errors'];
        return array();
    }

    $books = array();

    foreach( $response['ItemSearchResponse']['Items'] as $Items ) {

        if( !isset($Items['Item']) ) {
            break;
        }

        foreach( $Items['Item'] as $item ) {

            // Check each data point to make sure it was returned by Amazon
            if( isset( $item['VariationSummary'] ) ) {
                $saleprice = (isset($item["VariationSummary"]["LowestPrice"]["FormattedPrice"]))? $item["VariationSummary"]["LowestPrice"]["FormattedPrice"] : '';
            } else {
                $saleprice = (isset($item["OfferSummary"]["LowestNewPrice"]["FormattedPrice"]))? $item["OfferSummary"]["LowestNewPrice"]["FormattedPrice"] : '';
            }

            if( $saleprice == '' ) continue;

            $image = $item["SmallImage"]["URL"];

            $title=$item['ItemAttributes']['Title'];

            if( isset($item["DetailPageURL"]) ) {
                $url = $item["DetailPageURL"];
            } else {
                $url = '';
            }

            $books[] = new Book( $url, $title, $saleprice, priceValueFromString( $saleprice ), $image );
        }
    }

    return $books;
}

function processPBooksResponse( $content ) 
{
  $books = array();
  $scanner = new HTMLScanner( $content );
  $done = false;
  while( !$done && $scanner->parse() ) {
    if( $scanner->ElementName == 'ol' &&
	isset( $scanner->Attributes[ 'class' ] ) &&
	$scanner->Attributes[ 'class' ] == 'booklist search border-bottom' ) 
      {
	// we found the start of the book list, continue reading all the books
	while( !$done ) {
	  $tagsequence = array( 'li', 'small', 'small', 'div', 'a' );
	  if( !$scanner->stopAtTagSequenceEnd( $tagsequence ) ) {
	    $done = true;
	    break;
	  }

	  $url = 'http://www.powells.com' . $scanner->Attributes[ 'href' ];
	  $title = $scanner->Attributes[ 'title' ];

	  if( !$scanner->parse() ) {
	    $done = true;
	    break;
	  }

	  if( !$scanner->ElementName == 'img' ) {
	    continue;    // skip this element
	  }

	  $image = $scanner->Attributes[ 'src' ];

	  // now find the price
	  while( $scanner->parse() ) {
	    if( !empty( $scanner->Attributes ) &&
		isset( $scanner->Attributes[ 'class' ] ) &&
		$scanner->Attributes[ 'class' ] == 'price' ) {
	    
	      if( !$scanner->parse() ) {
		$done = true;
		break;
	      }


	      $price = $scanner->ElementValue;
	      $price_value = priceValueFromString( $scanner->ElementValue );

	      $books[] = new Book( $url, $title, $price, $price_value, $image );
	      break;
	    }
	  }
	}
      }
  }

  return $books;
}

function processOverstockBooksResponse( $content ) 
{
  $books = array();
  $scanner = new HTMLScanner( $content );

  $bookStartTagSequence = array( array( 'div', array( 'class' => 'prodBox' ) ),
				 array( 'div', array( 'class' => 'proComplete2' ) ),
				 array( 'div', array( 'class' => 'NewCatListImage2' ) ) );

  while( $scanner->parse() ) {

    if( $scanner->stopAtTagAndAttributeSequenceEnd( $bookStartTagSequence ) ) {

      while( $scanner->ElementName != 'a' )
	if( !$scanner->parse() ) break 2;

      
      $url = $scanner->Attributes[ 'href' ];
      while( $scanner->ElementName != 'img' )
	if( !$scanner->parse() ) break 2;

      $image = $scanner->Attributes[ 'src' ];

      if( !$scanner->stopAtTagAndAttributeSequenceEnd( array( array( 'div', array( 'class' => 'NewCatListPro' ) ) ) ) )
	break;

      while( $scanner->ElementName != 'a' )
	if( !$scanner->parse() ) break 2;

      $title = $scanner->Attributes[ 'title' ];

      if( !$scanner->stopAtTagAndAttributeSequenceEnd( array( array( 'span', array( 'class' => 'NewCatListPrice2' ) ) ) ) )
	break;

      if( !$scanner->parse() ) break;

      $price = $scanner->ElementValue;
      $price_value = priceValueFromString( $scanner->ElementValue );

      // need to crop the string and format it properly

      $books[] = new Book( $url, $title, $price, $price_value, $image );
    }
  }

  return $books;
}

function generateBooksTable( $books, $caption )
{
  // Create the outside of the output table
  $resultstable = "<table id=\"booktable\" summary=\"Search Results\">";
  $resultstable .= "<caption>$caption</caption>";

  if( empty( $books ) ) {
    $resultstable .= "<tr>No Results Found</tr>";
  } else {
    $resultstable .= "<tr><th>Item</th><th>&nbsp</th><th>Title</th><th>Rating</th><tr>";
    $i = 1;
    foreach( $books as $book ) {
      if( $i % 2 ) {
	$resultstable .= $book->printRow( $i, "even" );
      } else {
	$resultstable .= $book->printRow( $i, "odd", "alt" );
      }

      ++$i;
    }
  }
  // Close the table
  $resultstable .= '</table>';
  return $resultstable;
}

?>
