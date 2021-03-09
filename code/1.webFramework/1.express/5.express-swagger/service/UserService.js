'use strict';


/**
 * Logs user into the system
 * 
 *
 * username String user name for login
 * password String user password for login
 * returns ApiResponse
 **/
exports.userLoginGET = function(username,password) {
  return new Promise(function(resolve, reject) {
    var examples = {};
    examples['application/json'] = {
  "code" : 0,
  "message" : "success",
  "data" : [ {
    "username" : username,
    "password" : password
  } ]
};
    if (Object.keys(examples).length > 0) {
      resolve(examples[Object.keys(examples)[0]]);
    } else {
      resolve();
    }
  });
}


/**
 * Get user by user name
 * 
 *
 * username String The name that needs to be fetched
 * returns ApiResponse
 **/
exports.userUsernameGET = function(username) {
  return new Promise(function(resolve, reject) {
    var examples = {};
    examples['application/json'] = {
  "code" : 0,
  "message" : "success",
  "data" : [ {
    "username" : username
  } ]
};
    if (Object.keys(examples).length > 0) {
      resolve(examples[Object.keys(examples)[0]]);
    } else {
      resolve();
    }
  });
}

