---Sources I pulled the data from: https://www.billboard.com/charts/top-album-sales
--------https://www.billboard.com/charts/hot-100
--------https://www.billboard.com/charts/artist-100

-- Question 1: Two queries using inner joins, one explicit and one implicit
--- explicit inner join: Shows artists who songs and albums in the top 20. Shows the weekly charting position of both the song and album
SELECT al.name as album, s.name AS song, s.artistName, s.position AS songPosition, al.position AS albumPosition FROM albums al INNER JOIN songs s ON s.artistName = al.artist ORDER BY s.position;
---implicit inner join shows artists ranked top 15 who also have songs in the top 20
SELECT s.name AS song, a.name, a.position as artistRanking, s.position AS songRanking FROM songs s, artists a WHERE s.artistName = a.name HAVING a.position > 0 ORDER BY artistRanking;

-- Question 2: two queries using left joins
---Left join to display artists in the weekly top 20 and whether or not they have songs in the top 20
---NULL results in the artistName column means that the artist does not have a song in the top 20
---the a.position > 0 limits the query to include just the weekly top 20 artists, since the table includes all artists mentioned in the dataset
SELECT a.name, s.artistName FROM artists a LEFT JOIN songs s ON a.name = s.artistName WHERE a.position > 0;
---Left join to display artists with top 20 albums who do not have top 20 songs
SELECT al.artist, s.artistName, al.name as albumName FROM albums al LEFT JOIN songs s on al.artist = s.artistName WHERE s.artistName IS NULL;

-- Question 3: 3 queries with any sort of nested or sub queries
---First subquery: SELECT AVG(duration) FROM songs;
---Shows top 20 songs with a higher than average (from this same) duration on billboard hot 100 list
SELECT s.artistName, s.name, s.duration FROM songs s WHERE s.duration > (SELECT AVG(duration) FROM songs) ORDER BY s.duration DESC;
--Second nested subquery: To identify songs that have gone up the charts
---SELECT s.artistName FROM songs s WHERE s.lastWeek > s.position;
---Query lists artists who climbed up the charts and also have an album in the top 20
SELECT al.artist FROM albums al WHERE al.artist IN (SELECT s.artistName FROM songs s WHERE s.lastWeek > s.position);
--Third nested query: SELECT al.artist FROM albums al INNER JOIN songs s ON s.artistName = al.artist
---Shows artists ranked in top 15 also ranked with top 20 songs and top 20 albums
SELECT a.name FROM artists a WHERE a.name IN (SELECT al.artist FROM albums al INNER JOIN songs s ON s.artistName = al.artist);

-- Question 4: Two inner joins
--- displays information about artists with top 20 songs who also are ranked as top 15 artists and have a top 20 album
SELECT a.name AS artist, s.name AS song, s.position, al.name AS album FROM songs s INNER JOIN artists a ON s.artistName = a.name INNER JOIN albums al ON s.artistName = al.artist WHERE a.position > 0;

-- Question 5: Two additional queries of choice
--- Inner join query to display top 15 artists that have a song in the top 20 that peaked at #1
--SELECT s.artistName FROM songs s WHERE peak = 1;
SELECT a.name FROM artists a INNER JOIN songs s ON a.name = s.artistName WHERE a.name IN (SELECT s.artistName FROM songs s WHERE peak = 1) AND a.position > 0;

---This query is a right join to highlight if songs with artists not in the artists table
SELECT s.artistName FROM songs s RIGHT JOIN artists a ON s.artistName = a.name WHERE a.name IS NULL;

----EXTRA CREDIT----
---- 1. ---- Do artists tend to fall near the same place on top charts? 
SELECT a.name, a.position AS artistRanking, s.position AS songRanking, al.position AS albumRANKING FROM artists a, songs s, albums al WHERE a.name = s.artistName AND a.name = al.artist ORDER BY a.position;
---- 2. ---- Do songs that are on the charts longer tend to have lower rankings?
SELECT name, position, lastWeek, duration FROM songs ORDER BY duration;
--Note: No correlation noted just by looking at the data. I think future statistics could actually answer this.
--- 3. ---- What is the average jump for songs withing a week?
SELECT AVG(ABS(s.peak - s.position)) FROM songs s;
-- And then the data for every song
SELECT s.artistName, s.name, ABS(s.peak - s.position) AS jump FROM songs s;







