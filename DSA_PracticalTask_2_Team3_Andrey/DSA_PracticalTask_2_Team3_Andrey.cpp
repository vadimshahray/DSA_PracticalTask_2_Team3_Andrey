#include <conio.h>
#include <stdio.h>
#include <windows.h>

// Максимальное кол-во элементов в деке.
const UCHAR N = 4;

// Команды консольного меню.
enum COMMAND
{
   PUSH_FRONT,  // Добавить элемент в начало дека.
   PUSH_BACK,   // Добавить элемент в конец дека.
   POP_FRONT,   // Вытолкнуть элемент из начала дека.
   POP_BACK,    // Вытолкнуть элемент из конца дека.
   EMPTY,       // Проверить, пуст ли дек.
   FULL,        // Проверить, полон ли дек.
   CLEAR,       // Очистить дек.
   PRINT,       // Вывести все элементы дека на консоль.
   EXIT         // Завершить выполнение программы.
};


struct deck
{
   private:
   char beg = -1, end = -1, data[N] = { };

   public:
   /// <summary>
   /// Добавляет элемент e в начало дека.
   /// </summary>
   /// <param name="e">Элемент, который нужно добавить.</param>
   /// <returns>Выполнилась ли операция.</returns>
   bool push_front(char e)
   {
      bool is_f = full(), is_e = empty();
      if (!is_f)
      {
         beg = is_e ? end = N - 1 : beg == 0 ? N - 1 : beg - 1;
         data[beg] = e;
      }

      return !is_f;
   }
   /// <summary>
   /// Добавляет элемент e в конец дека.
   /// </summary>
   /// <param name="e">Элемент, который нужно добавить.</param>
   /// <returns>Выполнилась ли операция.</returns>
   bool push_back(char e)
   {
      bool is_f = full(), is_e = empty();
      if (!is_f)
      {
         end = is_e ? beg = 0 : end == N - 1 ? 0 : end + 1;
         data[end] = e;
      }

      return !is_f;
   }
   /// <summary>
   /// Выталкивет элемент из начала дека и передает его в e.
   /// </summary>
   /// <param name="e">Куда передать вытолкнутый элемент.</param>
   /// <returns>Выполнилась ли операция.</returns>
   bool pop_front(char &e)
   {
      bool is_e = empty(), will_e = beg == end;
      if (!is_e)
      {
         e = data[beg];
         beg = will_e ? end = -1 : beg == N - 1 ? 0 : beg + 1;
      }

      return !is_e;
   }
   /// <summary>
   /// Выталкивет элемент из начала дека и передает его в e.
   /// </summary>
   /// <param name="e">Куда передать вытолкнутый элемент.</param>
   /// <returns>Выполнилась ли операция.</returns>
   bool pop_back(char &e)
   {
      bool is_e = empty(), will_e = beg == end;
      if (!is_e)
      {
         e = data[end];
         end = will_e ? beg = -1 : end == 0 ? end = N - 1 : end - 1;
      }

      return !is_e;
   }

   /// <summary>
   /// Проверяет, пуст ли дек.
   /// </summary>
   bool empty() { return beg == -1; }
   /// <summary>
   /// Проверяет, полон ли дек.
   /// </summary>
   bool full() { return beg - end == 1 || end - beg == N - 1; }
   
   /// <summary>
   /// Очищает дек.
   /// </summary>
   void clear() { for (char e = 0; pop_front(e); ); }
   /// <summary>
   /// Выводит элементы дека на консоль.
   /// </summary>
   void print()
   {
      deck d;
      char e = 0;

      for ( ; pop_front(e); d.push_back(e)) printf_s("%c ", e);
      for ( ; d.pop_front(e); push_back(e));
   }
};


int main()
{
   UINT iCp = GetConsoleCP(), oCp = GetConsoleOutputCP();
   SetConsoleCP(1251);
   SetConsoleOutputCP(1251);

   deck d;
   bool repeat = true;
   char cmd = 0, elem = 0;
   do
   {
      printf_s("Выберите команду:\n[%d] Добавить элемент в начало дека;\n[%d] Добавить элемент в конец дека;\n[%d] Вытолкнуть элемент из начала дека;\n[%d] Вытолкнуть элемент из конца дека;\n[%d] Проверить, пуст ли дек;\n[%d] Проверить, полон ли дек;\n[%d] Очистить дек;\n[%d] Вывести содержимое дека;\n[%d] Завершить работу.\nКоманда: ", PUSH_FRONT, PUSH_BACK, POP_FRONT, POP_BACK, EMPTY, FULL, CLEAR, PRINT, EXIT);

      scanf_s("\n%c", &cmd, 1);
      printf_s("\n");

      switch (cmd - '0')
      {
         case PUSH_FRONT:
            printf_s("Введите элемент: ");
            scanf_s("\n%c", &elem, 1);

            printf_s(d.push_front(elem) ? "Элемент успешно добавлен."
                                        : "Не удалось добавить элемент: стек полон."); break;
         case PUSH_BACK:
            printf_s("Введите элемент: ");
            scanf_s("\n%c", &elem, 1);

            printf_s(d.push_back(elem) ? "Элемент успешно добавлен." 
                                       : "Не удалось добавить элемент: стек полон."); break;
         case POP_FRONT:
            d.pop_front(elem) ? printf_s("Вытолкнутый элемент: %c", elem)
                              : printf_s("Не удалось выполнить данную операцию: стек пуст."); break;
         case POP_BACK:
            d.pop_back(elem) ? printf_s("Вытолкнутый элемент: %c", elem) 
                             : printf_s("Не удалось выполнить данную операцию: стек пуст."); break;
         case EMPTY:
            printf_s(d.empty() ? "Дек пуст." : "Дек не пуст."); break;
         case FULL:
            printf_s(d.full() ? "Дек полон." : "Дек не полон."); break;
         case CLEAR:
            d.clear();
            printf_s("Дек очищен."); break;
         case PRINT:
            printf_s("Содержимое дека:\n");
            d.print(); break;
         case EXIT:
            repeat = false; break;
         default:
            printf_s("Неверный номер команды."); break;
      }
      printf_s("\n\n");
   } while(repeat);

   SetConsoleCP(iCp);
   SetConsoleOutputCP(oCp);

   return 0 * _getch();
}