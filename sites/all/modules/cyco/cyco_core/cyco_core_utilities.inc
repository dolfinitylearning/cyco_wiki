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

/**
 * Check whether the current user has a role, or one of a set of roles.
 * 
 * @global stdClass $user Current user.
 * 
 * @param int or stdClass $user User id or object.
 * @param string or array $roles Role(s) to check for.
 * @return boolean True if the user has at least one of the roles.
 */
function cyco_core_user_has_role($user, $roles) {
  // Load the user to check, depending on the type of the first argument.
  if (is_integer($user)) {
    // It's a uid.
    $user = user_load($user);
    if ( ! $user ) {
      $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__
          . ' bad uid: ' . $user;
      cyco_core_handle_error($message);
      return FALSE;
    }
  }
  elseif (is_object($user)) {
    if ( !isset($user->roles)) {
      $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__
          . ' bad user object: <pre>' . print_r($user, TRUE) . '</pre>';
      cyco_core_handle_error($message);
      return FALSE;
    }
  }
  else {
    $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__
        . ' bad thing passed: <pre>' . print_r($user, TRUE) . '</pre>';
    cyco_core_handle_error($message);
    return FALSE;
  }
  if (is_array($roles)) {
    $check = array_intersect($roles, array_values($user->roles));
    $result = empty($check) ? FALSE : TRUE;
  }
  else {
    $result = in_array($roles, $user->roles);
  }
  return $result;
}

/**
 * Check whether the current user has a role, or one of a set of roles.
 * 
 * @global stdClass $user Current user.
 * 
 * @param string or array $roles Role(s) to check for.
 * @return boolean True if the user has at least one of the roles.
 */
function cyco_core_current_user_has_role($roles) {
  global $user;
  return cyco_core_user_has_role($user, $roles);
}

