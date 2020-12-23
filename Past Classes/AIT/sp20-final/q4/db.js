const mongoose = require('mongoose');

const GenreSchema = new mongoose.Schema({
  name: String,    
  subGenres: [String]
});

mongoose.model('Genre', GenreSchema);
mongoose.connect('mongodb://localhost/sp20-ait');
