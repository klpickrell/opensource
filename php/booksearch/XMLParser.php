<?php
class XMLParser {

  function parse( $xml )
  {
    if( !$xml ) {
      return array();
    }

    if( !function_exists( 'xml_parser_create' ) ) {
      return array();
    }

    $parser = xml_parser_create('');
    xml_parser_set_option($parser, XML_OPTION_TARGET_ENCODING, "UTF-8"); 
    xml_parser_set_option($parser, XML_OPTION_CASE_FOLDING, 0);
    xml_parser_set_option($parser, XML_OPTION_SKIP_WHITE, 1);
    xml_parse_into_struct($parser, trim($xml), $xml_values);
    xml_parser_free($parser);

    if( !$xml_values ) {
      return;
    }

    $xml_array = array();
    $parents = array();
    $opened_tags = array();
    $arr = array();

    $current = &$xml_array;

    $repeated_tag_index = array();
    foreach($xml_values as $data) {
      unset($attributes,$value);

      // tag(string), type(string), level(int), attributes(array).
      extract($data);

      $result = array();
      $attributes_data = array();
        
      if(isset($value)) {
	$result = $value;
      }

      if( isset($attributes) ) {
	foreach($attributes as $attr => $val) {
	  $attributes_data[$attr] = $val;
	}
      }

      switch( $type ) {

      case 'open':
	$parent[$level-1] = &$current;
	if( !is_array($current) or (!in_array($tag, array_keys($current))) ) {
	  $current[$tag] = $result;
	  if($attributes_data) {
	    $current[$tag. '_attributes'] = $attributes_data;
	  }
	  $repeated_tag_index[$tag.'_'.$level] = 1;

	  $current = &$current[$tag];

	} else { // duplicate element

	  if( isset($current[$tag][0]) ) {//If there is a 0th element it is already an array
	    $current[$tag][$repeated_tag_index[$tag.'_'.$level]] = $result;
	    $repeated_tag_index[$tag.'_'.$level]++;
	  } else {//This section will make the value an array if multiple tags with the same name appear together
	    $current[$tag] = array($current[$tag],$result);//This will combine the existing item and the new item together to make an array
	    $repeated_tag_index[$tag.'_'.$level] = 2;
                    
	    if(isset($current[$tag.'_attr'])) { //The attribute of the last(0th) tag must be moved as well
	      $current[$tag]['0_attr'] = $current[$tag.'_attr'];
	      unset($current[$tag.'_attr']);
	    }

	  }
	  $last_item_index = $repeated_tag_index[$tag.'_'.$level]-1;
	  $current = &$current[$tag][$last_item_index];
	}
	break;
      case 'complete':
	//See if the key is already taken.
	if(!isset($current[$tag])) { //New Key
	  $current[$tag] = $result;
	  $repeated_tag_index[$tag.'_'.$level] = 1;
	  if( $attributes_data ) $current[$tag. '_attr'] = $attributes_data;

	} else { //If taken, put all things inside a list(array)
	  if(isset($current[$tag][0]) and is_array($current[$tag])) {//If it is already an array...

	    // ...push the new element into that array.
	    $current[$tag][$repeated_tag_index[$tag.'_'.$level]] = $result;
                    
	    if( $attributes_data ) {
	      $current[$tag][$repeated_tag_index[$tag.'_'.$level] . '_attr'] = $attributes_data;
	    }
	    $repeated_tag_index[$tag.'_'.$level]++;

	  } else { //If it is not an array...
	    $current[$tag] = array($current[$tag],$result); //...Make it an array using using the existing value and the new value
	    $repeated_tag_index[$tag.'_'.$level] = 1;
	    if(isset($current[$tag.'_attr'])) { //The attribute of the last(0th) tag must be moved as well
                            
	      $current[$tag]['0_attr'] = $current[$tag.'_attr'];
	      unset($current[$tag.'_attr']);
	    }
                        
	    if($attributes_data) {
	      $current[$tag][$repeated_tag_index[$tag.'_'.$level] . '_attr'] = $attributes_data;
	    }
	    $repeated_tag_index[$tag.'_'.$level]++; //0 and 1 index is already taken
	  }
	}
	break;
      case 'close':

	$current = &$parent[$level-1];

	break;
      }
    }
    
    return $xml_array;
  }  
}
?>