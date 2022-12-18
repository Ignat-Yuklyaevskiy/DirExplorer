#include "DirectoryMenu.h"

/**
 *  TODO
 *  +1. Наследование
 *  2. Исключения
 *  -3. Класс Command ?
 *  +4. Класс Menu (Обычное меню, Меню директорий)
 *  +5. Работа с датой (Фильтрация по дате)
 *  +6. Дубликаты
 *  +-7. Обработка кнопок в разных меню
 */

int main()
{
	setlocale(0, "RU");
	bool isRun = true;
	vector<string> menuItems{ "Ввод директории", "Выбор директории", "Справка" };
	string input;
	while (isRun)
	{
		pair<int, CommandState> command = TextMenu(menuItems, "Главное меню").Start();
		if (command.second == Exit)
			break;
		switch (command.first)
		{
		case 0:
			cout << ">";
			getline(std::cin, input);
			DirectoryMenu(new Directory(input)).PathHandle();
			break;
		case 1:
			DirectoryMenu(new Directory("")).Start();
			break;
		case 2:
			cout << "Right    - переход в директорию" << endl;
			cout << "Left     - выход из директории" << endl;
			cout << "Up, Down - перемещение по меню" << endl;
			cout << "Enter    - выбор директории для анализа" << endl;
			cout << "Esc      - возврат в предыдущее меню" << endl;
			std::system("PAUSE");
			break;
		}
	}

	return 0;
}
