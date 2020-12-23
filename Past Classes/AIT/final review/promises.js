


//https://cs.nyu.edu/courses/spring20/CSCI-UA.0480-008/_site/slides/21/promises.html?print-pdf#/
//avoiding chaining
//https://cs.nyu.edu/courses/spring20/CSCI-UA.0480-008/_site/slides/21/promises.html?print-pdf#/
//function to retrive a url and call cb with the response text
function get(url, cb) {
  console.log('getting ', url);
  req = new XMLHttpRequest();
  req.open('GET', url, true);
  req.addEventListener('load', function() {
    console.log('loading req');
    if(req.status >= 200 && req.status < 400) {
      console.log(req.responseText);
      cb(req.responseText);
    }
  });
  req.send();
}
// and also 
function extractURL(json) {
  const data = JSON.parse(json) 
  console.log(data.url);
  return data.url;
}
//solution 
const url = 'http://localhost:3000/data/tango.json';

get(url, function(responseText) {
  const url2 = extractURL(responseText); 
  get(url2, function(responseText) {
    const url3 = extractURL(responseText); 
    get(url3, function(responseText) {
      console.log('done'); 
    });
  });
});

///////another solution is to use promises: api code that acts like we are dealing with sequential operations
//A Promise is an object that represents an asynchronous action - some operation that may or may not have been completed yet
//such as writing to a file, making an http request, getting data from a db
//it can be pending, fulfilled, rejected
const p = new Promise(function(fulfill, reject) { //always one param: executor function, which always has to params
  // do something async
  if(asyncTaskCompletedSuccessfully) {
	fulfill('Success!');
  } else {
	reject('Failure!');
  }
});
//two methos that allow the fulfull and reject objects to be set
then(fulfill, reject) //sets both the fulfill and reject functions, performs the appropriate callback (arg1 or arg2)
catch(reject) //only sets the reject function
