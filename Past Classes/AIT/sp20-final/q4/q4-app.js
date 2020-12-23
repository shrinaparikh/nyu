const express = require('express');
const app = express();
const mongoose = require('mongoose');
require('./db.js');
const Genre = mongoose.model('Genre');

const path = require('path');
app.use(express.static(path.join(__dirname, 'public')));

app.use(express.urlencoded({ extended: false }));

// returns the names of all genres
// response looks like {data: [{name: "genre1"}, {name: "genre2"}]}
app.get('/api/music/genres', (req, res) => {
  Genre.find({}, (err, genres) => {
    if(err) {
      res.send({err: 'an error ocurred'});
    } else {
      res.send({
        data: genres.map(g => {return {name: g.name};})
      });
    }
  })
});

// TODO: add a route that responds to GET requests for...
// /api/music/genre/someGenreName

app.get('/api/music/genres/:someGenreName', (req, res) => {
  Genre.find({name: req.params.someGenreName}, (err, genres) => {
    if(err) {
      res.send({err: 'an error ocurred'});
    } else {
      res.send({genres});
    }
  })
});

app.listen(3000);
