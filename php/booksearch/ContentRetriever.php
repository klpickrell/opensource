<?php

class ContentRetriever
{
  var $urls;
  var $multi_handle;
  var $url_handles;
  var $url_contents;

  function ContentRetriever() {

    if( $this->canParallelExecute() )
      $this->multi_handle = curl_multi_init();

    $this->urls = array();
    $this->url_handles = array();
    $this->url_contents = array();
  }

  function canParallelExecute() {
    return 
      function_exists( 'curl_multi_add_handle' ) &&
      function_exists( 'curl_multi_exec' ) &&
      function_exists( 'curl_multi_getcontent' );
  }

  function addURL( $url ) {
    $this->urls[] = $url;
    $this->url_handles[$url] = curl_init( $url );
    curl_setopt( $this->url_handles[$url], CURLOPT_HEADER, false);
    curl_setopt( $this->url_handles[$url], CURLOPT_RETURNTRANSFER, true );

    if( $this->canParallelExecute() ) {
      curl_multi_add_handle( $this->multi_handle, $this->url_handles[$url] );
    }
  }

  function retrieveAll() {

    if( $this->canParallelExecute() ) {
      curl_multi_select($this->multi_handle);
      do {
	curl_multi_exec( $this->multi_handle, $running );
      } while( $running == CURLM_CALL_MULTI_PERFORM );
    } else {
      foreach( $this->url_handles as $url => $handle ) {
	$this->url_contents[$url] = curl_exec( $handle );
      }
    }
  }

  function getResponse( $url ) {
    if( $this->canParallelExecute() ) {
      return curl_multi_getcontent( $this->urlhandles[$url] );
    } else {
      return $this->url_contents[$url];
    }
  }

  function retrieveSingle( $url ) {
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_HEADER, false);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

    $page = curl_exec($ch);
    curl_close($ch);

    return $page;
  }
}

?>
