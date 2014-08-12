<?php

/**
 * @file
 * Defines some CyCo utilities used by other modules.
 */




/**
 * Format a timestamp in ISO 8601, using the user's timezone, or a default
 * if not set.
 * @param type $timestamp Timestamp to format.
 * @return string Date/time in 8601, using user's timezone.
 */
function cyco_core_timestamp_to_iso6801( $timestamp ) {
  $result = format_date($timestamp, 'custom', 'c', date_default_timezone());
  return $result;
}

/**
 * Convert date/time from UTC to user's time zone.
 * @param string $utc Date/time in UTC, e.g., 1995-04-27 01:55:55
 * @return string Date/time in user's time zone.
 */
function cyco_core_utc_to_user_time_zone( $utc ) {
  $utc .= ' +0:00';
  $dt = new DateTime('@' . strtotime($utc));  // will snap to UTC because of the 
  $dt->setTimeZone(new DateTimeZone(drupal_get_user_timezone()));
  $user_tz = $dt->format('Y-m-d H:i:s');
  return $user_tz;
}

/** Get now in format for date field.
 * @return array Formatted date/time.
 */
function cyco_core_get_now_utc() {
  $when = strtotime('now');
  $date = array(
    'value' => format_date($when, 'custom', 'Y-m-d H:i:s', 'UTC'),
    'timezone' => 'UTC',  
    'timezone_db' => 'UTC',
  );
  return $date;
  
  
}

/**
 * Find the next line break in a string, whether it's \r\n, or \n.
 * @param string $string String to search.
 * @param int $start Where to start searching.
 * @return array Result array. 
 *   [0] = position (-1 if not found).
 *   [1] = EOL length (0 if not found, 1 if \n, 2 if \r\n). 
 */
function cyco_core_find_next_line_break( $string, $start ) {
  $pos = stripos( $string, "\n", $start );
  if ( $pos === FALSE ) {
    return array(-1, 0);
  }
  if ( $pos == 0 ) {
    return array(0, 1);
  }
  if ( substr($string, $pos - 1, 1) == "\r" ) {
    return array( $pos - 1, 2);
  }
  return array( $pos, 1 );
}

/**
 * Convert a Drupal URI to a URL usable on the Web.
 * @param string $uri Drupal URI
 * @return string Usable URL
 */
function cyco_core_uri2path( $uri ) {
  $absolute_url = file_create_url( $uri );
  $url = parse_url($absolute_url);
  $usable_url = $url['path'];
  return $usable_url;
}
