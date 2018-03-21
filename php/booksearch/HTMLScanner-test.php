<?php

require_once( "HTMLScanner.php" );

/*
$parser = new HTMLScanner( file_get_contents( 'test.html' ) );
$i = 1;
while( $parser->parse() ) {
  print( "Element $i:\n" );
  print( "ElementType=" . $parser->ElementType . "\n" );
  print( "ElementName=" . $parser->ElementName . "\n" );
  print( "ElementValue=" . $parser->ElementValue . "\n" );
  print( "Attributes=" );
  print_r( $parser->Attributes ); 
  print( "\n" );

  ++$i;
}
*/
$parser = new HTMLScanner( file_get_contents( 'target' ) );

$bookStartTagSequence = array( array( 'div', array( 'class' => 'prodBox' ) ),
			       array( 'div', array( 'class' => 'proComplete2' ) ),
			       array( 'div', array( 'class' => 'NewCatListImage2' ) ) );

if( $parser->stopAtTagAndAttributeSequenceEnd( $bookStartTagSequence ) ) {
  print( "found sequence\n" );
} else {
  print( "failed to find sequence\n" );
}

?>