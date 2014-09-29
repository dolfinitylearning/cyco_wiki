<?php

/**
 * @file
 * template.php
 */

/**
 * Implements hook_theme_registry_alter().
 * 
 * Prevent the Bootstrap theme from running bootstrap_process_book_navigation.
 * It creates errors sometimes.
 */
function cyco_wiki_theme_registry_alter(&$registry) {
  $target_index = NULL;
  foreach ( $registry['book_navigation']['process functions'] as $index => $name ) {
    if ( $name == 'bootstrap_process_book_navigation' ) {
      $target_index = $index;
      break;
    }
  }
  if ( !is_null($target_index) ) {
    unset( $registry['book_navigation']['process functions'][ $target_index ] );
  }
}
