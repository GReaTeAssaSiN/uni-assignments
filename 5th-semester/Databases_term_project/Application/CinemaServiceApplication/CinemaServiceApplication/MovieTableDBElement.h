#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class MovieTableDBElement
{
	private: Int32^ MovieID{};
	private: String^ MovieName{};
	private: DateTime^ Release{};
	private: String^ Genre{};
	private: String^ AgeLimit{};
	private: TimeSpan^ Duration{};
	private: String^ MovieFormat{};
	public: MovieTableDBElement(SqlDataReader^ reader);
	public: Int32^ getMovieID();
	public: String^ getMovieName();
	public: DateTime^ getRelease();
	public: String^ getGenre();
	public: String^ getAgeLimit();
	public: TimeSpan^ getDuration();
	public: String^ getMovieFormat();
};

