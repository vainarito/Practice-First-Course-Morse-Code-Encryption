#include"func.h"

const char* morse_table[] = {
 ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
 "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
 "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---",
 "...--", "....-", ".....", "-....", "--...", "---..", "----." };

void flash_morz(char* str)
{
	printf("Введите строку на азбуке Морзе: ");
	fgets(str, MAX_SIZE, stdin);
	str[strcspn(str, "\n")] = 0; // удаление символа новой строки
	bool valid_input = true;
	system("cls");
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] != '.' && str[i] != '-' && str[i] != ' ' && str[i] != '\n') {
			valid_input = false;
			break;
		}
	}
	while (!valid_input) {
		printf(ANSI_COLOR_RED"Ошибка!\n"ANSI_COLOR_RESET);
		printf("Введите только точки, тире и пробелы: ");
		fgets(str, MAX_SIZE, stdin);
		str[strcspn(str, "\n")] = 0; // удаление символа новой строки
		valid_input = true;
		system("cls");
		for (int i = 0; i < strlen(str); i++) {
			if (str[i] != '.' && str[i] != '-' && str[i] != ' ' && str[i] != '\n') {
				valid_input = false;
				break;
			}
		}
	}
	system("cls");
	char* text = morse_to_str(str);
	printf(ANSI_COLOR_YELLOW"Расшифровка: %s\n"ANSI_COLOR_RESET, text);
	free(text);
}

void choose_file_option(char* filename, bool* file_exists) {
	system("cls");
	int file_choice;
	printf("1. Создать новый файл\n");
	printf("2. Открыть существующий файл\n");
	printf("3. Выход в меню\n");
	printf(ANSI_COLOR_YELLOW"Введите свой выбор: "ANSI_COLOR_RESET);
	while (!scanf("%d", &file_choice) || getchar() != '\n' || file_choice < 0 || file_choice > 3)
	{
		system("cls");
		printf(ANSI_COLOR_RED"Ошибка ввода!\n"ANSI_COLOR_RESET);
		printf("1. Создать новый файл\n");
		printf("2. Открыть существующий файл\n");
		printf("3. Выход в меню\n");
		printf(ANSI_COLOR_YELLOW"Введите свой выбор: "ANSI_COLOR_RESET);
		rewind(stdin);
	}
	system("cls");
	if (file_choice == 1) {
		printf("Введите имя файла: ");
		scanf("%s", filename);
		strcat(filename, ".txt");
		FILE* file = fopen(filename, "w");
		if (file == NULL) {
			printf(ANSI_COLOR_RED"Ошибка при создании файла!\n"ANSI_COLOR_RESET);
		}
		else {
			fclose(file);
			*file_exists = true;
			system("cls");
			printf(ANSI_COLOR_YELLOW"Файл был успешно создан!\n"ANSI_COLOR_RESET);
		}
	}
	else if (file_choice == 2) {
		printf("Введите имя файла: ");
		scanf("%s", filename);
		strcat(filename, ".txt");
		FILE* file = fopen(filename, "r");
		if (file == NULL) {
			system("cls");
			printf(ANSI_COLOR_RED"Ошибка: файл не существует или его название неправильное!\n"ANSI_COLOR_RESET);
			*file_exists = false;
		}
		else {
			fclose(file);
			*file_exists = true;
			system("cls");
			printf(ANSI_COLOR_YELLOW"Файл был успешно открыт!\n"ANSI_COLOR_RESET);
		}
	}
	else if (file_choice == 3) {}

}

void morse_file_to_str(char* filename, bool file_exists) {
	system("cls");
	if (file_exists) {
		int choice;
		printf("1. Расшифровать весь файл\n");
		printf("2. Расшифровать одну строку\n");
		printf(ANSI_COLOR_YELLOW"Введите свой выбор: "ANSI_COLOR_RESET);
		while (!scanf("%d", &choice) || getchar() != '\n' || choice < 0 || choice > 2)
		{
			system("cls");
			printf(ANSI_COLOR_RED"Ошибка ввода!\n"ANSI_COLOR_RESET);
			printf("1. Расшифровать весь файл\n");
			printf("2. Расшифровать одну строку\n");
			printf(ANSI_COLOR_YELLOW"Введите свой выбор: "ANSI_COLOR_RESET);
			rewind(stdin);
		}
		system("cls");
		if (choice == 1) {
			// перевод всего файла
			printf(ANSI_COLOR_YELLOW"Расшифровка всего файла %s:\n"ANSI_COLOR_RESET, filename);
			FILE* file = fopen(filename, "r");
			char line[MAX_SIZE];
			while (fgets(line, MAX_SIZE, file) != NULL) {
				char* text = morse_to_str(line);
				printf("%s\n", text);
				free(text);
			}
			printf("\n");
			fclose(file);
		}
		else if (choice == 2) {
			// перевод одной строки
			display_file_contents(filename, file_exists);
			int line_number;
			printf(ANSI_COLOR_YELLOW"Введите номер строки: "ANSI_COLOR_RESET);

			FILE* file = fopen(filename, "r");
			int num_lines = 0;
			char line[MAX_SIZE];
			while (fgets(line, MAX_SIZE, file) != NULL) {
				num_lines++;
			}
			fclose(file);

			while (!scanf("%d", &line_number) || getchar() != '\n' || line_number < 1 || line_number > num_lines)
			{
				system("cls");
				display_file_contents(filename, file_exists);
				printf(ANSI_COLOR_RED"Ошибка ввода!\n"ANSI_COLOR_RESET);
				printf(ANSI_COLOR_YELLOW"Введите номер строки: "ANSI_COLOR_RESET);
				rewind(stdin);
			}

			system("cls");
			file = fopen(filename, "r");
			int current_line = 0;
			printf(ANSI_COLOR_YELLOW"Расшифровка строки %d из файла %s:\n"ANSI_COLOR_RESET, choice, filename);
			while (fgets(line, MAX_SIZE, file) != NULL) {
				current_line++;
				if (current_line == line_number) {
					char* text = morse_to_str(line);
					printf("%s\n", text);
					free(text);
					break;
				}
			}
			printf("\n");
			fclose(file);
		}
	}
	else {
		system("cls");
		printf(ANSI_COLOR_RED"Ошибка: файл не был открыт!\n"ANSI_COLOR_RESET);
	}

}

void run_program() {
	char str[MAX_SIZE];
	char filename[SIZE_NAME_FILE];
	int choice;
	bool file_exists = false;
	do
	{
		printf("Меню:\n");
		printf("1. Выбрать файл\n");
		printf("2. Преобразовать текст в азбуку Морзе\n");
		printf("3. Показать содержимое файла\n");
		printf("4. Расшифровать содержимое файла\n");
		printf("5. Быстрая расшифровка сообшения с азбуки Морзе\n");
		printf("6. Выход\n");
		printf(ANSI_COLOR_YELLOW"Введите свой выбор: "ANSI_COLOR_RESET);
		choice = input_case();

		switch (choice)
		{
		case 1:
			choose_file_option(filename, &file_exists);
			break;
		case 2:
			convert_text_to_morse(str, filename, file_exists);
			break;
		case 3:
			display_file_contents(filename, file_exists);
			break;
		case 4:
			morse_file_to_str(filename, file_exists);
			break;
		case 5: // новый case для быстрой расшифровки
			flash_morz(str);
			break;
		case 6:
			printf("Выход...\n");
			break;

		default:
			system("cls");
			printf(ANSI_COLOR_RED"Неверный выбор!\n"ANSI_COLOR_RESET);
			break;
		}
	} while (choice != 6);
}

void convert_text_to_morse(char* str, char* filename, bool file_exists) {
	printf("Ведите строку: ");
	fgets(str, MAX_SIZE, stdin);
	//str[strcspn(str, "\n")] = '\0'; // удаление символа новой строки

	char* morse = str_to_morse(str);
	system("cls");
	printf(ANSI_COLOR_RED"Азбука Морзе: %s\n" ANSI_COLOR_RESET, morse);

	if (file_exists)
	{
		FILE* file = fopen(filename, "a"); // открытие файла для добавления данных
		time_t current_time = time(NULL);
		struct tm* local_time = localtime(&current_time);
		char timestamp[20];
		strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", local_time);
		fprintf(file, "%s [%s]\n", morse, timestamp); // запись строки и ее представления в азбуке Морзе в файл
		fclose(file); // закрытие файла
	}
	else
	{
		printf(ANSI_COLOR_RED"Текст не был никуда сохранён, так как не был открыт или создан файл!\n"ANSI_COLOR_RESET);
	}
}


void display_file_contents(char* filename, bool file_exists) {
	if (file_exists)
	{
		FILE* file = fopen(filename, "r");
		if (file == NULL)
		{
			system("cls");
			printf(ANSI_COLOR_RED"Ошибка при открытии файла!\n"ANSI_COLOR_RESET);
		}
		else
		{
			system("cls");
			printf(ANSI_COLOR_YELLOW"Содержимое файла %s:\n"ANSI_COLOR_RESET, filename);
			char line[MAX_SIZE];
			while (fgets(line, MAX_SIZE, file) != NULL)
			{
				printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, line);
			}
			fclose(file);
			printf("\n");
		}
	}
	else
	{
		system("cls");
		printf(ANSI_COLOR_RED"Ошибка: файл не был открыт!\n"ANSI_COLOR_RESET);
	}
}

int input_case()
{
	int value;
	while (!scanf("%d", &value) || getchar() != '\n')
	{
		system("cls");
		printf(ANSI_COLOR_RED"Ошибка ввода!\n"ANSI_COLOR_RESET);
		printf("Меню:\n");
		printf("1. Выбрать файл\n");
		printf("2. Преобразовать текст в азбуку Морзе\n");
		printf("3. Показать содержимое файла\n");
		printf("4. Расшифровать содержимое файла\n");
		printf("5. Быстрая расшифровка сообшения с азбуки Морзе\n");
		printf("6. Выход\n");
		printf(ANSI_COLOR_YELLOW"Введите свой выбор: "ANSI_COLOR_RESET);
		rewind(stdin);
	}
	return value;
}

//! функция для преобразования строки в азбуку Морзе
char* str_to_morse(const char* str)
{
	size_t len = strlen(str);
	//! выделение памяти для строки с преобразованными символами
	char* result = (char*)calloc(len * 5 + 1, sizeof(char));
	if (result == NULL)
	{
		printf("Ошибка выделения памяти!\n");
		exit(1);
	}

	result[0] = '\0'; // начальное значение строки
	for (size_t i = 0; i < len; i++)
	{
		char c = str[i];
		if (c == ' ')
		{
			strcat(result, " ");
			Sleep(2000); // пауза между словами
		}
		else if (c >= 'A' && c <= 'Z')
		{
			const char* morse = morse_table[c - 'A'];
			strcat(result, morse);
			for (size_t j = 0; j < strlen(morse); j++)
			{
				if (morse[j] == '.')
				{
					Beep(800, 150); // воспроизведение точки
				}
				else if (morse[j] == '-')
				{
					Beep(900, 300); // воспроизведение тире
				}
				Sleep(25); // пауза между символами
			}
			Sleep(1000); // пауза между буквами
			strcat(result, " ");
		}
		else if (c >= 'a' && c <= 'z')
		{
			const char* morse = morse_table[c - 'a'];
			strcat(result, morse);
			for (size_t j = 0; j < strlen(morse); j++)
			{
				if (morse[j] == '.')
				{
					Beep(800, 150); // воспроизведение точки
				}
				else if (morse[j] == '-')
				{
					Beep(900, 300); // воспроизведение тире
				}
				Sleep(25); // пауза между символами
			}
			Sleep(1000); // пауза между буквами
			strcat(result, " ");
		}
		else if (c >= '0' && c <= '9')
		{
			const char* morse = morse_table[c - '0' + 26];
			strcat(result, morse);
			for (size_t j = 0; j < strlen(morse); j++)
			{
				if (morse[j] == '.')
				{
					Beep(800, 150); // воспроизведение точки
				}
				else if (morse[j] == '-')
				{
					Beep(900, 300); // воспроизведение тире
				}
				Sleep(25); // пауза между символами
			}
			Sleep(100); // пауза между буквами
			strcat(result, " ");
		}
	}
	return result;
}

char* morse_to_str(const char* morse) {
	size_t len = strlen(morse);
	char* result = (char*)calloc(len + 1, sizeof(char));
	if (result == NULL) {
		printf("Ошибка выделения памяти!\n");
		exit(1);
	}

	result[0] = '\0'; // начальное значение строки
	size_t i = 0;
	while (i < len) {
		if (morse[i] == ' ') {
			strcat(result, " ");
			i++;
		}
		else {
			size_t j = i;
			while (j < len && morse[j] != ' ') {
				j++;
			}
			char symbol[MAX_SIZE];
			strncpy(symbol, morse + i, j - i);
			symbol[j - i] = '\0';
			for (int k = 0; k < 36; k++) {
				if (strcmp(morse_table[k], symbol) == 0) {
					if (k < 26) {
						char c = 'A' + k;
						strncat(result, &c, 1);
					}
					else {
						char c = '0' + k - 26;
						strncat(result, &c, 1);
					}
					break;
				}
			}
			i = j;
		}
	}

	return result;
}
