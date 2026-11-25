#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TASKS 100
#define MAX_TITLE_LEN 128
#define FILENAME "tasks.dat"

typedef struct {
    int id;
    char title[MAX_TITLE_LEN];
    int priority; // 1 - Низкий, 2 - Средний, 3 - Высокий
    bool completed;
} Task;

typedef struct {
    Task items[MAX_TASKS];
    int count;
    int next_id;
} TaskManager;

// Прототипы функций
void manager_init(TaskManager *tm);
void clear_input_buffer(void);
void print_menu(void);
void toggle_task(TaskManager *tm);
void delete_task(TaskManager *tm);
void save_tasks(const TaskManager *tm);
void load_tasks(TaskManager *tm);
const char* get_priority_str(int priority);

int main(void) {
    TaskManager tm;
    manager_init(&tm);
    load_tasks(&tm);

    int choice = 0;
    printf("=== Менеджер задач на C ===\n");

    while (true) {
        print_menu();
        printf("Выберите действие: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка: введите число.\n");
            clear_input_buffer();
            continue;
        }
        printf("123\n");
        clear_input_buffer();

        switch (choice) {
            case 1:
                add_task(&tm);
                break;
            case 2:
                list_tasks(&tm);
                break;
            case 3:
                toggle_task(&tm);
                break;

            case 5:
                save_tasks(&tm);
                break;
            case 0:
                save_tasks(&tm);
                printf("Выход из программы. До свидания!\n");
                return 0;
            default:
                printf("Неверный пункт меню. Попробуйте снова.\n");
        }
    }

    return 0;
}

void manager_init(TaskManager *tm) {
    tm->count = 0;
    tm->next_id = 1;
}

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Очистка буфера ввода
    }
}

void print_menu(void) {
    printf("\n--- МЕНЮ ---\n");
    printf("1. Добавить задачу\n");
    printf("2. Показать все задачи\n");
    printf("3. Изменить статус выполнения\n");
    printf("4. Удалить задачу\n");
    printf("5. Сохранить в файл\n");
    printf("0. Сохранить и выйти\n");
}

const char* get_priority_str(int priority) {
    switch (priority) {
        case 1: return "Низкий";
        case 2: return "Средний";
        case 3: return "Высокий";
        default: return "Неизвестно";
    }
}

void add_task(TaskManager *tm) {
    if (tm->count >= MAX_TASKS) {
        printf("Ошибка: достигнут лимит задач (%d).\n", MAX_TASKS);
        return;
    }

    Task new_task;
    new_task.id = tm->next_id++;
    new_task.completed = false;

    printf("Введите описание задачи: ");
    if (fgets(new_task.title, MAX_TITLE_LEN, stdin) == NULL) {
        printf("Ошибка чтения строки.\n");
        return;
    }
    // Удаляем символ переноса строки в конце
    new_task.title[strcspn(new_task.title, "\n")] = '\0';

    if (strlen(new_task.title) == 0) {
        printf("Описание не может быть пустым.\n");
        tm->next_id--;
        return;
    }

    printf("Выберите приоритет (1 - Низкий, 2 - Средний, 3 - Высокий): ");
    if (scanf("%d", &new_task.priority) != 1 || new_task.priority < 1 || new_task.priority > 3) {
        printf("Некорректный приоритет. Установлен 'Средний' (2).\n");
        new_task.priority = 2;
    }
    clear_input_buffer();

    tm->items[tm->count++] = new_task;
    printf("Задача #%d успешно добавлена!\n", new_task.id);
}

void list_tasks(const TaskManager *tm) {
    if (tm->count == 0) {
        printf("\nСписок задач пуст.\n");
        return;
    }

    printf("\n%-4s | %-6s | %-9s | %s\n", "ID", "Статус", "Приоритет", "Описание");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < tm->count; i++) {
        const Task *t = &tm->items[i];
        printf("%-4d | %-6s | %-9s | %s\n",
               t->id,
               t->completed ? "[X]" : "[ ]",
               get_priority_str(t->priority),
               t->title);
    }
}

void toggle_task(TaskManager *tm) {
    int id;
    printf("Введите ID задачи для смены статуса: ");
    if (scanf("%d", &id) != 1) {
        printf("Некорректный ввод.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    for (int i = 0; i < tm->count; i++) {
        if (tm->items[i].id == id) {
            tm->items[i].completed = !tm->items[i].completed;
            printf("Статус задачи #%d обновлен.\n", id);
            return;
        }
    }
    printf("Задача с ID %d не найдена.\n", id);
}

void delete_task(TaskManager *tm) {
    int id;
    printf("Введите ID задачи для удаления: ");
    if (scanf("%d", &id) != 1) {
        printf("Некорректный ввод.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    for (int i = 0; i < tm->count; i++) {
        if (tm->items[i].id == id) {
            // Сдвигаем оставшиеся элементы влево
            for (int j = i; j < tm->count - 1; j++) {
                tm->items[j] = tm->items[j + 1];
            }
            tm->count--;
            printf("Задача #%d удалена.\n", id);
            return;
        }
    }
    printf("Задача с ID %d не найдена.\n", id);
}

void save_tasks(const TaskManager *tm) {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        perror("Ошибка открытия файла для записи");
        return;
    }

    fwrite(&tm->count, sizeof(int), 1, file);
    fwrite(&tm->next_id, sizeof(int), 1, file);
    fwrite(tm->items, sizeof(Task), tm->count, file);

    fclose(file);
    printf("Данные сохранены в '%s'.\n", FILENAME);
}

void load_tasks(TaskManager *tm) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        // Файл еще не создан, это нормально при первом запуске
        return;
    }

    if (fread(&tm->count, sizeof(int), 1, file) != 1 ||
        fread(&tm->next_id, sizeof(int), 1, file) != 1) {
        fclose(file);
        return;
    }

    if (tm->count > MAX_TASKS) {
        tm->count = MAX_TASKS;
    }
    fread(tm->items, sizeof(Task), tm->count, file);

    fclose(file);
    printf("Загружено задач: %d\n", tm->count);
}
