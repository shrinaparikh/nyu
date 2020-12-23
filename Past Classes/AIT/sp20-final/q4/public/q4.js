document.addEventListener("DOMContentLoaded", main);

function getURL(url, cb) {
  const xhr = new XMLHttpRequest();
  xhr.open('GET', url);
  xhr.addEventListener('load', function() {
    if(xhr.status >= 200 && xhr.status < 400) {
      cb(JSON.parse(xhr.responseText)); 
    } 
  });
  xhr.send();
}

function handleClick() {
  getURL('/api/music/genres/:someGenreName', function(response) {
     let parent; //find genre as parent
    for(let i = 0 ; i < response.length; i++) {

      let nameEle = document.createElement('p')
      nameEle.textContent = response[i].name;
      nameEle.addEventListener('click', handleClick);
      parent.appendChild(nameEle);

    }   
  })
}

function main() {
  getURL('/api/music/genres', function(response) {
    //response is the parsed JSON data from responseText
    let parent = document.getElementById('genreList');
    for(let i = 0 ; i < response.length; i++) {
      let nameEle = document.createElement('p')
      nameEle.textContent = response[i].name;
      nameEle.addEventListener('click', handleClick);
      parent.appendChild(nameEle);

    }
    
  });
}


