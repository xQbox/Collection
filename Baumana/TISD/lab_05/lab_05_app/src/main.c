#include "process.h"

float q1_f_s = 1, q1_f_f = 5, q2_f_s = 0, q2_f_f = 3;
float q1_w_s = 0, q1_w_f = 4, q2_w_s = 0, q2_w_f = 1;


void param()
{
    while (1)
    {
        int rc;
        printf("Введите начало и конец интервала доставки в первую очередь(x y)\n");
        rc = scanf("%f%f", &q1_f_s, &q1_f_f);
        if (rc != 2)
        {
            printf("Неправильный ввод\n");
            continue;
        }
        else if (q1_f_s >= q1_f_f)
        {
            printf("Неправильный ввод\n");
            continue;
        }
        else if (q1_f_s < 0 || q1_f_f < 0)
        {
            printf("Неправильный ввод\n");
            continue;
        }

        printf("Введите начало и конец интервала доставки во вторую очередь(x->y)\n");
        rc = scanf("%f%f", &q2_f_s, &q2_f_f);
        if (rc != 2)
        {
            printf("Неправильный ввод\n");
            continue;
        }
        else if (q2_f_s >= q2_f_f)
        {
            printf("Неправильный ввод\n");
            continue;
        }
        else if (q2_f_s < 0 || q2_f_f < 0)
        {
            printf("Неправильный ввод\n");
            continue;
        }

        printf("Введите начало и конец интервала выполнения заявки из первой очереди(x->y)\n");
        rc = scanf("%f%f", &q1_w_s, &q1_w_f);
        if (rc != 2)
        {
            printf("Неправильный ввод\n");
            continue;
        }
        else if (q1_w_s >= q1_w_f)
        {
            printf("Неправильный ввод\n");
            continue;
        }
        else if (q1_w_s < 0 || q1_w_f < 0)
        {
            printf("Неправильный ввод\n");
            continue;
        }

        printf("Введите начало и конец интервала выполнения заявки из второй очереди(x->y)\n");
        rc = scanf("%f%f", &q2_w_s, &q2_w_f);
        if (rc != 2)
        {
            printf("Неправильный ввод\n");
            continue;
        }
        else if (q2_w_s >= q2_w_f)
        {
            printf("Неправильный ввод\n");
            continue;
        }
        else if (q2_w_s < 0 || q2_w_f < 0)
        {
            printf("Неправильный ввод\n");
            continue;
        }

        break;
    }
}


int main(void)
{
    int choice;
    int rc;
    char *menu = "0 - завершение работы программы\n1 - запустить прототип для очереди массивом\n2 - запустить прототип для очереди списком\n"
    "3 - эффективность\n4 - перейти в ручной режим\n5 - поменять параметры прототипа\n";
    printf("Программа реализует обслуживающий аппарат , который принимает заявки из 2-х очередей\n");

    while (1)
    {
        printf("Выберите пункт меню:\n");
        printf("%s", menu);
        rc = scanf("%d", &choice);
        if (rc != 1)
        {
            printf("Неверный пункт меню\n");
            while (getchar() != '\n')
                ;
            continue;
        }
        else
        {
            switch (choice)
            {
            case 0:
                return 0;
                break;
            case 1:
                simulate_array();
                break;
            case 2:
                simulate_list();
                break;
            case 3:
                efficiency();
                break;
            case 4:
                manu_mode();
                break;
            case 5:
                param();
                break;
            default:
                printf("Неверно введен пункт меню\n");
                break;
            }
        }
    }
    return 0;
}
