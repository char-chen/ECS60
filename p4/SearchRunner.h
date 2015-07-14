// Author: Sean Davis

#ifndef SEARCHRUNNER_H
#define	SEARCHRUNNER_H

class Song
{
public:
  char title[68];
  char artist[26];
  char ID[11];
  char album[36];
};

class Answer
{
public:
  int length;
  int count;
};

class Request
{
public:
  int type;
  char criteria[68];
  char criteria2[68];
};
#endif	/* SEARCHRUNNER_H */

