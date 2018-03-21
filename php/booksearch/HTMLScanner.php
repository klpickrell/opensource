<?php

class HTMLScanner {

    var $ElementName = "";
    var $ElementValue = "";
    var $Attributes;

    var $html;
    var $htmlLength;
    var $htmlIndex = 0;

    var $BOE_ARRAY;
    var $B_ARRAY;
    var $BOS_ARRAY;
    

    function HTMLScanner( $text ) {
        $this->html = $text;
        $this->htmlLength = strlen($text);
        $this->Attributes = array();
        $this->setTextIndex (0);

        $this->BOE_ARRAY = array (" ", "\t", "\r", "\n", "=" );
        $this->B_ARRAY = array (" ", "\t", "\r", "\n" );
        $this->BOS_ARRAY = array (" ", "\t", "\r", "\n", "/" );
    }

    function parse() {
        $text = $this->skipToElement();
        if ($text != "") {
            $this->ElementName = "Text";
            $this->ElementValue = $text;
	    $this->clearAttributes();
            return true;
        }
        return $this->readTag();
    }

    function clearAttributes() {
        $this->Attributes = array();
    }

    function readTag() {
        if ($this->currentChar != "<") {
            return false;
        }
        $this->clearAttributes();
        $this->skipMaxInTag ("<", 1);
        if ($this->currentChar == '/') {
            $this->moveNext();
            $name = $this->skipToBlanksInTag();
            $this->ElementName = $name;
            $this->ElementValue = "";            
            $this->skipEndOfTag();
            return true;
        }
        $name = $this->skipToBlanksOrSlashInTag();
        if (!$this->isValidTagIdentifier ($name)) {
                $comment = false;
                if (strpos($name, "!--") === 0) {
                    $ppos = strpos($name, "--", 3);
                    if (strpos($name, "--", 3) === (strlen($name) - 2)) {
                        $this->ElementName = "Comment";
                        $this->ElementValue = "<" . $name . ">";
                        $comment = true;                        
                    }
                    else {
                        $rest = $this->skipToStringInTag ("-->");    
                        if ($rest != "") {
                            $this->ElementName = "Comment";
                            $this->ElementValue = "<" . $name . $rest;
                            $comment = true;
                            // Already skipped end of tag
                            return true;
                        }
                    }
                }
                if (!$comment) {
                    $this->ElementName = "Text";
                    $this->ElementValue = "<" . $name;
		    $this->clearAttributes();
                    return true;
                }
        }
        else {
                $this->ElementValue = "";
                $this->ElementName = $name;
                while ($this->skipBlanksInTag()) {
                    $attrName = $this->skipToBlanksOrEqualsInTag();
                    if ($attrName != "" && $attrName != "/") {
                        $this->skipBlanksInTag();
                        if ($this->currentChar == "=") {
                            $this->skipEqualsInTag();
                            $this->skipBlanksInTag();
                            $value = $this->readValueInTag();
                            $this->Attributes[strtolower($attrName)] = $value;
                        }
                        else {
                            $this->Attributes[strtolower($attrName)] = "";
                        }
                    }
                }
        }
        $this->skipEndOfTag();
        return true;            
    }

    function isValidTagIdentifier ($name) {
        return ereg ("^[A-Za-z0-9_\\-]+$", $name);
    }
    
    function skipBlanksInTag() {
        return "" != ($this->skipInTag ($this->B_ARRAY));
    }

    function skipToBlanksOrEqualsInTag() {
        return $this->skipUntil($this->BOE_ARRAY);
    }

    function skipToBlanksInTag() {
        return $this->skipUntil($this->B_ARRAY);
    }

    function skipToBlanksOrSlashInTag() {
        return $this->skipUntil($this->BOS_ARRAY);
    }

    function skipEqualsInTag() {
        return $this->skipMaxInTag ("=", 1);
    }

    function readValueInTag() {
        $ch = $this->currentChar;
        $value = "";
        if ($ch == "\"") {
            $this->skipMaxInTag ("\"", 1);
            $value = $this->skipUntil("\"");
            $this->skipMaxInTag ("\"", 1);
        }
        else if ($ch == "'") {
            $this->skipMaxInTag ("'", 1);
            $value = $this->skipUntil("'");
            $this->skipMaxInTag ("'", 1);
        }                
        else {
            $value = $this->skipToBlanksInTag();
        }
        return $value;
    }

    function setTextIndex ($index) {
        $this->htmlIndex = $index;
        if ($index >= $this->htmlLength) {
            $this->currentChar = -1;
        }
        else {
            $this->currentChar = $this->html{$index};
        }
    }

    function moveNext() {
        if ($this->htmlIndex < $this->htmlLength) {
            $this->setTextIndex ($this->htmlIndex + 1);
            return true;
        }
        else {
            return false;
        }
    }

    function skipEndOfTag() {
        while (($ch = $this->currentChar) !== -1) {
            if ($ch == ">") {
                $this->moveNext();
                return;
            }
            $this->moveNext();
        }
    }

    function skipInTag ($chars) {
        $sb = "";
        while (($ch = $this->currentChar) !== -1) {
            if ($ch == ">") {
                return $sb;
            } else {
                $match = false;
                for ($idx = 0; $idx < count($chars); $idx++) {
                    if ($ch == $chars[$idx]) {
                        $match = true;
                        break;
                    }
                }
                if (!$match) {
                    return $sb;
                }
                $sb .= $ch;
                $this->moveNext();
            }
        }
        return $sb;
    }

    function skipMaxInTag ($chars, $maxChars) {
        $sb = "";
        $count = 0;
        while (($ch = $this->currentChar) !== -1 && $count++ < $maxChars) {
            if ($ch == ">") {
                return $sb;
            } else {
                $match = false;
                for ($idx = 0; $idx < count($chars); $idx++) {
                    if ($ch == $chars[$idx]) {
                        $match = true;
                        break;
                    }
                }
                if (!$match) {
                    return $sb;
                }
                $sb .= $ch;
                $this->moveNext();
            }
        }
        return $sb;
    }

    function skipUntil( $chars ) {
        $sb = "";
        while (($ch = $this->currentChar) !== -1) {
            $match = $ch == ">";
            if (!$match) {
                for ($idx = 0; $idx < count($chars); $idx++) {
                    if ($ch == $chars[$idx]) {
                        $match = true;
                        break;
                    }
                }
            }
            if ($match) {
                return $sb;
            }
            $sb .= $ch;
            $this->moveNext();
        }
        return $sb;
    }

  /*
    function skipUntil( $chars ) {
        $sb = "";
        while( ($ch = $this->currentChar) !== -1 ) {

	  if( $ch == ">" || @array_search( $ch, $chars ) ) {
	    return $sb;
	  }

          $sb .= $ch;
          $this->moveNext();
        }
        return $sb;
    }
  */
    function skipToElement() {
        $sb = "";
        while (($ch = $this->currentChar) !== -1) {
            if ($ch == "<") {
                return $sb;
            }
            $sb .= $ch;
            $this->moveNext();
        }
        return $sb;             
    }

    /**
     * Returns text between current position and $needle,
     * inclusive, or "" if not found. The current index is moved to a point
     * after the location of $needle, or not moved at all
     * if nothing is found.
     */
    function skipToStringInTag ($needle) {
        $pos = strpos ($this->html, $needle, $this->htmlIndex);
        if ($pos === false) {
            return "";
        }
        $top = $pos + strlen($needle);
        $retvalue = substr ($this->html, $this->htmlIndex, $top - $this->htmlIndex);
        $this->setTextIndex ($top);
        return $retvalue;
    }

  function stopAtTagSequenceEnd( $sequence, $skipText = true ) {
    $count = count( $sequence );
    $total_matched = 0;
    $current = $sequence[0];
    while( true ) {
      if( $skipText && $this->ElementName == 'Text' ) {
	if( !$this->parse() ) break;
	continue;
      }

      if( $this->ElementName == $current ) {
	$total_matched++;
	if( $total_matched >= $count ) {
	  return true;
	}
	$current = $sequence[ $total_matched ];
      } else {
	$total_matched = 0;
	$current = $sequence[0];
	if( $this->ElementName == $current ) {
	  continue;
	} 
      }

      if( !$this->parse() ) break;
    }
    return false;
  }

  function stopAtTagAndAttributeSequenceEnd( $sequence, $strictlyEqual = false, $skipText = true ) {

    $count = count( $sequence );
    if( $count == 0 ) 
      return;

    $total_matched = 0;

    $done = false;

    while( true ) {

      if( $this->ElementName == 'Comment' ) {
	if( !$this->parse() ) break;
	continue;
      }

      if( $skipText && $this->ElementName == 'Text' ) {
	if( !$this->parse() ) break;
	continue;
      }

      if( $this->ElementName == $sequence[$total_matched][0] ) {
	// now check attributes
	$attributes = $sequence[$total_matched][1];
	$arr = array_intersect( $attributes, $this->Attributes );

	if( !$attributes ||
	    ($strictlyEqual && $attributes == $this->Attributes) ||
	    ($attributes == array_intersect( $attributes, $this->Attributes )) ) {

	  $total_matched++;

	  if( $total_matched >= $count ) {
	    return true;
	  }
	} else {
	  $total_matched = 0;
	}
      } else {
	$total_matched = 0;
	if( $this->ElementName == $sequence[$total_matched][0] ) {
	  continue;
	}
      }

      if( !$this->parse() ) break;
    }

    return false;
  }
}
?>
