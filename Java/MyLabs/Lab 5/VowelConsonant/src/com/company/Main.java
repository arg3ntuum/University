package com.company;

import java.util.Scanner;

//vowels:a, e, i, o, u
public class Main {
        public static void main(String[] args) {
            Scanner in = new Scanner(System.in);
            System.out.print("Введите количество символов что собираетесь обрабатывать: ");
            byte kolvo = in.nextByte();
            System.out.print("Введите строку для обработки: ");
            String something = in.next();
            System.out.print(something);
            StackChar golosni = new StackChar(something.length()); // Створення нового стека
            StackChar prigolosni = new StackChar(something.length()); // Створення нового стека

            char pole;
            for(int i = 0;i < something.length();i++){
                pole = something.charAt(i);
                if (pole  >= 'a' && pole <= 'z' || pole  >= 'A' && pole <= 'Z') {
                    if(pole == 'a' ||pole == 'A' ||pole == 'e' ||pole == 'E' ||pole == 'i' || pole == 'I' ||pole == 'o' ||pole == 'O' ||pole == 'u' ||pole == 'U')
                        golosni.push(pole);
                    else prigolosni.push(pole);
                }
            }

            System.out.print("\nСтек голосных:");
            for(int i = 0;i < kolvo;i++){
                char value = golosni.pop(); // Видалити елемент зі стеку
                System.out.print(value); // Вивід вмісту
                if (golosni.isEmpty())
                    break;
            }

            System.out.print("\nСтек приголосных:");
            for(int i = 0;i < kolvo;i++){
                char value = prigolosni.pop(); // Видалити елемент зі стеку
                System.out.print(value); // Вивід вмісту
                if (prigolosni.isEmpty())
                    break;
            }

    }
}
