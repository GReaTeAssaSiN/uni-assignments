#ifndef MYFUNCS_H_
#define MYFUNCS_H_

/*ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ*/
void MenuForChoices();
char GetCase();

/*ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ*/
void HorizontalLineForModel(const int& col_width);
std::string CenterText(const std::string& text, const int& width);
std::string AccessLevelToString(const int& access);
int AccessLevelToValue(const std::string& access);
void DrawLine();
int FindSubject(const std::vector<std::string> subjects, const std::string subject_name);
int FindObject(const std::vector<std::string> objects, const std::string object_name);

/*ОСНОВНЫЕ ФУНКЦИИ*/
void DisplayModelBLM(const std::vector<std::string>& subjects, const std::vector<std::string>& objects,
	const std::vector<int>& subjects_level_access, const std::vector<int>& objects_level_access);
void GenerateModelBLM(std::vector<int>& subjects_level_access, std::vector<int>& objects_level_access);
int EnterTheProgram(const std::vector<std::string>& subjects);
bool CheckNRU(const int& subject_level_access, const int& object_level_access);
bool CheckNWD(const int& subject_level_access, const int& object_level_access);
void ReadTheObjectBySubject(const int& subject_level_access, const std::vector<std::string>& objects, const std::vector<int>& objects_level_access);
void WriteToObjectBySubject(const int& subject_level_access, const std::vector<std::string>& objects, const std::vector<int>& objects_level_access);
void ChangeLevelAccessBySubject(const std::vector<int>& COPY_subjects_level_access, std::vector<int>& subjects_level_access, const int& subject_index);

#endif /*MYFUNCS_H_*/