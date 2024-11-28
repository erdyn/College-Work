/*
Title: Photo-sharing app database, Week 5 and 9 work

Date: October/November 2024

Author: Susanna Perkins
*/

-- Drop tables in case they exist so that I can create tables with those names
drop table if exists follow;
drop table if exists likes;
drop table if exists photos;
drop table if exists users;

-- Creating tables

-- Users
create table users(
    user_identification serial primary key, 
    username char(30) unique not null, 
    created_at date
);

-- Photos
create table photos(
    photo_identification serial primary key, 
    image_url varchar(50),
    user_identification integer,
    publication_date date,
    constraint photos_users_fk foreign key (user_identification) references users (user_identification)
);

-- Likes
create table likes(
    user_identification integer,
    photo_identification integer,
    date_of_like date, 
    constraint likes_users_fk foreign key (user_identification) references users (user_identification),
    constraint likes_photos_fk foreign key (photo_identification) references photos (photo_identification),
    primary key (user_identification, photo_identification)
);

-- Follows
create table follow(
    follower_id integer,
    followee_id integer,
    date_of_follow timestamp,
    constraint follower_id_fk foreign key (follower_id) references users (user_identification),
    constraint followee_id_fk foreign key (followee_id) references users (user_identification),
    primary key (follower_id, followee_id)
);

-- Populating users table
insert into users(username, created_at)
values
('Justy', '2024-09-24'),
('Clarence Navarro', '2024-09-23'),
('htlqvc', '2024-09-22'),
('quinners', '2024-09-21'),
('j.ptaxil', '2024-09-20'),
('Roda', '2021-09-18'),
('Chicky', '2022-10-02'),
('Gui', '2020-09-17'),
('Lurleen', '2019-09-17'),
('Pearl', '2022-09-29'),
('Guillema', '2022-09-29'),
('Iolanthe', '2021-09-29'),
('Kasper', '2022-09-29'),
('Roddie', '2022-09-29'),
('Saunder', '2022-10-29'),
('Zenith', '2024-09-19'),
('Fern', '2024-09-18'),
('Arielle', '2024-09-17'),
('Ezekiel', '2024-09-16'),
('Milo', '2024-09-15'),
('Claudine', '2023-09-25'),
('Jude', null),
('Astrid', '2023-09-23'),
('Leopold', '2023-09-22'),
('Marcellus', '2023-09-21');

-- Populating photos table with user_identification
insert into photos(image_url, user_identification, publication_date)
values
('www.justin.com', 1, '2022-09-24'),
('www.clarence.com', 2, '2022-09-23'),
('www.bella.com', 3, '2022-09-22'),
('www.cillian.com', 4, '2022-09-21'),
('www.john.com', 5, '2022-09-20'),
('www.Roda.com', 6, '2023-11-04'),
('www.Chicky.com', 7, '2024-03-05'),
('www.Gui.com', 8, '2024-03-05'),
('www.Lurleen.com', 9, '2024-03-17'),
('www.Pearl.com', 10, '2024-09-27'),
('www.Guillema.com', 11, '2023-10-19'),
('www.Iolanthe.com', 12, '2023-10-19'),
('www.Kasper.com', 13, '2024-03-05'),
('www.Roddie.com', 14, '2023-10-19'),
('www.Saunder.com', 15, '2023-10-19'),
('www.Zenith.com', 16, '2024-09-19'),
('www.Fern.com', 17, '2024-09-18'),
('www.Arielle.com', 18, '2024-09-17'),
('www.Ezekiel.com', 19, '2024-09-16'),
('www.Milo.com', 20, '2024-09-15'),
('www.Claudine.com', 21, '2023-09-25'),
('www.Jude.com', 22, null),
('www.Jude2.com', 22, '2023-09-23'),
('www.Leopold.com', 24, null),
('www.Leopold2.com', 24, '2023-09-21');

-- Populating likes table with user_identification and photo_identification
insert into likes(user_identification, photo_identification, date_of_like)
values
(1, 3, '2023-09-24'),
(1, 4, '2023-09-23'),
(3, 4, '2023-09-22'),
(4, 4, '2023-09-21'),
(5, 6, '2023-09-20'),
(6, 7, '2023-11-04'),
(7, 8, '2023-06-01'),
(8, 9, '2023-11-23'),
(9, 10, '2023-10-04'),
(10, 11, '2023-01-28'),
(11, 12, '2023-11-03'),
(12, 13, '2023-11-04'),
(13, 14, '2023-10-08'),
(14, 15, '2023-11-04'),
(15, 16, '2023-09-16'),
(16, 17, '2023-09-15'),
(17, 18, '2023-09-14'),
(18, 19, '2023-09-13'),
(19, 20, '2023-09-12'),
(20, 21, '2023-09-11'),
(21, 22, null),
(22, 23, '2023-08-19'),
(23, 24, '2023-08-18'),
(24, 25, '2023-08-17'),
(25, 1, '2023-08-16');

-- Populating follow table with follower_id and followee_id
insert into follow(follower_id, followee_id, date_of_follow)
values
(1, 2, '2023-09-24 12:12:10'),
(2, 3, '2023-09-23 11:12:11'),
(3, 4, '2023-09-22 10:12:12'),
(4, 5, '2023-09-21 08:59:16'),
(5, 6, '2023-09-20 12:12:18'),
(6, 7, '2023-11-04 09:12:20'),
(7, 8, '2023-06-01 07:12:34'),
(8, 9, '2023-11-23 12:12:50'),
(9, 10, '2023-10-04 12:07:48'),
(10, 11, '2023-01-28 12:12:50'),
(11, 12, '2023-11-03 07:32:59'),
(12, 13, '2023-11-04 12:12:11'),
(13, 14, '2023-10-08 09:12:12'),
(14, 15, '2023-11-04 10:12:01'),
(15, 16, '2023-09-16 11:12:06'),
(16, 17, null),
(17, 18, '2023-09-14 11:10:14'),
(18, 19, '2023-09-13 09:45:32'),
(19, 20, '2023-09-12 12:20:18'),
(20, 21, '2023-09-11 13:32:45'),
(21, 22, '2023-08-20 07:25:33'),
(22, 23, '2023-08-19 08:10:55'),
(23, 24, '2023-08-18 09:15:22'),
(24, 25, '2023-08-17 11:22:13'),
(25, 1, '2023-08-16 12:18:44');

-- Show tables
select * from users;
select * from photos;
select * from likes;
select * from follow;


-- Week 5 Queries

-- Q1 Usernames with followers
select u.username as "Users with followers"
from users u
join follow f on u.user_identification = f.followee_id;

-- Q2 Image url photos liked by user: Justy
select p.image_url as "image_url of photos liked by Justy"
from photos p
join likes l on p.photo_identification = l.photo_identification
where l.user_identification = (select user_identification from users where username = 'Justy');

-- Q3 Users who have not posted any photos
select u.username as "Users with no posted photos"
from users u
left join photos p on u.user_identification = p.user_identification
where p.photo_identification is null;

-- Q4 Users who have liked their own photos
select u.username as "Users who have liked their own photos"
from users u
join photos p on u.user_identification = p.user_identification
join likes l on p.photo_identification = l.photo_identification
where u.user_identification = l.user_identification;

-- Q5 Users who have posted photos but have not received any likes
select u.username as "Users who have posted but received no likes"
from users u
join photos p on u.user_identification = p.user_identification
left join likes l on p.photo_identification = l.photo_identification
where l.photo_identification is null;

-- Q6 Users who have posted photos and received likes
select distinct u.username as "Users who have received likes"
from users u
join photos p on u.user_identification = p.user_identification
join likes l on p.photo_identification = l.photo_identification;

-- Q7 Usernames with more than 10 chars
select username as "Usernames containing more than 10 characters"
from users
where length(username) > 10;

-- Q8 Usernames ending with the letter 'n'
select username as "Usernames ending in 'n' "
from users
where username like '%n';

-- Q9 Replace values in the username attribute
select replace(username, ' ', '_') as modified_username
from users;


-- Week 9 Queries

-- Quesion 1: Write a query to select the username and the number of photos published by each user. 
-- Display the result in two columns: "Username" and "Number of photos". Order the result by the number of photos in descending order.
select u.username, count(photos) as "Number of photos"
from users u
left join photos on u.user_identification = photos.user_identification
group by u.username
order by "Number of photos" desc;


-- Question 2: Find the total number of likes received for each photo. Display the photo_id and the corresponding number of likes. 
-- Order the result by the number of likes in descending order.
select p.photo_identification, count(l) as "Number of likes"
from photos p
left join likes l on p.photo_identification = l.photo_identification
group by p.photo_identification
order by "Number of likes" desc;



-- Question 3: Identify the user who has posted the earliest photo. Display their username and the date of the earliest photo. 
-- Display the date in the format DD/MM/YYYY
select u.username, to_char(p.publication_date, 'DD/MM/YYYY') as "Earliest_Photo_Publication_Date"
from users u join photos p
on u.user_identification = p.user_identification
where p.publication_date = (select min(publication_date) from photos);


-- Week 10 Queiries

-- INDEX Q1
-- Compare: without Index
explain analyze
select * from users where username = 'Marcellus';


-- Create index: users.username
drop index if exists users_username_ind;
create index users_username_ind on users(username);

-- Compare with Index
explain analyze
select * from users where username = 'Marcellus';

-- Because this is a small amount of data the difference doesn't represent how index scan differs


-- INDEX Q2
-- photos publication date desc
explain analyze
select * from photos order by publication_date desc ;

-- index: photos.publication_date
drop index if exists photos_date_ind;
create index photos_date on photos(publication_date);

-- w index
explain analyze
select * from photos order by publication_date desc;
-- SETS Q1
-- Select all the userIDs that appear in both the likes and follow table
select likes.user_identification
from likes
intersect
select follow.follower_id
from follow
union
select follow.followee_id
from follow;


