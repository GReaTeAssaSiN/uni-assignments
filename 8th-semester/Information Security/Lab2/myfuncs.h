#ifndef MYFUNCS_H_
#define MYFUNCS_H_

/*ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ*/
void MenuForChoices();
char getCase();
void SubMenuForChoices(const std::string& object_name);
char getSubmenuCase(const std::string& object_name);

/*ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ*/
void horizontal_table_line(const int& col_width, const std::vector<std::string>& objects);
std::string center_text(const std::string& text, const int& width);
std::string access_level_to_string(const int& access);
void draw_line();
int find_subject(const std::vector<std::string> subjects, const std::string subject_name);
int find_object(const std::vector<std::string> objects, const std::string object_name);

/*ОСНОВНЫЕ ФУНКЦИИ*/
void display_table(const std::vector<std::string> subjects, const std::vector<std::string>& objects, const std::vector<std::vector<int>>& access_matrix);
void generate_access_matrix(std::vector<std::vector<int>>& access_matrix);
int enter_the_program(const std::vector<std::string>& subjects);
void display_subject_permissions(const int& subject_index, const std::vector<std::string>& objects, const std::vector<std::vector<int>>& access_matrix);
void file_choice(const int& subject_index, const std::vector<std::string>& subjects, const std::vector<std::string>& objects,
	std::vector<std::vector<int>>& access_matrix);
bool file_interract(const int& subject_index, const int& object_index, const std::vector<std::string>& subjects, const std::vector<std::string>& objects,
	std::vector<std::vector<int>>& access_matrix);
bool check_permission(const std::vector<std::vector<int>>& access_matrix, const int& subject_index, const int& object_index, const int& bit);
void modify_access_matrix(const std::vector<std::string>& subjects, const int& target_object_index, std::vector<std::vector<int>>& access_matrix, const int& subject_index);
#endif /* MYFUCNCS_H_*/