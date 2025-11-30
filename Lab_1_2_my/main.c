#include <stdio.h>  // Бібліотека для стандартного вводу/виводу: printf(), scanf()
#include <stdlib.h> // Бібліотека з утилітами, включає функцію system()

// Макровизначення (константи), які вставляються в код при компіляції
#define Name "Yaroslav" // Ім’я студента
#define LastName "Marchuk" // Прізвище студента
#define GroupName "RI-p51" // Назва академічної групи
#define Faculty "RTF" // Назва факультету
#define University "Igor Sikorsky Kyiv Polytechnic Institute" // Назва університету

// Точка входу в програму — функція main()
int main()
{
    // -------------------- Оголошення змінних --------------------
    unsigned int semestr;       // Зберігає номер семестру (тільки позитивні значення)
    float admissionScore;       // Зберігає вступний бал (може бути дробовим)
    int grade1, grade2, grade3; // Зберігає три оцінки
    double averageGrade;        // Середнє значення оцінок (тип double — більша точність)
    unsigned int age;           // Вік студента (тільки позитивне ціле число)

    // -------------------- Введення даних від користувача --------------------

    // Виводимо на екран ім’я та прізвище, та запитуємо подальші дані
    printf("%s %s Enter following data.\n", Name, LastName);

    // Запитуємо номер семестру
    printf("Enter semestr: ");
    scanf("%u", &semestr); // %u — формат для unsigned int (ціле без знаку)

    // Запитуємо вступний бал
    printf("Enter your admission score: ");
    scanf("%f", &admissionScore); // %f — формат для float

    // Запитуємо три оцінки
    printf("Enter grade #1: ");
    scanf("%d", &grade1); // %d — формат для int

    printf("Enter grade #2: ");
    scanf("%d", &grade2);

    printf("Enter grade #3: ");
    scanf("%d", &grade3);

    // Запитуємо вік
    printf("Enter your age: ");
    scanf("%u", &age); // Знову ж таки, %u — формат для unsigned int

    // -------------------- Обробка даних --------------------

    // Обчислення середньої оцінки:
    // Спочатку сума трьох оцінок (grade1 + grade2 + grade3)
    // Потім ділення на 3, перетворене до типу double для точності
    averageGrade = (double)(grade1 + grade2 + grade3) / 3;

    // -------------------- Виведення результату --------------------

    // Очищення екрану (команда system викликає команду ОС)
    // На Windows працює "cls", на Linux/macOS треба використовувати "clear"
    system("cls");

    // Вивід основної інформації
    printf("%s", University);         // Виводимо назву університету
    printf("\n%s", Faculty);          // Виводимо факультет
    printf("\n%s", GroupName);        // Виводимо групу

    // Вивід лінії для поділу інформації
    printf("\n---------------------------");

    // Виводимо ім’я та прізвище студента
    printf("\nstudent: %s %s", Name, LastName);

    // Виводимо вік і семестр
    printf("\nage: %u", age);
    printf("\nsemestr: %u", semestr);

    // Знову лінія для розділення
    printf("\n---------------------------");

    // Виводимо вступний бал (з точністю до 2 знаків після коми)
    printf("\nadmission score: %.2f", admissionScore);

    // Виводимо середню оцінку (з точністю до 3 знаків після коми)
    printf("\naverage grade = %.3lf", averageGrade);

    // Завершення рядка
    printf("\n");

    // -------------------- Завершення програми --------------------
    return 0; // Повертаємо 0 — сигналізує успішне завершення програми
}
