/**
 * You can modify this file.
 */

#include "matcher.h"
/**
 * Your helper functions can go below this line
 */



/**
 * Your helper functions can go above this line
 */


/**
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */



/**
 * Implementation of your matcher function, which
 * will be called by the main program.
 *
 * You may assume that both line and pattern point
 * to reasonably short, null-terminated strings.
 */ 
int matches_leading(char *partial_line, char *pattern) {
  if(*pattern == '\0'){ //base case: it matches if there is no pattern
    return 1;
  }
  else if(*partial_line == '\0'){ //if the base case is null, return 1 which is false
    return 1;
  }
  else if(*pattern == '\\'){ //if it contains '\' change the next character to a normal character and not a special character
    if(*(pattern + 2) == '?'){ //if there is a ? after 2 characters in the pattern
      if(*partial_line == *(pattern+1)){ // if the character in the line is equal to the next character in the pattern, the function recursively
        return matches_leading(partial_line+1, pattern+3);
      }
      return matches_leading(partial_line, pattern+3); //increment through recursion
    }
    else if(*partial_line == *(pattern+1)){ //treat the special character as a normal character and check if it is the same as the character in the partial_line
      return matches_leading(partial_line+1, pattern+2);
    }
    else{ // else just return false
      return 0;
    }
  }
  else if(*pattern == '+'){ //if the pattern contains a '+' 
    while(*(pattern - 1) == *partial_line){ //Continue matching characters as long as they are equal to the preceding character in the pattern
      partial_line++; 
    }
    return matches_leading(partial_line, pattern + 1);
  }
  else if(*pattern == '.'){ //if the pattern contains a '.'
    if(*partial_line != '\n'){ //if the partial line is not a newline character, keep matching the characters
      return matches_leading(partial_line + 1, pattern + 1);
    }
    else{ 
      return 0;
    }
  }
  else if(*(pattern + 1) == '?'){ //if the next character in the pattern is a '?'
    if(*pattern == *partial_line){ //if the pattern and character on the line are the same, skip the optional character in pattern
      return matches_leading(partial_line+1, pattern+2);
    }
    else{
      return matches_leading(partial_line, pattern+2);
    }
  }
  else{
    if(*partial_line == *pattern && *pattern != '?' && *pattern != '+' && *pattern != '.' && *pattern != '\\'){ //if the characters from the partial_line and pattern are the same, and the characters are not special cases, increment recursively
      return matches_leading(partial_line+1, pattern+1);
    } 
  }
  return 0;
}

int rgrep_matches(char *line, char *pattern) { //function checks if the pattern matches any leading portion of the line
  while(*line != '\0'){ //while the line is not null, iterate through each character in the line
    if(matches_leading(line, pattern)){ //if a match is found, return 1. If there is no match, increment to the next character of line 
      return 1;  
    }
    else{
      line++;
    }
  }
  return 0;
}
