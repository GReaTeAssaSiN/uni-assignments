#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class ReviewTableDBElement
{
	private: String^ UserLogin{};
	private: DateTime^ CommentDateTime{};
	private: String^ CinemaName{};
	private: String^ MovieName{};
	private: array<Byte>^ TranscriptPicture{};
	private: String^ Comment{};
	public: ReviewTableDBElement(SqlDataReader^ reader);
	public: String^ getUserLogin();
	public: DateTime^ getCommentDateTime();
	public: String^ getCinemaName();
	public: String^ getMovieName();
	public: array<Byte>^ getTranscriptPicture();
	public: String^ getComment();
};

