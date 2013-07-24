create table book (
  isbn    text not null primary key,
  title   text not null,
  author  text not null,
  price   decimal(10,2) not null
);
