#include "ReviewTableDBElement.h"

	ReviewTableDBElement::ReviewTableDBElement(SqlDataReader^ reader)
	{
		UserLogin = reader->GetString(0);
		CommentDateTime = reader->GetDateTime(1);
		CinemaName = reader->GetString(2);
		MovieName = reader->GetString(3);
		TranscriptPicture = (array<Byte>^)reader->GetSqlBinary(4);
		Comment = reader->GetString(5);
	}
	String^ ReviewTableDBElement::getUserLogin()
	{
		return this->UserLogin;
	}
	DateTime^ ReviewTableDBElement::getCommentDateTime()
	{
		return this->CommentDateTime;
	}
	String^ ReviewTableDBElement::getCinemaName()
	{
		return this->CinemaName;
	}
	String^ ReviewTableDBElement::getMovieName()
	{
		return this->MovieName;
	}
	array<Byte>^ ReviewTableDBElement::getTranscriptPicture()
	{
		return this->TranscriptPicture;
	}
	String^ ReviewTableDBElement::getComment()
	{
		return this->Comment;
	}