create table book (
  isbn    text not null primary key,
  title   text not null,
  author  text not null,
  price   decimal(10,2) not null
);

create table custorder (
  id      serial not null primary key,
  name    text not null,
  street  text not null,
  city    text not null
);

create table custorderitem (
  custorderid int not null,
  isbn    text not null,
  amount  int not null,
  primary key (custorderid, isbn),
  foreign key (custorderid) references custorder,
  foreign key (isbn) references book
);
