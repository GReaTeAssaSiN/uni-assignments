#include "MovieTableDBElement.h"

MovieTableDBElement::MovieTableDBElement(SqlDataReader^ reader)
{
	MovieID = reader->GetInt32(0);
	MovieName = reader->GetString(1);
	Release = reader->GetDateTime(2);
	Genre = reader->GetString(3);
	(AgeLimit = reader->IsDBNull(4) ? "0+" : reader->GetString(4));
	Duration = reader->GetTimeSpan(5);
	(MovieFormat = reader->IsDBNull(6) ? "2D" : reader->GetString(6));
}
Int32^ MovieTableDBElement::getMovieID()
{
	return this->MovieID;
}
String^ MovieTableDBElement::getMovieName()
{
	return this->MovieName;
}
DateTime^ MovieTableDBElement::getRelease()
{
	return this->Release;
}
String^ MovieTableDBElement::getGenre()
{
	return this->Genre;
}
String^ MovieTableDBElement::getAgeLimit()
{
	return this->AgeLimit;
}
TimeSpan^ MovieTableDBElement::getDuration()
{
	return this->Duration;
}
String^ MovieTableDBElement::getMovieFormat()
{
	return this->MovieFormat;
}