package com.company;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.print("Введите количество символов что собираетесь обрабатывать: ");
        byte kolvo = in.nextByte();
        System.out.print("Введите строку для обработки: ");
        String something = in.next();
        System.out.print(something);

        StackChar symbol = new StackChar(something.length()); // Створення нового стека
        StackX num = new StackX(something.length()); // Створення нового стека
        char pole;
        for(int i = 0;i < something.length();i++){
            pole = something.charAt(i);
            if (pole  >= '0' && pole <= '9')//if(pole == '1' || pole == '2' || pole == '3' || pole == '4')//Character.toString(something.charAt(0))
                num.push(something.charAt(i));// Занесення елементів в стек
            else symbol.push(pole);
        }

        System.out.print("\nСтек символов:");
        for(int i = 0;i < kolvo;i++){
            char value = symbol.pop(); // Видалити елемент зі стеку
            System.out.print(value); // Вивід вмісту
            if (symbol.isEmpty())
                break;
        }
        System.out.print("\nСтек чисел:");
        for(int i = 0;i < kolvo;i++){
            if (num.isEmpty())
                break;
            long value = num.pop();
            if (value != 0) // Видалити елемент зі стеку
            System.out.print(value - 48); // Вивід вмісту
            if (num.isEmpty())
                break;
        }

    }
}